#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>
#include "globalConstants.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL2.\n");
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_HORIZONTAL_SIZE,
                                          WINDOW_VERTICAL_SIZE,
                                          SDL_WINDOW_BORDERLESS);

    if (!window) {
        printf("Failed to create window.\n");
        return EXIT_FAILURE;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if (!window_surface) {
        printf("Failed to get the surface from the window\n");
        return EXIT_FAILURE;
    }

    SDL_Event event;
    const double fps_limit_ms = 1000 / (double) FPS_LIMIT;
    uint64_t perfCount_cycle_start;
    uint64_t perfCount_cycle_end;
    double time_cycle;
    for (int i = 0; i < 200; i++) {
        perfCount_cycle_start = SDL_GetPerformanceCounter();


        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    return 0;
            }
        }

        SDL_UpdateWindowSurface(window);


        perfCount_cycle_end = SDL_GetPerformanceCounter();
        time_cycle = 1000 * (perfCount_cycle_end - perfCount_cycle_start) / (double) SDL_GetPerformanceFrequency();
        if (time_cycle < fps_limit_ms) {
            SDL_Delay(fps_limit_ms - time_cycle);
        }

    }

    return EXIT_SUCCESS;
}