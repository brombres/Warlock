#ifndef BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H
#define BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H

#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "Balefire/Core/WindowRendererContext.h"
#include "Balefire/Vulkan/RendererVulkan.h"

namespace BALEFIRE
{
  struct WindowRendererContextVulkan : WindowRendererContext
  {
    // PROPERTIES
    RendererVulkan*  renderer;

    VkPhysicalDevice gpu;
    VkDevice         device;
    VkSurfaceKHR     surface;

    VkSwapchainKHR           swapchain;
    VkFormat                 swapchain_image_format;
	  std::vector<VkImage>     swapchain_images;
    std::vector<VkImageView> swapchain_image_views;

    uint32_t         graphics_queue_family;
    VkQueue          graphics_queue;
    VkQueue          present_queue;
    VkCommandPool    command_pool;
    VkCommandBuffer* command_buffers = nullptr;

    VkRenderPass               render_pass;
    std::vector<VkFramebuffer> framebuffers;

    VkSemaphore present_semaphore, render_semaphore;
    VkFence*    render_fences;

    int frame_count = 0;  // FIXME

    // CONSTRUCTORS
    WindowRendererContextVulkan( Window* window, RendererVulkan* renderer )
      : WindowRendererContext(window), renderer(renderer) {}
    virtual ~WindowRendererContextVulkan();

    // METHODS
    virtual void configure();
    virtual void render();
  };
};

#endif // BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H
