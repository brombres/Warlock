#ifndef SDL_DISPLAY
#define SDL_DISPLAY

#pragma once

#include <SDL2/SDL.h>

#include "Display.h"
#include "Window.h"

namespace Warlock
{

struct SDLDisplay : Display
{
  virtual Window          create_window();
  virtual SDL_WindowFlags window_creation_flags();
};

struct SDLWindowData : WindowData
{
  SDL_Window* sdl_window = nullptr;

  SDLWindowData( SDL_Window* sdl_window ) { this->sdl_window = sdl_window; }
  ~SDLWindowData() { if (sdl_window) SDL_DestroyWindow(sdl_window); }
};

}; // namespace Warlock

#endif // SDL_DISPLAY
