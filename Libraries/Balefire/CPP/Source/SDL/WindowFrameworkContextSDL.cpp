#include "Balefire/SDL/WindowFrameworkContextSDL.h"
using namespace BALEFIRE;

WindowFrameworkContextSDL::~WindowFrameworkContextSDL()
{
  if (sdl_window)
  {
    SDL_DestroyWindow( sdl_window );
    sdl_window = nullptr;
  }
}
