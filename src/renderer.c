#include "renderer.h"

void blit(appData_t *app, SDL_Texture *texture, const int x, const int y) {
  
  SDL_Rect destRect;
  destRect.x = x;
  destRect.y = y;

  SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

  SDL_RenderCopy(app->renderer, texture, NULL, &destRect);
}
