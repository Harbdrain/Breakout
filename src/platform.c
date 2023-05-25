#include <SDL2/SDL.h>
#include <stdio.h>

int main(void) {
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) == 0) {
        printf("SDL initialized.\n");
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     800, 600, 0);

    int exit = 0;
    while (!exit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit = 1;
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        exit = 1;
                    }
                    break;
            }
        }

        SDL_Delay(1);
    }
    return 0;
}
