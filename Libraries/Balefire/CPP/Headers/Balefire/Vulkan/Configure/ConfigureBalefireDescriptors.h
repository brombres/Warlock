#pragma once

#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct ConfigureBalefireDescriptors : VKZ::ConfigureDescriptors
  {
    ConfigureBalefireDescriptors( VKZ::OldDescriptors* descriptors )
      : VKZ::ConfigureDescriptors(descriptors) {}

    void on_configure() override;
  };
};
