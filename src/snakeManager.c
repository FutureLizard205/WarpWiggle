#include "snakeManager.h"

/*
* This function is used to get the data for a new snake 
* from the initial data provided in the map file
*/
snakeData_t *getSnakeDataFromInitialData(mapData_t mapData) {
  
  snakeData_t *snakeData = malloc(sizeof(snakeData_t));
  snakeData->tiles = malloc((mapData.scoreGoal + mapData.initialSnakeData.tailLength + 1) * sizeof(snakeTileData_t));

  snakeData->type = mapData.initialSnakeData.type;
  snakeData->tailLength = mapData.initialSnakeData.tailLength;

  for (uint_fast32_t i = 0; i <= snakeData->tailLength; i++) {
    snakeData->tiles[i] = mapData.initialSnakeData.tiles[i];    
  }
  
  
  return snakeData;
}
