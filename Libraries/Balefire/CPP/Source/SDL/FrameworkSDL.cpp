#include "Balefire/SDL/FrameworkSDL.h"
using namespace BALEFIRE;

void FrameworkSDL::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
}

WindowID FrameworkSDL::create_window( String name )
{
  return 0;
}
