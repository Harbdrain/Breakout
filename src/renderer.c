#include "renderer.h"

#include <SDL2/SDL.h>

void renderer_buffer_clear(SDL_Renderer* renderer, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void renderer_buffer_present(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
}

void renderer_buffer_rect_draw(SDL_Renderer* renderer, int x, int y, int w,
                               int h, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                           SDL_ALPHA_OPAQUE);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
}

void renderer_color_set(Color* color, uint8 r, uint8 g, uint8 b) {
    color->r = r;
    color->g = g;
    color->b = b;
}