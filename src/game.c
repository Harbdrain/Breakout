#include "game.h"

#include "renderer.h"
#include "utils.h"

typedef struct {
    int x;
    int y;
} Vec2;
typedef struct {
    int x, y;
    int w, h;
    Vec2 velocity;
} Ball;
typedef struct {
    int x, y;
    int w, h;
} Block;

internal Game game = {0};
internal Ball ball = {0};
internal Block player = {0};

// TODO: temporary function. Change later. Also it does not account viewport
internal void game_coordinates_convert_from_virtual(int x, int y, int w, int h,
                                                    SDL_Rect* rect) {
    rect->x = x - w / 2;
    rect->y = game.target_window_h - y - h / 2;
    rect->w = w;
    rect->h = h;
}

internal void game_draw(void) {
    renderer_buffer_clear((Color){0, 0, 255});
    SDL_Rect rect;
    game_coordinates_convert_from_virtual(ball.x, ball.y, ball.w, ball.h,
                                          &rect);
    renderer_buffer_rect_draw(&rect, (Color){4, 191, 110});
    game_coordinates_convert_from_virtual(player.x, player.y, player.w,
                                          player.h, &rect);
    renderer_buffer_rect_draw(&rect, (Color){0, 255, 0});
    renderer_buffer_present();
}

internal void game_update(void) {
    // Ball
    ball.x += ball.velocity.x;
    ball.y += ball.velocity.y;
    if (ball.x < ball.w / 2 || ball.x > game.target_window_w - ball.w / 2) {
        ball.velocity.x *= -1;
    }
    if (ball.y < ball.h / 2 || ball.y > game.target_window_h - ball.h / 2) {
        ball.velocity.y *= -1;
    }
    // Player
    // TODO: account viewport
    player.x = game.input_state.mouse_x;
}

Game* game_init(void) {
    game.target_window_w = 800;
    game.target_window_h = 600;
    game.draw = &game_draw;
    game.update = &game_update;

    ball = (Ball){400, 500, 20, 20, {2, -4}};
    player = (Block){game.target_window_w / 2, 100, 200, 20};
    return &game;
}
