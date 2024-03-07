#ifndef BALEFIRE_FRAMEWORK_SDL_VULKAN_H
#define BALEFIRE_FRAMEWORK_SDL_VULKAN_H

#include <SDL2/SDL_vulkan.h>
#include "Balefire/SDL/FrameworkSDL.h"

namespace BALEFIRE
{
  struct FrameworkSDLVulkan : FrameworkSDL
  {
    virtual void     configure();
    virtual WindowID create_window( String name );
    virtual void     render( Window* window );
  };
};

#endif // BALEFIRE_FRAMEWORK_SDL_VULKAN_H
