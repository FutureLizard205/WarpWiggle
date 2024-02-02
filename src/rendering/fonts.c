#include "fonts.h"

void drawText(appData_t *app, SDL_Texture *fontTexture, char *text, uint8_t x, uint8_t y, enum fontAlignment alignment) {  

  /*
  *   TODO:
  *     Add font alignment feature
  */

  SDL_Rect sourceRect;
  
  sourceRect.h = charHeight;
  sourceRect.w = charWidth;

  uint_fast16_t i = 0;
  while(text[i] != '\0') {
    
    if (isdigit(text[i])) {
      // Digit (0 - 9)

      sourceRect.y = 2 * charHeight;
      sourceRect.x = (text[i] - '0') * charWidth;

    } else if (isalpha(text[i])) {
      // Alpha (A - Z, a - z)
      
      if (!islower(text[i])) {
        // Lower case alpha (a - z)
        
        sourceRect.y = 0;
        sourceRect.x = (text[i] - 'A') * charWidth;
      
      } else {
        // Upper case alpha (A - Z)

        sourceRect.y = charHeight;
        sourceRect.x = (text[i] - 'a') * charWidth;
      
      }
    } else {
      // Not alphanumeric
      
      sourceRect.y = 2 * charHeight;
      
      switch (text[i]) {
        case '.':
          sourceRect.x = 10 * charWidth;
          break;
        
        case ',':
          sourceRect.x = 11 * charWidth;
          break;
        
        case ':':
          sourceRect.x = 12 * charWidth;
          break;
        
        case ';':
          sourceRect.x = 13 * charWidth;
          break;
        
        case '-':
          sourceRect.x = 14 * charWidth;
          break;

        case '!':
          sourceRect.x = 15 * charWidth;
          break;
        
        default:
          // '?'
          sourceRect.x = 16 * charWidth;
          break;
      
      }
    }
    
    // Draw the character
    blit(app, fontTexture, &sourceRect, x, y, charWidth, charHeight);
    
    // Increment
    x+=charWidth;
    i++;
  }

}
