#include "renderer.h"

void blit(appData_t *app, SDL_Texture *texture, SDL_Rect *sourceRect, const uint_fast16_t x, const uint_fast16_t y, const uint_fast16_t w, const uint_fast16_t h) {
  
  SDL_Rect destRect;
  destRect.x = x;
  destRect.y = y;
  
  if (w == 0 || h == 0)
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
  else {
    destRect.w = w;
    destRect.h = h;
  }

  SDL_RenderCopy(app->renderer, texture, sourceRect, &destRect);
}
