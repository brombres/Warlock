#ifndef SDL_VULKAN_DISPLAY
#define SDL_VULKAN_DISPLAY

#pragma once

#include "SDLDisplay.h"

struct SDLVulkanDisplay : SDLDisplay
{
  ~SDLVulkanDisplay();
  virtual void configure();
};

#endif // SDL_VULKAN_DISPLAY
