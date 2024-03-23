#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#define VKZ_CONFIGURE_DEVICE             "device"
#define VKZ_CONFIGURE_SWAPCHAIN          "swapchain"
#define VKZ_CONFIGURE_QUEUES             "queues"
#define VKZ_CONFIGURE_DEPTH_STENCIL      "depth_stencil"
#define VKZ_CONFIGURE_RENDER_PASS        "render_pass"
#define VKZ_CONFIGURE_GRAPHICS_PIPELINES "graphics_pipelines"
#define VKZ_CONFIGURE_FRAMEBUFFERS       "framebuffers"
#define VKZ_CONFIGURE_COMMAND_POOL       "command_pool"
#define VKZ_CONFIGURE_COMMAND_BUFFERS    "command_buffers"
#define VKZ_CONFIGURE_SEMAPHORES         "semaphores"
#define VKZ_CONFIGURE_FENCES             "fences"

namespace VULKANIZE
{
  struct Context
  {
    bool                configured = false;

    std::vector<std::string> configuration_steps;
    VkSurfaceKHR             surface;
    vkb::PhysicalDevice      physical_device;
    vkb::Device              device;
    vkb::DispatchTable       device_dispatch;

    Context( VkSurfaceKHR surface );

    virtual ~Context();
    virtual bool configure();
    virtual bool _configure_device();
    virtual bool destroy();

    virtual void set_configuration_steps( std::vector<std::string>& steps );
  };
};
