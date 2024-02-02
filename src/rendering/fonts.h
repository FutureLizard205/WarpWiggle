#pragma once

#include <ctype.h>
#include "renderer.h"

#define charHeight 7
#define charWidth 7

enum fontAlignment {LEFT_ALIGNMENT, CENTERED_ALIGNMET, RIGHT_ALIGNMENT};

void drawText(appData_t *app, SDL_Texture *fontTexture, char *text, uint8_t x, uint8_t y, enum fontAlignment alignment);  
