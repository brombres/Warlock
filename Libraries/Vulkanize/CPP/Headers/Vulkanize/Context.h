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

#define VKZ_EVENT_CONFIGURE    1
#define VKZ_EVENT_EXECUTE      2
#define VKZ_EVENT_DEACTIVATE   3
#define VKZ_EVENT_SURFACE_LOST 4

namespace VKZ
{
  struct Context
  {
    bool configured = false;

    std::vector<std::string>                   phases;
    std::unordered_map<std::string,Operation*> operations;

    VkSurfaceKHR        surface;
    VkExtent2D          surface_size;
    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    VkSurfaceFormatKHR       swapchain_surface_format;
    vkb::Swapchain           swapchain;
    bool                     swapchain_created = false;
	  std::vector<VkImage>     swapchain_images;
    std::vector<VkImageView> swapchain_image_views;

    Context( VkSurfaceKHR surface );

    virtual ~Context();

    virtual void configure_operations();

    virtual void add_operation( std::string phase, Operation* operation );
    virtual bool configure();
    virtual void deactivate();
    virtual bool dispatch_event( std::string phase, std::string event, bool reverse_order=false );
    virtual bool execute( std::string phase );
    virtual void recreate_swapchain();
    virtual void set_operation( std::string phase, Operation* operation );

    static bool _phase_begins_with( const std::string& phase, const std::string& other );
  };
};
