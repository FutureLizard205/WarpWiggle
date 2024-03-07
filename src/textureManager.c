#include "textureManager.h"

SDL_Texture *loadTextureFile(const appData_t *app, const char *filename, bool isTile) {
  SDL_Texture *texture = NULL; 

  char *filePath = malloc(56 * sizeof(char));

  strcpy(filePath, "assets/textures/");
  
  if (isTile)
    strcat(filePath, "tiles/");

  strcat(filePath, filename);
  strcat(filePath, ".png");
  
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Loading texture file %s...", filePath);

  texture = IMG_LoadTexture(app->renderer, filePath);

  if(!texture) {

    // In the development environment, the assets folder may be inside of the include folder.
    // This takes care of that:

    char *filePath2 = malloc(64 * sizeof(char));
    strcpy(filePath2, "include/");
    strcat(filePath2, filePath);

    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Error, trying %s instead...", filePath2);
    
    texture = IMG_LoadTexture(app->renderer, filePath2);
    
    free(filePath2);
    filePath2 = NULL;
    
    if(!texture) 
      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Failed to load %s texture!", filename);
  }

  free(filePath);
  filePath = NULL;

  return texture;
}


textures_t *loadTextures(const appData_t *app) {
  textures_t *textures = malloc(sizeof(textures_t));
  textures->tilesTextures = malloc(0xFF * sizeof(SDL_Texture*));
  
  textures->snakeTexture = loadTextureFile(app, "snake1", 0);
  textures->fontTexture = loadTextureFile(app, "font", 0);

  textures->tilesTextures[0] = loadTextureFile(app, "00", 1);
  textures->tilesTextures[0x10] = loadTextureFile(app, "10", 1);


  return textures;
}
