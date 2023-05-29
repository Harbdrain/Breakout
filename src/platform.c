#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>

#include "renderer.h"

internal int running;
internal int const target_w = 800;
internal int const target_h = 600;
internal SDL_Renderer* renderer;

internal void event_process(SDL_Event event) {
    switch (event.type) {
        case SDL_QUIT: {
            running = 0;
        } break;
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0;
            }
        } break;
        case SDL_WINDOWEVENT: {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int w = event.window.data1;
                int h = event.window.data2;
                SDL_Rect rect = {0};

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
                SDL_RenderSetViewport(renderer, &rect);
            }
        } break;
    }
}

int main(void) {
    assert(SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0);
    SDL_Window* window =
        SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, target_w, target_h, 0);
    assert(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer);

    running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            event_process(event);
        }

        Color color = {255, 0, 0};
        renderer_buffer_clear(renderer, color);

        renderer_color_set(&color, 0, 0, 255);
        renderer_buffer_rect_draw(renderer, 0, 0, 1000, 1000, color);
        renderer_buffer_present(renderer);
        SDL_Delay(1);
    }
    return 0;
}
