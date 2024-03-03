#include "Balefire/SDL/WindowFrameworkContextSDL.h"
using namespace BALEFIRE;

WindowFrameworkContextSDL::~WindowFrameworkContextSDL()
{
  SDL_DestroyWindow( sdl_window );
  sdl_window = nullptr;
}
