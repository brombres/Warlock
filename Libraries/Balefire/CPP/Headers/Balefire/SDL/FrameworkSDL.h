#ifndef BALEFIRE_FRAMEWORK_SDL_H
#define BALEFIRE_FRAMEWORK_SDL_H

#include <SDL2/SDL.h>
#include "Balefire/Core/Framework.h"

namespace BALEFIRE
{
  struct FrameworkSDL : Framework
  {
    virtual void configure();
    virtual WindowID create_window( String name );
  };
};

#endif // BALEFIRE_FRAMEWORK_SDL_H
