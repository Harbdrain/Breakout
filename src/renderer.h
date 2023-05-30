#pragma once
#include <SDL2/SDL.h>

#include "utils.h"

typedef struct {
    uint8 r;
    uint8 g;
    uint8 b;
} Color;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Rect viewport_rect;
} RendererState;

extern RendererState* renderer_init(SDL_Renderer* renderer,
                                    SDL_Rect viewport_rect);
extern void renderer_buffer_clear(Color color);
extern void renderer_buffer_present(void);
extern void renderer_buffer_rect_draw(SDL_Rect* rect, Color color);
extern void renderer_viewport_set(SDL_Rect rect);

#define renderer_color_set(color, c_r, c_g, c_b) \
    color.r = c_r;                               \
    color.g = c_g;                               \
    color.b = c_b;
