#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "Balefire/Core/WindowRenderContext.h"
#include "Balefire/Vulkan/BVKImage.h"
#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct WindowRenderContextVulkan : WindowRenderContext
  {
    const int MAX_FRAMES_IN_FLIGHT = 2;

    // PROPERTIES
    RendererVulkan*  renderer;
    VkSurfaceKHR     surface = nullptr;

    vkb::PhysicalDevice  physical_device;
    vkb::Device          device;
    vkb::DispatchTable   device_dispatch;

    VkExtent2D               swapchain_size;
    vkb::Swapchain           swapchain;
	  std::vector<VkImage>     swapchain_images;
    std::vector<VkImageView> swapchain_image_views;

    uint32_t graphics_QueueFamilyIndex;
    uint32_t present_QueueFamilyIndex;
    VkQueue  graphics_queue;
    VkQueue  present_queue;

    BVKImage depth_buffer;

    VkRenderPass render_pass;

    //VkPipelineLayout pipeline_layout;
    //VkPipeline       graphics_pipeline;

    ////VkFormat                 swapchain_image_format;
    std::vector<VkFramebuffer> framebuffers;

    VkCommandPool                command_pool;
    std::vector<VkCommandBuffer> command_buffers;
    VkCommandBuffer              cmd;

    VkSemaphore image_available_semaphore;
    VkSemaphore rendering_finished_semaphore;

    std::vector<VkFence> fences;

    uint32_t frame_index;
    //size_t current_frame = 0;
    //int frame_count = 0;  // FIXME

    // CONSTRUCTORS
    WindowRenderContextVulkan( Window* window, RendererVulkan* renderer )
      : WindowRenderContext(window), renderer(renderer) {}
    virtual ~WindowRenderContextVulkan();

    // METHODS
    virtual void configure();
    int          find_memory_type( uint32_t typeFilter, VkMemoryPropertyFlags properties );
    virtual void render();

    void _configure_device();
    void _configure_swapchain();
    void _configure_queues();
    void _configure_graphics_pipeline();
    void _configure_depth_stencil();
    void _configure_render_pass();
    void _configure_framebuffers();
    void _configure_command_pool();
    void _configure_command_buffers();
    void _configure_semaphores();
    void _configure_fences();
    void _create_semaphore( VkSemaphore *semaphore );
    bool _find_supported_depth_format( VkFormat* depth_format );
    void _recreate_swapchain();

    VkShaderModule _create_shader_module( const Byte* code, int count );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
