#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct ConfigureDescriptors : VKZ::ConfigureDescriptors
  {
    ConfigureDescriptors( VKZ::Descriptors* descriptors )
      : VKZ::ConfigureDescriptors(descriptors) {}

    void on_configure() override;
  };
};
