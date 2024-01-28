#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdlInclude.h"

#include "globalStructs.h"

#define macro_error(condition, message) \
  if (condition) { \
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL); \
    return EXIT_FAILURE; \
  }


int main(int argc, char *argv[]) {
  
  // Global Data Initialization

  globalData_t globalData;

  globalData.app.windowHSize = 640;
  globalData.app.windowVSize = 480;
  strcpy(globalData.app.windowTitle, "WarpWiggle");
  globalData.app.fpsLimit = 0;


  // SDL2 Initialization

  macro_error(SDL_Init(SDL_INIT_VIDEO) < 0, "Failed to initialize SDL2.");

  globalData.app.window = SDL_CreateWindow(globalData.app.windowTitle,
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        globalData.app.windowHSize,
                                        globalData.app.windowVSize,
                                        0);
  
  macro_error(!globalData.app.window, "Failed to create window.");

  globalData.app.renderer = SDL_CreateRenderer(globalData.app.window, -1, SDL_RENDERER_PRESENTVSYNC);

  macro_error(!globalData.app.renderer, "Failed to create renderer.");
 

  // Game Loop
  
  SDL_Event event;
  const double fps_limit_ms = 1000 / (double) globalData.app.fpsLimit;
  uint64_t perfCount_cycle_start;
  uint64_t perfCount_cycle_end;
  double time_cycle;
  while (1) {

    // Get perfomance counter (for fps calculation)
    perfCount_cycle_start = SDL_GetPerformanceCounter();
    

    // Manage events
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
         case SDL_QUIT:
             SDL_Quit();
             return EXIT_SUCCESS;
      }
    }
    

    // Render
    SDL_SetRenderDrawColor(globalData.app.renderer, 130, 210, 250, SDL_ALPHA_OPAQUE);
	  SDL_RenderClear(globalData.app.renderer);
    SDL_RenderPresent(globalData.app.renderer);


    // FPS Limiter
    if (globalData.app.fpsLimit != 0) {
      perfCount_cycle_end = SDL_GetPerformanceCounter();
      time_cycle = 1000 * (perfCount_cycle_end - perfCount_cycle_start) / (double) SDL_GetPerformanceFrequency();
      if (time_cycle < fps_limit_ms) {
        SDL_Delay(fps_limit_ms - time_cycle);
      }
    }

  }

  return EXIT_SUCCESS;
}
