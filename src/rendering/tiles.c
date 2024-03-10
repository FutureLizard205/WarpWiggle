#include "tiles.h"

// The tiles which have an even id (LSb = 0) will be drawn exactly the same 
// every time, independently of the connections it has. In the map loader.c 
// file, the calcTileConnections function skips these are they are never used.
//
// The other tiles will always be drawn according to what connections they have.

#define TEXTURE_RESOLUTION 16

void drawMapTiles(appData_t *app, textures_t *textures, mapData_t *mapData, uint_fast16_t hOffset, uint_fast16_t vOffset) {
  
  uint_fast8_t tileID, tileConnections, tileXPos, tileYPos;
  uint_fast8_t hSize = mapData->hSize;
  uint_fast8_t vSize = mapData->vSize;
  SDL_Rect srcRect;
  bool lastOneWasEven = false;
  
  for(uint_fast8_t v = 0; v <= vSize; v++) {
    for(uint_fast8_t h = 0; h <= hSize; h++) {
      tileID = mapData->tiles[v*(hSize+1)+h];
      
      if ((tileID & 0b1) == 0) {
        // Tile with even ID       
        if (!lastOneWasEven) {

          srcRect.x = 0;
          srcRect.y = 0;
          srcRect.h = TEXTURE_RESOLUTION;
          srcRect.w = TEXTURE_RESOLUTION;
          lastOneWasEven = true;
        }
        
      } else {
        // Tile with odd ID
        lastOneWasEven = false;

        // TODO: Add calculations for srcRect

      }
      

      blit(app, textures->tilesTextures[tileID], &srcRect, 
      hOffset + h * TEXTURE_RESOLUTION, 
      vOffset + v * TEXTURE_RESOLUTION, 
      TEXTURE_RESOLUTION, TEXTURE_RESOLUTION);
    }
  }
}
