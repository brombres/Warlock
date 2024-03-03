#ifndef BALEFIRE_WINDOW_SDL_H
#define BALEFIRE_WINDOW_SDL_H

#pragma once

#include <SDL2/SDL.h>
#include "Balefire/Core/Window.h"

namespace BALEFIRE
{
  struct WindowSDL : Window
  {
    SDL_Window* sdl_window;

    WindowSDL( SDL_Window* sdl_window ) : sdl_window(sdl_window) {}
  };
};

#endif // BALEFIRE_WINDOW_SDL_H
