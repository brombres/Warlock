#ifndef BALEFIRE_SDL_H
#define BALEFIRE_SDL_H

#include <SDL2/SDL.h>
#include "Balefire/Core/Balefire.h"

namespace BALEFIRE
{
  struct BalefireSDL : Balefire
  {
    virtual void configure();
    virtual WindowID create_window( String name );
  };
};

#endif // BALEFIRE_SDL_H
