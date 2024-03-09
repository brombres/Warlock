#ifndef BALEFIRE_RENDERER_VULKAN_H
#define BALEFIRE_RENDERER_VULKAN_H

#pragma once

#include <cstdio>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"

#define VK_CHECK(stage,cmd)                                      \
	{                                                              \
		VkResult err = cmd;                                          \
		if ((err=cmd))                                               \
		{                                                            \
      fprintf( stderr,                                           \
          "[ERROR] Balefire Vulkan: error %s (%s).\n",           \
          stage, RendererVulkan::vkResult_to_c_string(err) );    \
      abort();                                                   \
		}                                                            \
	}

namespace BALEFIRE
{
  struct RendererVulkan : Renderer
  {
    Framework*               framework = nullptr;
    vkb::Instance            vulkan_instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    bool                     configured = false;

    RendererVulkan( Framework* framework ) : framework(framework) {}
    virtual ~RendererVulkan();
    virtual void configure();
    virtual void configure_window( Window* window );

    static const char* vkResult_to_c_string( VkResult result );
  };

  template <typename DataType>
  DataType vkb_require( vkb::Result<DataType> result )
  {
    if ( !result )
    {
      fprintf( stderr, "[ERROR] %s\n", result.error().message().c_str() );
      abort();
    }
    return result.value();
  }
};

#endif // BALEFIRE_RENDERER_VULKAN_H
