#ifndef BALEFIRE_RENDERER_VULKAN_H
#define BALEFIRE_RENDERER_VULKAN_H

#pragma once

#include <cstdio>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"
#include "Balefire/Balefire.h"
#include "Vulkanize/Vulkanize.h"

namespace BALEFIRE
{
  struct Vec4
  {
    float r;
    float g;
    float b;
    float a;

    Vec4() : r(0), g(0), b(0), a(1) {}
    Vec4( float r, float g, float b, float a=1.0 ) : r(r), g(g), b(b), a(a) {}
  };
};

#include "Balefire/Vulkan/VulkanContext.h"

namespace BALEFIRE
{
  struct RendererVulkan : Renderer
  {
    VKZ::Vulkanize             vulkanize;
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

#include "Balefire/Vulkan/Vertex.h"
#include "Balefire/Vulkan/VertexDescription.h"
#include "Balefire/Vulkan/Configure/ConfigureBalefireDescriptors.h"
#include "Balefire/Vulkan/Configure/ConfigureGFXLineListColor.h"
#include "Balefire/Vulkan/Configure/ConfigureGFXTriangleListColor.h"
#include "Balefire/Vulkan/WindowRenderContextVulkan.h"

#endif // BALEFIRE_RENDERER_VULKAN_H
