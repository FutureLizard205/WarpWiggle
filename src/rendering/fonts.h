#pragma once

#include <ctype.h>
#include <stdlib.h>
#include "renderer.h"

#define charHeight 7
#define charWidth 7
#define ASCII_FONT_OFFSET 32

enum fontAlignment {LEFT_ALIGNMENT, CENTER_ALIGNMENT, RIGHT_ALIGNMENT};

SDL_Rect *fontRectCacheCreate(); 

void drawText(appData_t *app, SDL_Texture *fontTexture, SDL_Rect *fontRectCache, char *text, uint_fast16_t x, uint_fast16_t y, enum fontAlignment alignment);
