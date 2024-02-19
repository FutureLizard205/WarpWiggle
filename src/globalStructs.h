#pragma once

#include <stdint.h>
#include "sdlInclude.h"


typedef struct {
  SDL_Window* window;
  SDL_Renderer *renderer;
  uint16_t windowHSize;
  uint16_t windowVSize;
  char windowTitle[16];
  uint16_t fpsLimit;
} appData_t;


typedef struct {
  uint_fast8_t x;
  uint_fast8_t y;
  uint_fast8_t headedFromDirection; // 0 = bottom, 1 = left, 2 = top, 3 = right
  // The direction where each tile is headed towoards corresponds to the reverse headedFromDirection of the next one
} snakeTileData_t;


typedef struct {
  uint_fast8_t type;
  uint_fast16_t tailLength;
  snakeTileData_t *tiles;     // Array with tailLength + 1 size
} snakeData_t;


typedef struct {
  uint_fast8_t dataVersion;
  uint_fast8_t hSize;
  uint_fast8_t vSize;
  uint_fast8_t fruitType;
  uint_fast16_t scoreGoal;
  uint_fast16_t timeLimit;
  uint_fast16_t theme;
  snakeData_t initialSnakeData;
  char *description;              // Array that ends in the first '\0'
  uint_fast8_t *tiles;            // Array with hSize * vSive size
  uint_fast8_t *tileConnections;       // Array with hSize * vSive size
} mapData_t;


typedef struct {
  SDL_Texture *snakeTexture;
  SDL_Texture *fontTexture;
  SDL_Texture **tilesTextures;
} textures_t;
