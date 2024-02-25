#ifndef SDL_DISPLAY
#define SDL_DISPLAY

#pragma once

#include <SDL2/SDL.h>

#include "Framework.h"
#include "ResourceBank.h"

namespace Warlock
{

struct SDLFramework : Framework
{
  ResourceBank<Window,SDL_Window*> windows;

  ~SDLFramework();

  virtual Window          create_window();
  virtual SDL_WindowFlags window_creation_flags();
};

}; // namespace Warlock

#endif // SDL_DISPLAY
