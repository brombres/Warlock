#ifndef SDL_VULKAN_DISPLAY_MANAGER
#define SDL_VULKAN_DISPLAY_MANAGER

#pragma once

#include "SDLDisplayManager.h"

struct SDLVulkanDisplayManager : SDLDisplayManager
{
  ~SDLVulkanDisplayManager();
  virtual void configure();
};

#endif // SDL_VULKAN_DISPLAY_MANAGER
