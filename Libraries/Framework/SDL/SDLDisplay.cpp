#include "SDLDisplay.h"
using namespace Warlock;

Window SDLDisplay::create_window()
{
  return Window(
    new SDLWindowData(
      SDL_CreateWindow(
        "Warlock Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        window_creation_flags()
      )
    )
  );
}

SDL_WindowFlags SDLDisplay::window_creation_flags()
{
  return (SDL_WindowFlags)SDL_WINDOW_SHOWN;
}
