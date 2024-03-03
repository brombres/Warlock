#ifndef BALEFIRE_RENDERER_VULKAN_H
#define BALEFIRE_RENDERER_VULKAN_H

#pragma once

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"

namespace BALEFIRE
{
  struct RendererVulkan : Renderer
  {
    Framework*               framework = nullptr;
    vkb::Instance            vkb_instance;
    VkInstance               vulkan_instance;
    VkDebugUtilsMessengerEXT vulkan_debug_messenger;

    RendererVulkan( Framework* framework ) : framework(framework) {}
    virtual ~RendererVulkan() {}
    virtual void configure();
    virtual void configure_window( Window* window );
  };
};

#endif // BALEFIRE_RENDERER_VULKAN_H
