#ifndef BALEFIRE_SDL_VULKAN_H
#define BALEFIRE_SDL_VULKAN_H

#include <SDL2/SDL_vulkan.h>
#include "Balefire/SDL/BalefireSDL.h"

namespace BALEFIRE
{
  struct BalefireSDLVulkan : BalefireSDL
  {
    virtual void configure();
    virtual WindowID create_window( String name );
  };
};

#endif // BALEFIRE_SDL_VULKAN_H
