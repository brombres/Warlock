#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#include "Vulkanize.h"
#include "Vulkanize/Image.h"

namespace VKZ
{
  struct Vulkanize;

  struct SPIRVBinary
  {
    int       size; // number of bytes in SPIR-V binary
    uint32_t* code; // SPIR-V words
  };

  struct Context : OperationManager
  {
    // PROPERTIES
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

    // Rendering
    uint32_t swap_index;

    // METHODS
    Context( VkSurfaceKHR surface );

    virtual ~Context();

    virtual VkShaderModule compile_shader( VKZ::Shader type, const std::string& filename,
                                           const std::string& shader_source );
    virtual SPIRVBinary    compile_shader_to_spirv( int stage, const char* filename, const char* shader_source );

    virtual void configure_operations();

    virtual void destroy();
    virtual int  find_memory_type( uint32_t typeFilter, VkMemoryPropertyFlags properties );
    virtual void recreate_swapchain();
  };
};
