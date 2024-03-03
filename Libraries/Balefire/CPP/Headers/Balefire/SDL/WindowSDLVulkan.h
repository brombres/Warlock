#ifndef BALEFIRE_WINDOW_SDL_VULKAN_H
#define BALEFIRE_WINDOW_SDL_VULKAN_H

#pragma once

#include <vulkan/vulkan.h>
#include "Balefire/SDL/WindowSDL.h"

namespace BALEFIRE
{
  struct WindowSDLVulkan : WindowSDL
  {
    VkPhysicalDevice         vulkan_gpu;
    VkDevice                 vulkan_device;
    VkSurfaceKHR             vulkan_surface;

    WindowSDLVulkan( SDL_Window* sdl_window ) : WindowSDL(sdl_window) {}
    virtual ~WindowSDLVulkan() {}
  };
};

#endif // BALEFIRE_WINDOW_SDL_VULKAN_H
