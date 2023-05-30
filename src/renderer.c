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

void renderer_buffer_rect_draw(SDL_Rect* rect, Color color) {
    SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(state.renderer, rect);
}

void renderer_viewport_set(SDL_Rect rect) {
    state.viewport_rect.x = rect.x;
    state.viewport_rect.y = rect.y;
    state.viewport_rect.h = rect.h;
    state.viewport_rect.w = rect.w;
    SDL_RenderSetViewport(state.renderer, &rect);
}
