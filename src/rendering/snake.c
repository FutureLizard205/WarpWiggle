#include "snake.h"

#define TEXTURE_RESOLUTION 16

void drawSnake(appData_t *app, textures_t *textures, snakeData_t snakeData) {
  SDL_Rect sourceRect;
  sourceRect.h = TEXTURE_RESOLUTION;
  sourceRect.w = TEXTURE_RESOLUTION;
  
  uint_fast8_t id;

  for (uint_fast32_t i = 0; i <= snakeData.tailLength; i++) {
    if(i == 0) {
      // Head of the snake

      id = 16 + snakeData.tiles[i].headedFromDirection;
    } else {

      id = 4 * snakeData.tiles[i-1].headedFromDirection;
      
      if (i == snakeData.tailLength) {
        // Tail of the snake

        id += id/4;

      } else {
        // Other snake tiles

        if (snakeData.tiles[i]. headedFromDirection < 2) {
          id += snakeData.tiles[i].headedFromDirection + 2;
        } else {
          id += snakeData.tiles[i].headedFromDirection - 2;
        }

        if (id / 4 > id % 4) {
          // Invert from the empty texture region
          id = 4 * (id%4) + id/4;  
        }
      }    
    }


    sourceRect.x = TEXTURE_RESOLUTION * (id % 4);
    sourceRect.y = TEXTURE_RESOLUTION * (id / 4);

    blit(app, textures->snakeTexture, &sourceRect, 
    TEXTURE_RESOLUTION * snakeData.tiles[i].x, 
    TEXTURE_RESOLUTION * snakeData.tiles[i].y, 
    TEXTURE_RESOLUTION, 
    TEXTURE_RESOLUTION);
  }
  
}
