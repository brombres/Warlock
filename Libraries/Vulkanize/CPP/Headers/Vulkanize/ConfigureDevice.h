#pragma once

#include "Vulkanize/Vulkanize.h"

namespace VKZ
{
  struct ConfigureDevice : Component
  {
    Context* context;
    int major_version;
    int minor_version;
    VkPhysicalDeviceFeatures         required_features      = {};
    VkPhysicalDeviceVulkan11Features required_features_v1_1 = {};
    VkPhysicalDeviceVulkan12Features required_features_v1_2 = {};
    VkPhysicalDeviceVulkan13Features required_features_v1_3 = {};

    ConfigureDevice( Context* context, int major_version=1, int minor_version=2 );
    virtual void on_configure();
    virtual void on_destroy();

    virtual const char* phase() { return VKZ_CONFIGURE_DEVICE; }
  };
};
