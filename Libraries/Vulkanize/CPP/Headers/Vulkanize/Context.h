#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#include "Vulkanize.h"

#define VKZ_CONFIGURE_DEVICE             "device"
#define VKZ_CONFIGURE_FORMATS            "formats"
#define VKZ_CONFIGURE_SURFACE_SIZE       "surface_size"
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

namespace VKZ
{
  struct Context
  {
    bool configured = false;

    std::vector<std::string>                   configuration_phases;
    std::unordered_map<std::string,Procedure*> procedures;

    VkSurfaceKHR        surface;
    VkExtent2D          surface_size;
    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    VkSurfaceFormatKHR  swapchain_surface_format;

    Context( VkSurfaceKHR surface );

    virtual ~Context();

    virtual void configure_procedures();

    virtual void add_configuration_phase( std::string phase, Procedure* procedure );
    virtual void add_render_phase( std::string phase, Procedure* procedure );
    virtual bool configure();
    virtual bool configure( std::string phase );
    virtual void destroy();
    virtual void destroy( std::string phase );
    virtual void recreate_swapchain();
    virtual bool render( std::string phase );
    virtual void set_configuration_phase( std::string phase, Procedure* procedure );
    virtual void set_render_phase( std::string phase, Procedure* procedure );
  };
};
