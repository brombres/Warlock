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

    std::vector<std::string>                configuration_phases;
    std::unordered_map<std::string,Action*> actions;

    VkSurfaceKHR        surface;
    VkExtent2D          surface_size;
    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    VkSurfaceFormatKHR       swapchain_surface_format;
    vkb::Swapchain           swapchain;
	  std::vector<VkImage>     swapchain_images;
    std::vector<VkImageView> swapchain_image_views;

    Context( VkSurfaceKHR surface );

    virtual ~Context();

    virtual void configure_actions();

    virtual void add_configuration_action( std::string phase, Action* action );
    virtual void add_event_handler( std::string event, Action* action );
    virtual bool configure();
    virtual void deactivate();
    virtual void deactivate( std::string event );
    virtual bool dispatch_event( std::string event );
    virtual void recreate_swapchain();
    virtual void set_configuration_action( std::string phase, Action* action );
    virtual void set_event_handler( std::string event, Action* action );
  };
};
