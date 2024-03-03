#ifndef BALEFIRE_RENDERER_VULKAN_H
#define BALEFIRE_RENDERER_VULKAN_H

#pragma once

#include <vulkan/vulkan.h>
#include "Balefire/Core/Balefire.h"
#include "Balefire/Core/Renderer.h"

namespace BALEFIRE
{
  struct RendererVulkan : Renderer
  {
    Balefire*                balefire = nullptr;
    VkInstance               instance;
    VkDebugUtilsMessengerEXT debug_messenger;

    RendererVulkan( Balefire* balefire ) : balefire(balefire) {}
    virtual ~RendererVulkan() {}
    virtual void configure();
  };
};

#endif // BALEFIRE_RENDERER_VULKAN_H
