#pragma once
#include <SDL2/SDL.h>

#include "utils.h"

typedef struct {
    uint8 r;
    uint8 g;
    uint8 b;
} Color;

extern void renderer_buffer_clear(SDL_Renderer* renderer, Color color);
extern void renderer_buffer_present(SDL_Renderer* renderer);
extern void renderer_buffer_rect_draw(SDL_Renderer* renderer, int x, int y,
                                      int w, int h, Color color);

extern void renderer_color_set(Color* color, uint8 r, uint8 g, uint8 b);
