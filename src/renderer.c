#include "renderer.h"

#include <SDL2/SDL.h>

internal RendererState state;

RendererState* renderer_init(SDL_Renderer* renderer, SDL_Rect viewport_rect) {
    state.renderer = renderer;
    state.viewport_rect = viewport_rect;
    return &state;
}

// TODO: custom clear function which fill viewport background as well
void renderer_buffer_clear(Color color) {
    SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state.renderer);
}

void renderer_buffer_present(void) { SDL_RenderPresent(state.renderer); }

void renderer_buffer_rect_draw_in_pixels(int x, int y, int w, int h,
                                         Color color) {
    SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b,
                           SDL_ALPHA_OPAQUE);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(state.renderer, &rect);
}
void renderer_buffer_rect_draw_in_pixels_r(SDL_Rect *rect,
                                         Color color) {
    SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(state.renderer, rect);
}

// TODO: define virtual coordinates
// TODO: fix pixel gaping
// NOTE: virtual coordinates are int and equals max resolution? or float for
// physics? Also should move virtual coordinates calculation into game.c
void renderer_buffer_rect_draw(float x, float y, float w, float h,
                               Color color) {
    y = 600.0f - y;
    int pixel_x = (int)((x - w / 2.0f) * (float)state.viewport_rect.w / 800.0f);
    int pixel_y = (int)((y - h / 2.0f) * (float)state.viewport_rect.h / 600.0f);
    int pixel_w = (int)(w * (float)state.viewport_rect.w / 800.0f);
    int pixel_h = (int)(h * (float)state.viewport_rect.h / 600.0f);
    renderer_buffer_rect_draw_in_pixels(pixel_x, pixel_y, pixel_w, pixel_h,
                                        color);
}

void renderer_viewport_set(SDL_Rect rect) {
    state.viewport_rect.x = rect.x;
    state.viewport_rect.y = rect.y;
    state.viewport_rect.h = rect.h;
    state.viewport_rect.w = rect.w;
    SDL_RenderSetViewport(state.renderer, &rect);
}
