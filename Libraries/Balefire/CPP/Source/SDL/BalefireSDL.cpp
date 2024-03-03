#include "Balefire/SDL/BalefireSDL.h"
#include "Balefire/SDL/WindowSDLVulkan.h"
using namespace BALEFIRE;

void BalefireSDL::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
}

WindowID BalefireSDL::create_window( String name )
{
  Window* window = new WindowSDL(
    SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1024,
      768,
      //window_creation_flags()
      SDL_WINDOW_SHOWN
    )
  );

  //renderer->configure_window( window_id );
  return windows.add( window );
}
