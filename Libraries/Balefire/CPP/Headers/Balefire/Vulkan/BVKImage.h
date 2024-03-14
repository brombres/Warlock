#ifndef BALEFIRE_BVK_IMAGE_H
#define BALEFIRE_BVK_IMAGE_H

#pragma once

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

namespace BALEFIRE
{
  struct WindowRenderContextVulkan;

  struct BVKImage
  {
    WindowRenderContextVulkan* context;
    VkFormat       format;
    VkImage        image;
    VkDeviceMemory memory;
    VkImageView    view;
    bool           image_created = false;
    bool           memory_allocated = false;
    bool           view_created = false;
    bool           exists = false;

    BVKImage();
    BVKImage( WindowRenderContextVulkan* context, int width, int height, VkFormat format,
              VkImageUsageFlags usage, VkImageAspectFlags aspect,
              VkMemoryPropertyFlags properties=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
              VkImageTiling tiling=VK_IMAGE_TILING_OPTIMAL );
    ~BVKImage();

    bool create( WindowRenderContextVulkan* context, int width, int height, VkFormat format,
                 VkImageUsageFlags usage, VkImageAspectFlags aspect,
                 VkMemoryPropertyFlags properties=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 VkImageTiling tiling=VK_IMAGE_TILING_OPTIMAL );
    void destroy();
  };
};

#endif // BALEFIRE_BVK_IMAGE_H
