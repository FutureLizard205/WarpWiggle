#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdlInclude.h"

#include "globalMacros.h"
#include "globalStructs.h"

#include "windowManager.h"
#include "textureManager.h"
#include "snakeManager.h"

#include "rendering/fonts.h"
#include "rendering/snake.h"
#include "rendering/tiles.h"

#include "map/loader.h"

#define TEXTURE_RESOLUTION 16

int main(int argc, char *argv[]) {
  
  // SDL2 Initialization

  macro_error(SDL_Init(SDL_INIT_VIDEO) < 0, "Failed to initialize SDL2.");

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);


  // Global Data Initialization

  appData_t app;

  strcpy(app.windowTitle, "WarpWiggle");
  app.fpsLimit = 0;
  app.windowHTiles = 32;
  app.windowVTiles = 20;
  app.renderingScale = getMaxWindowScale(&app);
  
  
  // Window and Render Initialization

  app.window = SDL_CreateWindow(app.windowTitle,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                TEXTURE_RESOLUTION * app.windowHTiles * app.renderingScale,
                                TEXTURE_RESOLUTION * app.windowVTiles * app.renderingScale,
                                0);
  
  macro_error(!app.window, "Failed to create window.");

  app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_PRESENTVSYNC);

  macro_error(!app.renderer, "Failed to create renderer.");
 

  // loadTextures function test
  textures_t *textures = loadTextures(&app);

  // Font Cache
  SDL_Rect *fontRectCache = fontRectCacheCreate();


  // Map load test
  mapData_t *map = loadMapFile("01");
  
  // snakeManager test
  snakeData_t *snake = getSnakeDataFromInitialData(*map);
  

  // Snake Data for testing
  snake->tailLength += 2;
  
  snake->tiles[0].x = 1;
  snake->tiles[0].y = 1;
  snake->tiles[0].headedFromDirection = 1;

  snake->tiles[1].x = 0;
  snake->tiles[1].y = 1;
  snake->tiles[1].headedFromDirection = 2;

  snake->tiles[2].x = 0;
  snake->tiles[2].y = 0;
  snake->tiles[2].headedFromDirection = 3;

  snake->tiles[3].x = 1;
  snake->tiles[3].y = 0;



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
    setFontColor(textures, COLOR_WHITE);
    drawText(&app, textures, fontRectCache, "abcxyz.:12345;,ABCDE!-?", 210, 20, LEFT_ALIGNMENT);  
    setFontColor(textures, COLOR_BLACK);
    drawText(&app, textures, fontRectCache, "Some text is here 123", 250, 120, LEFT_ALIGNMENT);
    setFontColor(textures, COLOR_RED);
    drawText(&app, textures, fontRectCache, "Some text is here 123", 250, 130, CENTER_ALIGNMENT);
    setFontColor(textures, COLOR_BLUE);
    drawText(&app, textures, fontRectCache, "Some text is here 123", 250, 140, RIGHT_ALIGNMENT);

    // drawSnake function test
    drawSnake(&app, textures, *snake);

    // drawMapTiles function test
    drawMapTiles(&app, textures, map, 16, 16);


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
