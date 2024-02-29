#ifndef SDL_VULKAN_RENDERER
#define SDL_VULKAN_RENDERER

#pragma once

#include "SDLVulkanFramework.h"
#include "VulkanRenderer.h"
#include <SDL2/SDL_vulkan.h>

namespace Warlock
{

struct SDLVulkanRenderer : VulkanRenderer
{
  SDLVulkanFramework* framework;

  SDLVulkanRenderer( SDLVulkanFramework* framework );

  virtual void configure_window( Window window );
};

}; // namespace Warlock

#endif // SDL_VULKAN_RENDERER
