#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include "renderer.h"

#define charHeight 7
#define charWidth 7
#define ASCII_FONT_OFFSET 32

enum fontAlignment {LEFT_ALIGNMENT, CENTER_ALIGNMENT, RIGHT_ALIGNMENT};

#define COLOR_WHITE   255 ,255 ,255
#define COLOR_BLACK   0   ,0   ,0
#define COLOR_RED     255 ,0   ,0
#define COLOR_GREEN   0   ,255 ,0
#define COLOR_BLUE    0   ,0   ,255

SDL_Rect *fontRectCacheCreate(); 

void setFontColor(SDL_Texture *fontTexture, uint8_t r, uint8_t g, uint8_t b);

void drawText(appData_t *app, SDL_Texture *fontTexture, SDL_Rect *fontRectCache, char *text, uint_fast16_t x, uint_fast16_t y, enum fontAlignment alignment);
