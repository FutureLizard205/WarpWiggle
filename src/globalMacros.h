#pragma once

#define macro_errorMessage(message) \
  SDL_LogError(SDL_LOG_CATEGORY_ERROR, message); \
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);

#define macro_error(condition, message) \
  if (condition) { \
    macro_errorMessage(message) \
    return EXIT_FAILURE; \
  }
