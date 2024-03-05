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
    RendererVulkan*  renderer;

    VkPhysicalDevice gpu;
    VkDevice         device;
    VkSurfaceKHR     surface;

    VkSwapchainKHR           swapchain;
    VkFormat                 swapchain_image_format;
	  std::vector<VkImage>     swapchain_images;
    std::vector<VkImageView> swapchain_image_views;

    VkQueue         graphics_queue;
    uint32_t        graphics_queue_family;
    VkCommandPool   command_pool;
    VkCommandBuffer main_command_buffer;

    VkRenderPass               render_pass;
    std::vector<VkFramebuffer> framebuffers;

    VkSemaphore semaphore_present, semaphore_render;
    VkFence     render_fence;

    WindowRendererContextVulkan( RendererVulkan* renderer ) : renderer(renderer) {}
    virtual ~WindowRendererContextVulkan();
  };
};

#endif // BALEFIRE_WINDOW_RENDERER_CONTEXT_VULKAN_H
