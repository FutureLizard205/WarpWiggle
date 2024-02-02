#pragma once

#include "../sdlInclude.h"

#include "../globalStructs.h"

void blit(appData_t *app, SDL_Texture *texture, SDL_Rect *sourceRect, const int x, const int y, const int w, const int h); 
