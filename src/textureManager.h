#pragma once

#include <string.h>
#include <stdlib.h>

#include "sdlInclude.h"
#include "globalStructs.h"

SDL_Texture *loadTexture(const appData_t* app, const char* filename);
