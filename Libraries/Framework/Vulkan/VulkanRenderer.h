#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H

#pragma once

#include "WarlockRenderer.h"

#include <vulkan/vulkan.h>

struct VulkanRenderer : Warlock::Renderer
{
  // Adapted from: https://vkguide.dev
};

static const char* vkResult_to_c_string( VkResult result );

#endif // VULKAN_RENDERER_H
