#ifndef SDL_VULKAN_DISPLAY
#define SDL_VULKAN_DISPLAY

#pragma once

#include "SDLDisplay.h"

namespace Warlock
{

struct SDLVulkanDisplay : SDLDisplay
{
  ~SDLVulkanDisplay();
  virtual void            configure();
  virtual SDL_WindowFlags window_creation_flags();
};

}; // namespace Warlock

#endif // SDL_VULKAN_DISPLAY
