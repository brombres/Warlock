#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H

#pragma once

#include "Renderer.h"

#include <vulkan/vulkan.h>

namespace Warlock
{

struct VulkanRenderer : Renderer
{
  // Adapted from: https://vkguide.dev
	VkInstance               instance;
	VkDebugUtilsMessengerEXT debug_messenger;
	VkPhysicalDevice         gpu;
	VkDevice                 device;
	VkSurfaceKHR             surface;
};

static const char* vkResult_to_c_string( VkResult result );

}; // namespace Warlock

#endif // VULKAN_RENDERER_H
