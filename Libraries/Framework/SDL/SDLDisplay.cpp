#include "SDLDisplay.h"
using namespace Warlock;

Window SDLDisplay::create_window()
{
  SDL_WindowFlags flags = window_creation_flags();
  if (flags & SDL_WINDOW_VULKAN) printf("SDL_WINDOW_VULKAN:%08x\n",SDL_WINDOW_SHOWN);
  if (flags & SDL_WINDOW_SHOWN)  printf("SDL_WINDOW_SHOWN: %08x\n",SDL_WINDOW_VULKAN);

  return Window(
    new SDLWindowData(
      SDL_CreateWindow(
        "Warlock Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        768,
        //window_creation_flags()
        SDL_WINDOW_SHOWN
      )
    )
  );
}

SDL_WindowFlags SDLDisplay::window_creation_flags()
{
  return (SDL_WindowFlags)SDL_WINDOW_SHOWN;
}
