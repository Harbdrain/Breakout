#include <SDL2/SDL.h>
#include <stdio.h>

#include "game.h"
#include "renderer.h"

internal RendererState* renderer_state;
internal Game* game;

internal void platform_event_process(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT: {
            game->running = 0;
        } break;
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game->running = 0;
            }
        } break;
        case SDL_MOUSEMOTION: {
            game->input_state.mouse_x =
                event.motion.x - renderer_state->viewport_rect.x;
            game->input_state.mouse_y =
                event.motion.y - renderer_state->viewport_rect.y;
        } break;
        case SDL_WINDOWEVENT: {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int w = event.window.data1;
                int h = event.window.data2;
                SDL_Rect rect = (SDL_Rect){0};

                int target_w = game->target_window_w;
                int target_h = game->target_window_h;
                // (w / h > target_w / target_h)
                if (w * target_h > target_w * h) {
                    rect.h = h;
                    rect.w = h * target_w / target_h;
                    rect.x = (w - rect.w) / 2;
                } else {
                    rect.w = w;
                    rect.h = w * target_h / target_w;
                    rect.y = (h - rect.h) / 2;
                }
                renderer_viewport_set(rect);
            }
        } break;
    }
}

internal int platform_init(void) {
    // SDL init
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL subsystem initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow(
        "Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        game->target_window_w, game->target_window_h, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return -1;
    }
    
    // game init
    renderer_state = renderer_init(
        renderer,
        (SDL_Rect){0, 0, game->target_window_w, game->target_window_h});
    game = game_init();
    return 0;
}

int main(void) {
    if (platform_init() != 0) {
        return 0;
    }

    game->running = 1;
    uint64 last_time = SDL_GetTicks64();
    uint64 frames_count = 0;
    while (game->running) {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            platform_event_process(event);
        }

        // draw things
        game->draw();

        // count FPS
        uint64 cur_time = SDL_GetTicks64();
        frames_count++;
        if (cur_time - last_time >= 1000) {
            float fps =
                (float)(1000 * frames_count) / (float)(cur_time - last_time);
            printf("FPS: %f\n", fps);
            frames_count = 0;
            last_time = cur_time;
        }
    }
    return 0;
}
