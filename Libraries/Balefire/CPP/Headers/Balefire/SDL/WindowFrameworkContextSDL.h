#ifndef BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_SDL_H
#define BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_SDL_H

#pragma once

#include <SDL2/SDL.h>
#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowFrameworkContextSDL : WindowFrameworkContext
  {
    SDL_Window* sdl_window = nullptr;
    Uint32      sdl_window_id;

    WindowFrameworkContextSDL( Window* window, SDL_Window* sdl_window );
    virtual ~WindowFrameworkContextSDL();
  };
};

#endif // BALEFIRE_WINDOW_FRAMEWORK_CONTEXT_SDL_H
