#include "renderer.h"

void blit(appData_t *app, SDL_Texture *texture, SDL_Rect *sourceRect, const uint_fast16_t x, const uint_fast16_t y, const uint_fast16_t w, const uint_fast16_t h) {
  
  uint_fast8_t scale = app->renderingScale;

  SDL_Rect destRect;
  destRect.x = x * scale;
  destRect.y = y * scale;
  
  if (w == 0 || h == 0) {
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
    destRect.w *= scale;
    destRect.h *= scale;
  } else {
    destRect.w = w * scale;
    destRect.h = h * scale;
  }

  SDL_RenderCopy(app->renderer, texture, sourceRect, &destRect);
}
