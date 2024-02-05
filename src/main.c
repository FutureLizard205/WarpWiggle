#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdlInclude.h"

#include "globalMacros.h"
#include "globalStructs.h"
#include "textureManager.h"
#include "rendering/renderer.h"
#include "rendering/fonts.h"

#include "map/loader.h"

int main(int argc, char *argv[]) {
  
  // Global Data Initialization

  appData_t app;

  app.windowHSize = 640;
  app.windowVSize = 480;
  strcpy(app.windowTitle, "WarpWiggle");
  app.fpsLimit = 0;

  // SDL2 Initialization

  macro_error(SDL_Init(SDL_INIT_VIDEO) < 0, "Failed to initialize SDL2.");

  app.window = SDL_CreateWindow(app.windowTitle,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                app.windowHSize,
                                app.windowVSize,
                                0);
  
  macro_error(!app.window, "Failed to create window.");

  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

  macro_error(!app.renderer, "Failed to create renderer.");
 

  // loadTexture function test
  SDL_Texture *fontTex = loadTexture(&app, "font");
  
  // Font Cache
  SDL_Rect *fontRectCache = fontRectCacheCreate();



  // Map load test
  loadMapFile("01");


  // Game Loop
  
  SDL_Event event;
  const double fps_limit_ms = 1000 / (double) app.fpsLimit;
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
    SDL_SetRenderDrawColor(app.renderer, 130, 210, 250, SDL_ALPHA_OPAQUE);
	  SDL_RenderClear(app.renderer);
    
    //blit(&app, fontTex, 20, 20); // blit function test

    // drawText function tests
    setFontColor(fontTex, COLOR_WHITE);
    drawText(&app, fontTex, fontRectCache, "abcxyz.:12345;,ABCDE!-?", 210, 20, LEFT_ALIGNMENT);  
    setFontColor(fontTex, COLOR_BLACK);
    drawText(&app, fontTex, fontRectCache, "Some text is here 123", 250, 120, LEFT_ALIGNMENT);
    setFontColor(fontTex, COLOR_RED);
    drawText(&app, fontTex, fontRectCache, "Some text is here 123", 250, 130, CENTER_ALIGNMENT);
    setFontColor(fontTex, COLOR_BLUE);
    drawText(&app, fontTex, fontRectCache, "Some text is here 123", 250, 140, RIGHT_ALIGNMENT);


   SDL_RenderPresent(app.renderer);


    // FPS Limiter
    if (app.fpsLimit != 0) {
      perfCount_cycle_end = SDL_GetPerformanceCounter();
      time_cycle = 1000 * (perfCount_cycle_end - perfCount_cycle_start) / (double) SDL_GetPerformanceFrequency();
      if (time_cycle < fps_limit_ms) {
        SDL_Delay(fps_limit_ms - time_cycle);
      }
    }

  }

  return EXIT_SUCCESS;
}
