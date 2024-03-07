#ifndef BALEFIRE_RENDERER_VULKAN_H
#define BALEFIRE_RENDERER_VULKAN_H

#pragma once

#include <iostream>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"

#define VK_CHECK(cmd)                                            \
	{                                                              \
		VkResult err = cmd;                                          \
		if ((err=cmd))                                               \
		{                                                            \
      fprintf( stderr, "[ERROR] Vulkan error: %s.\n", RendererVulkan::vkResult_to_c_string(err) ); \
      abort();                                                   \
		}                                                            \
	}

namespace BALEFIRE
{
  struct RendererVulkan : Renderer
  {
    Framework*               framework = nullptr;
    vkb::Instance            vkb_instance;
    VkInstance               vulkan_instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    bool                     configured = false;

    RendererVulkan( Framework* framework ) : framework(framework) {}
    virtual ~RendererVulkan();
    virtual void configure();
    virtual void configure_window( Window* window );

    static const char* vkResult_to_c_string( VkResult result );
  };
};

#endif // BALEFIRE_RENDERER_VULKAN_H
