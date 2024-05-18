#ifndef BALEFIRE_FRAMEWORK_SDL_VULKAN_H
#define BALEFIRE_FRAMEWORK_SDL_VULKAN_H

#include <vector>
#include <SDL2/SDL_vulkan.h>
#include "Balefire/SDL/FrameworkSDL.h"

namespace BALEFIRE
{
  struct FrameworkSDLVulkan : FrameworkSDL
  {
    virtual void    configure();
    virtual Window* create_window( int index, std::string name );
    virtual void    render( Window* window, CmdData* data );
    virtual void    update_pixel_size( Window* window );
  };
};

#endif // BALEFIRE_FRAMEWORK_SDL_VULKAN_H
