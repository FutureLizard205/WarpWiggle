#include "textureManager.h"

SDL_Texture *loadTexture(const appData_t* app, const char* filename) {
  SDL_Texture *texture = NULL; 

  char *filePath = malloc(50 * sizeof(char));

  strcpy(filePath, "assets/textures/");
  strcat(filePath, filename);
  strcat(filePath, ".png");
  
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Loading texture file %s...", filePath);

  texture = IMG_LoadTexture(app->renderer, filePath);

  if(!texture) {

    // In the development environment, the assets folder may be inside of the include folder.
    // This takes care of that:

    char *filePath2 = malloc(58 * sizeof(char));
    strcpy(filePath2, "include/");
    strcat(filePath2, filePath);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Error, trying %s instead...", filePath2);
    
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
