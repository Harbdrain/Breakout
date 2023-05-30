#include "game.h"

#include "renderer.h"
#include "utils.h"

internal Game game = {0};

internal void game_draw(void) {
    renderer_buffer_clear((Color){255, 0, 0});
    renderer_buffer_rect_draw_in_pixels(0, 0, 1000, 1000, (Color){0, 0, 255});
    renderer_buffer_rect_draw_in_pixels(game.input_state.mouse_x - 100, 50, 200,
                                        20, (Color){0, 255, 0});
    renderer_buffer_present();
}

Game* game_init(void) {
    game.target_window_w = 800;
    game.target_window_h = 600;
    game.draw = &game_draw;
    return &game;
}
