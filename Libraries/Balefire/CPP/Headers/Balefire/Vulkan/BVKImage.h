#ifndef BALEFIRE_BVK_IMAGE_H
#define BALEFIRE_BVK_IMAGE_H

#pragma once

#include <vulkan/vulkan.h>

namespace BALEFIRE
{
  struct BVKImage
  {
    VkImage        image;
    VkDeviceMemory memory;
    VkImageView    view;

    BVKImage( int width, int height, VkFormat format,
              VkImageUsageFlags usage, VkImageAspectFlags aspect,
              VkMemoryPropertyFlags properties=VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
              VkImageTiling tiling=VK_IMAGE_TILING_OPTIMAL );

    void destroy();
  };
};

#endif // BALEFIRE_BVK_IMAGE_H
