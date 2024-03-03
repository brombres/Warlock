#include "Balefire/SDL/BalefireSDL.h"
#include "Balefire/SDL/WindowSDLVulkan.h"
using namespace BALEFIRE;

void BalefireSDL::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
}

WindowID BalefireSDL::create_window( String name )
{
  SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN);

  Window* window = new WindowSDL(
    SDL_CreateWindow(
      name,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1024,
      768,
      flags
    )
  );

  window->id = windows.add( window );
  renderer->configure_window( window );

  return window->id;
}
