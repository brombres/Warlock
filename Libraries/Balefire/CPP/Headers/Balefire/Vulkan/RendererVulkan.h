#ifndef BALEFIRE_RENDERER_VULKAN_H
#define BALEFIRE_RENDERER_VULKAN_H

#pragma once

#include <cstdio>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Renderer.h"

#define VK_LOG_ERROR(stage) fprintf( stderr, "[ERROR] Balefire Vulkan: error %s.\n", stage );

#define ON_VK_ERROR(stage,cmd,body)                              \
	{                                                              \
		VkResult err = cmd;                                          \
		if ((err=cmd))                                               \
		{                                                            \
      fprintf( stderr,                                           \
          "[ERROR] Balefire Vulkan: error %s (%s).\n",           \
          stage, RendererVulkan::vkResult_to_c_string(err) );    \
      body;                                                      \
		}                                                            \
	}

#define VK_CHECK(stage,cmd) ON_VK_ERROR(stage,cmd,abort())

namespace BALEFIRE
{
  struct RendererVulkan : Renderer
  {
    Framework*                 framework = nullptr;
    bool                       configured = false;

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
