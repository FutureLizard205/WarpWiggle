#include "loader.h"

/*
* This function is used to determine the connections of the map tiles,
* to be used when rendering them.
* A tile is considered connected to another one if they have the same id.
*
* It returns an array of uint_fast8_t, each element relative to each tile,
* where the 0s indicate no connection, and the 1s a connection, 
* going clockwise, from LSb to MSb, starting in the tile directly above.
*/
uint_fast8_t *calcTileConnections(mapData_t *mapData) {
  
  uint_fast8_t h = mapData->hSize + 1;
  uint_fast8_t v = mapData->vSize + 1;  

  uint_fast8_t *tileConnections=calloc(h*v, sizeof(uint_fast8_t));

  uint_fast8_t currentTile;
  for(uint_fast8_t i = 0; i < h; i++){
    for(uint_fast8_t j = 0; j < v; j++){
      
      currentTile = mapData->tiles[h*i+j];
      if(i != 0) {
        if(mapData->tiles[h*(i-1)+j] == currentTile)
          tileConnections[h*i+j] |= 0b00000001;
        if(j != h-1)
          if(mapData->tiles[h*(i-1)+j+1] == currentTile)
            tileConnections[h*i+j] |= 0b00000010;
        if(j != 0)
          if(mapData->tiles[h*(i-1)+j-1] == currentTile)
            tileConnections[h*i+j] |= 0b10000000;

      }

      if(i != v-1) {
        if(j != h-1)
          if(mapData->tiles[h*(i+1)+j+1] == currentTile)
            tileConnections[h*i+j] |= 0b00001000;
        if(mapData->tiles[h*(i+1)+j] == currentTile)
          tileConnections[h*i+j] |= 0b00010000;
        if(j != 0)
          if(mapData->tiles[h*(i+1)+j-1] == currentTile)
            tileConnections[h*i+j] |= 0b00100000;

      }

      if(j != 0) {
        if(mapData->tiles[h*i+j-1] == currentTile) {
          tileConnections[h*i+j] |= 0b01000000;
        }
      }
        
      if(j != h-1) {
        if(mapData->tiles[h*i+j+1] == currentTile) {
          tileConnections[h*i+j] |= 0b00000100;
        }
      }
    }
  }

  return tileConnections;
}



mapData_t *loadMapFile(const char *mapName) {
  
  char *filePath = malloc(62 * sizeof(char));

  strcpy(filePath, "assets/maps/");
  strcat(filePath, mapName);
  strcat(filePath, ".wwmap");
 
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Loading map file %s...", filePath);

  FILE *mapFile = fopen(filePath, "rb");

  if (!mapFile) {
    
    char *filePath2 = malloc(70 * sizeof(char));

    strcpy(filePath2, "include/");
    strcat(filePath2, filePath);
    
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Error, trying %s instead...", filePath2);
    
    mapFile = fopen(filePath2, "rb");
    
    free(filePath2);
    filePath2 = NULL;
  }

  free(filePath);
  filePath = NULL;

  if (!mapFile) {
    char *errorString = malloc(85 * sizeof(char));
    strcpy(errorString, "Couldn't load map file ");
    strcat(errorString, mapName);
    strcat(errorString, ".");
    macro_errorMessage(errorString);
    free(errorString);
    errorString = NULL;
    return NULL;
  }


  mapData_t *mapData = calloc(1, sizeof(mapData_t));
  
  
  fread(&mapData->dataVersion, sizeof(uint8_t), 1, mapFile);
  fread(&mapData->hSize, sizeof(uint8_t), 1, mapFile);
  fread(&mapData->vSize, sizeof(uint8_t), 1, mapFile);
  fread(&mapData->fruitType, sizeof(uint8_t), 1, mapFile);
  fread(&mapData->scoreGoal, sizeof(uint16_t), 1, mapFile);
  fread(&mapData->timeLimit, sizeof(uint16_t), 1, mapFile);
  fread(&mapData->theme, sizeof(uint16_t), 1, mapFile);
  
 
  fread(&mapData->initialSnakeData.type, sizeof(uint8_t), 1, mapFile);
  fread(&mapData->initialSnakeData.tailLength, sizeof(uint16_t), 1, mapFile);
  
  mapData->initialSnakeData.tiles = calloc(mapData->initialSnakeData.tailLength + 1, sizeof(snakeTileData_t));
  uint_fast16_t i = 0;
  while(i <= mapData->initialSnakeData.tailLength) {
    fread(&(mapData->initialSnakeData.tiles[i].x), 1, sizeof(uint8_t), mapFile);
    fread(&(mapData->initialSnakeData.tiles[i].y), 1, sizeof(uint8_t), mapFile);
    fread(&(mapData->initialSnakeData.tiles[i].headedFromDirection), 1, sizeof(uint8_t), mapFile);
    i++;
  }
  

  mapData->description = malloc(20 * sizeof(char));

  i = 0;
  do {
    fread(&(mapData->description[i++]), 1, sizeof(char), mapFile);
  } while (mapData->description[i-1] != '\0'); 


  uint_fast16_t numberOfTiles = (mapData->hSize + 1) * (mapData->vSize + 1);

  mapData->tiles = calloc(numberOfTiles, sizeof(uint_fast8_t));

  i = 0;
  while(fread(&(mapData->tiles[i]), sizeof(char), 1, mapFile) && i < numberOfTiles - 1) {
    i++;
  }

  fclose(mapFile);
  mapFile = NULL;


  mapData->tileConnections = calcTileConnections(mapData);

  // Test
  /*
  for(i = 0; i <= mapData->hSize; i++) {
    for(uint16_t j = 0; j <= mapData->vSize; j++) {
      printf("%d ",*(mapData->tiles+j+(mapData->hSize+1)*i));
        if(j==mapData->hSize)
          printf("\n");
    }
  }
  

  printf("\n\n");
  for(i = 0; i <= mapData->hSize; i++) {
    for(uint16_t j = 0; j <= mapData->vSize; j++) {
      printf("%3d ",*(mapData->tileConnections+j+(mapData->hSize+1)*i));
        if(j==mapData->hSize)
          printf("\n");
    }
  }
  */




  return mapData;
}
