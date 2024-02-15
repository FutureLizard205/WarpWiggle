#include "fonts.h"

/*
 * This function creates a cache which consists of an array of SDL_Rect, 
 * one element for each drawable character, which is used to draw text.
 *
 * It allows the drawText() function not to waste time looking for the 
 * character it wants to draw in the fontTexture.
 */
SDL_Rect *fontRectCacheCreate() {
  /*
   *  Goes through the ASCII table, beginning in address 32 (char '0')
   *  and ending in 126 (char '~').
   */
  
  SDL_Rect *cache = malloc((127 - ASCII_FONT_OFFSET) * sizeof(SDL_Rect));


  for(char i = ASCII_FONT_OFFSET; i < 127; i++) {
    
    cache[i-ASCII_FONT_OFFSET].w = charWidth;
    cache[i-ASCII_FONT_OFFSET].h = charHeight;
    
    if (isdigit(i)) {

      // Digit (0 - 9)
      
      cache[i-ASCII_FONT_OFFSET].x = (i - '0') * charWidth;
      cache[i-ASCII_FONT_OFFSET].y = 2 * charHeight;
      
      continue;
    }

    if (isalpha(i)) {
      
      // Alpha (A - Z, a - z)

      if (isupper(i)) {

        // Upper case (A - Z)
        
        cache[i-ASCII_FONT_OFFSET].x = (i - 'A') * charWidth;
        cache[i-ASCII_FONT_OFFSET].y = 0;

      } else {
        
        // Lower case (a - z)

        cache[i-ASCII_FONT_OFFSET].x = (i - 'a') * charWidth;
        cache[i-ASCII_FONT_OFFSET].y = charHeight;
      
      }

      continue;
    }
    

    // Other chars

    cache[i-ASCII_FONT_OFFSET].y = 2 * charHeight;
      
    switch (i) {
      case '.':
        cache[i-ASCII_FONT_OFFSET].x = 10 * charWidth;
        break;
      
      case ',':
        cache[i-ASCII_FONT_OFFSET].x = 11 * charWidth;
        break;
      
      case ':':
        cache[i-ASCII_FONT_OFFSET].x = 12 * charWidth;
        break;
      
      case ';':
        cache[i-ASCII_FONT_OFFSET].x = 13 * charWidth;
        break;
      
      case '-':
        cache[i-ASCII_FONT_OFFSET].x = 14 * charWidth;
        break;

      case '!':
        cache[i-ASCII_FONT_OFFSET].x = 15 * charWidth;
        break;
      
      case ' ':
        cache[i-ASCII_FONT_OFFSET].x = 17 * charWidth;
        break;

      default:
        // '?'
        cache[i-ASCII_FONT_OFFSET].x = 16 * charWidth;
        break;
    }
  
  }

  
  return cache;
}


void setFontColor(SDL_Texture *fontTexture, uint8_t r, uint8_t g, uint8_t b) {
  SDL_SetTextureColorMod(fontTexture, r, g, b);
}


void drawText(appData_t *app, SDL_Texture *fontTexture, SDL_Rect *fontRectCache, char *text, uint_fast16_t x, uint_fast16_t y, enum fontAlignment alignment) {  

  // Alignment offset
  if (alignment != LEFT_ALIGNMENT) {
    uint_fast16_t size = strlen(text) * charWidth;
    x -= (alignment*size)/2;
  }


  uint_fast16_t i = 0;
  while(text[i] != '\0') {

    // Draw the character
    blit(app, fontTexture, fontRectCache + text[i] - ASCII_FONT_OFFSET, x, y, charWidth, charHeight);
  
    // Increment
    x+=charWidth;
    i++;
  }

}
