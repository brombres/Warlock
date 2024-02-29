#include "SDLFramework.h"
#include "SDLVulkanRenderer.h"
using namespace Warlock;

SDLFramework::~SDLFramework()
{
  while (windows.count)
  {
    SDL_DestroyWindow( windows.remove_last() );
  }
}

Window SDLFramework::create_window()
{
  SDL_WindowFlags flags = window_creation_flags();
  if (flags & SDL_WINDOW_VULKAN) printf("SDL_WINDOW_VULKAN:%08x\n",SDL_WINDOW_SHOWN);
  if (flags & SDL_WINDOW_SHOWN)  printf("SDL_WINDOW_SHOWN: %08x\n",SDL_WINDOW_VULKAN);


  int window_id =
    windows.add(
      SDL_CreateWindow(
        "Warlock Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        768,
        //window_creation_flags()
        SDL_WINDOW_SHOWN
      )
    );
  renderer->configure_window( window_id );
  return window_id;
}

SDL_WindowFlags SDLFramework::window_creation_flags()
{
  return (SDL_WindowFlags)SDL_WINDOW_SHOWN;
}
