#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "Balefire/Core/WindowRenderContext.h"
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
    //vkb::DispatchTable device_dispatch;

    VkExtent2D     swapchain_size;
    vkb::Swapchain swapchain;

    uint32_t graphics_QueueFamilyIndex;
    uint32_t present_QueueFamilyIndex;
    VkQueue  graphics_queue;
    VkQueue  present_queue;

    //VkRenderPass     render_pass;

    //VkPipelineLayout pipeline_layout;
    //VkPipeline       graphics_pipeline;

    ////VkFormat                 swapchain_image_format;
	  //std::vector<VkImage>       swapchain_images;
    //std::vector<VkImageView>   swapchain_image_views;
    //std::vector<VkFramebuffer> framebuffers;

    //VkCommandPool                command_pool;
    //std::vector<VkCommandBuffer> command_buffers;

    //std::vector<VkSemaphore> available_semaphores;
    //std::vector<VkSemaphore> finished_semaphores;
    //std::vector<VkFence> in_flight_fences;
    //std::vector<VkFence> image_in_flight;

    //size_t current_frame = 0;


    //VkSemaphore present_semaphore, render_semaphore;
    //VkFence*    render_fences;

    //int frame_count = 0;  // FIXME

    // CONSTRUCTORS
    WindowRenderContextVulkan( Window* window, RendererVulkan* renderer )
      : WindowRenderContext(window), renderer(renderer) {}
    virtual ~WindowRenderContextVulkan();

    // METHODS
    virtual void configure();
    virtual void render();

    void _configure_device();
    void _configure_swapchain();
    void _configure_queues();
    void _configure_render_pass();
    void _configure_graphics_pipeline();
    void _configure_framebuffers();
    void _configure_command_pool();
    void _configure_command_buffers();
    void _configure_sync_objects();
    void _recreate_swapchain();

    VkShaderModule _create_shader_module( const Byte* code, int count );
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_VULKAN_H
