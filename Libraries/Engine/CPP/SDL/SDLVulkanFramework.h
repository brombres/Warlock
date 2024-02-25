#ifndef SDL_VULKAN_DISPLAY
#define SDL_VULKAN_DISPLAY

#pragma once

#include "SDLFramework.h"
#include <SDL2/SDL_vulkan.h>

namespace Warlock
{

struct SDLVulkanFramework : SDLFramework
{
  ~SDLVulkanFramework();
  virtual void            configure();
  virtual SDL_WindowFlags window_creation_flags();
};

}; // namespace Warlock

#endif // SDL_VULKAN_DISPLAY
