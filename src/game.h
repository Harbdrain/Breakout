#pragma once

typedef struct {
    int mouse_x;
    int mouse_y;
} InputState;

typedef struct {
    int target_window_w;
    int target_window_h;
    int running;
    InputState input_state;

    void (*draw)(void);
} Game;

extern Game* game_init(void);
