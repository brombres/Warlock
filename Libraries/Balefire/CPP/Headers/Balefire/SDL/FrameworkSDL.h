#ifndef BALEFIRE_FRAMEWORK_SDL_H
#define BALEFIRE_FRAMEWORK_SDL_H

#include <string>
#include <SDL2/SDL.h>
#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct FrameworkSDL : Framework
  {
    virtual void configure();
    virtual WindowID create_window( std::string name );
    virtual bool     handle_events();
  };
};

#endif // BALEFIRE_FRAMEWORK_SDL_H
