#include "windowManager.h"

#define TEXTURE_RESOLUTION 16

// This function tries to get the maximum window scale that will comfortably
// fit in the main display (index 0).
// 
// If it fails, or if the display is too small, it will return 1.

uint_fast8_t getMaxWindowScale(const appData_t *app) {
  uint_fast16_t hPixelCount = TEXTURE_RESOLUTION * app->windowHTiles;
  uint_fast16_t vPixelCount = TEXTURE_RESOLUTION * app->windowVTiles;

  SDL_Rect displayRect;
  
  if (!SDL_GetDisplayUsableBounds(0, &displayRect)) {
    // The function failed
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, 
                "Error trying to read display size, setting rendering scale to 1: %s.",
                SDL_GetError());

    return 1;
  }
  
 
  uint_fast8_t maxHSize = (displayRect.w - 40) / hPixelCount;
  uint_fast8_t maxVSize = (displayRect.h - 80) / vPixelCount;
  
  uint_fast8_t result = (maxVSize < maxHSize) ? maxVSize : maxHSize;
  return (result > 0) ? result : 1;
}
