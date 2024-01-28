#pragma once

#include <stdint.h>
#include "sdlInclude.h"

struct appData {
  SDL_Window* window;
  SDL_Renderer *renderer;
  uint16_t windowHSize;
  uint16_t windowVSize;
  char windowTitle[16];
  uint16_t fpsLimit;
};

typedef struct {
  struct appData app;
} globalData_t;
