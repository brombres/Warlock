#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct ConfigureGFXLineListColor : VKZ::ConfigureGraphicsPipeline
  {
    ConfigureGFXLineListColor( VKZ::GraphicsPipeline* graphics_pipeline )
      : VKZ::ConfigureGraphicsPipeline(graphics_pipeline) {}
    virtual void on_configure();
  };
};
