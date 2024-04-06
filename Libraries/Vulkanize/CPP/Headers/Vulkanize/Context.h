#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#include "Vulkanize.h"
#include "Vulkanize/Image.h"

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
    // PROPERTIES
    bool configured = false;

    std::vector<std::string>                   phases;
    std::unordered_map<std::string,Operation*> operations;

    VkSurfaceKHR        surface;
    VkExtent2D          surface_size;
    vkb::PhysicalDevice physical_device;
    vkb::Device         device;
    vkb::DispatchTable  device_dispatch;

    VkSurfaceFormatKHR         swapchain_surface_format;
    vkb::Swapchain             swapchain;
    bool                       swapchain_created = false;
	  std::vector<VkImage>       swapchain_images;
    std::vector<VkImageView>   swapchain_image_views;
    VKZ::Image                 depth_stencil;
    std::vector<VkFramebuffer> framebuffers;

    uint32_t graphics_QueueFamilyIndex;
    uint32_t present_QueueFamilyIndex;
    VkQueue  graphics_queue;
    VkQueue  present_queue;

    VkRenderPass     render_pass;

    VkPipelineLayout pipeline_layout;
    VkPipeline       graphics_pipeline;

    VkCommandPool                command_pool;
    std::vector<VkCommandBuffer> command_buffers;
    VkCommandBuffer              cmd;

    VkSemaphore image_available_semaphore;
    VkSemaphore rendering_finished_semaphore;

    std::vector<VkFence> fences;

    // METHODS
    Context( VkSurfaceKHR surface );

    virtual ~Context();

    virtual void configure_operations();

    virtual void add_operation( std::string phase, Operation* operation );
    virtual bool activate( const std::string phase );
    virtual bool configure();
    virtual void deactivate( const std::string phase );
    virtual void destroy();
    virtual bool dispatch_event( std::string phase, std::string event, bool reverse_order=false );
    virtual bool execute( std::string phase );
    virtual int  find_memory_type( uint32_t typeFilter, VkMemoryPropertyFlags properties );
    virtual void recreate_swapchain();
    virtual void set_operation( std::string phase, Operation* operation );

    static bool _phase_begins_with( const std::string& phase, const std::string& other );
  };
};
