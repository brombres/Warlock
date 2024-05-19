#include "Balefire/SDL/WindowFrameworkContextSDL.h"
using namespace BALEFIRE;

WindowFrameworkContextSDL::WindowFrameworkContextSDL( Window* window, SDL_Window* sdl_window )
  : WindowFrameworkContext(window), sdl_window(sdl_window)
{
  sdl_window_id = SDL_GetWindowID( sdl_window );
}

WindowFrameworkContextSDL::~WindowFrameworkContextSDL()
{
  if (sdl_window)
  {
    SDL_DestroyWindow( sdl_window );
    sdl_window = nullptr;
  }
}

