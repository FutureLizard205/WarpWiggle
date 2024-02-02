#pragma once

#include <stdint.h>
#include "../sdlInclude.h"

#include "../globalStructs.h"

void blit(appData_t *app, SDL_Texture *texture, SDL_Rect *sourceRect, const uint_fast16_t x, const uint_fast16_t y, const uint_fast16_t w, const uint_fast16_t h); 
