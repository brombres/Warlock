#include "VulkanInterface.h"
#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;

void init_vulkan_extern(Vulkan *vulkan)
{
  ////////////////////////////////////////////////////
  /////// [Screen]
  //////////////////////////////////////////
  bool test = vulkan->Create_Swapchain(false);
  vulkan->Create_ImageViews();
  vulkan->Setup_DepthStencil();
  vulkan->Create_RenderPass();
  vulkan->Create_Framebuffers();

  ///////////////////////////////////////////////////////////

  vulkan->createCommandPool();
  vulkan->createCommandBuffers();
  vulkan->create_semaphores();
  vulkan->createFences();
}

Vulkan::Vulkan()
{

}

Vulkan::~Vulkan()
{

}

////////////////////////////////////////////////////
/////// [Core]
//////////////////////////////////////////
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

extern SDL_Window *window;
extern char* window_name;

const vector<const char*> validationLayers = {
  ///has bug
  //"VK_LAYER_LUNARG_standard_validation"
};

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanReportFunc(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objType,
    uint64_t obj,
    size_t location,
    int32_t code,
    const char* layerPrefix,
    const char* msg,
    void* userData)
{
  printf("VULKAN VALIDATION: %s\n", msg);
  return VK_FALSE;
}

#include <set>

////////////////////////////////////////////////////
/////// [Screen]
//////////////////////////////////////////
#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : (x) > (hi) ? (hi) : (x))
bool Vulkan::Create_Swapchain(bool resize)
{
  /*
  int width,height = 0;
  SDL_Vulkan_GetDrawableSize(window, &width, &height);
  VkSurfaceCapabilitiesKHR surfaceCapabilities;//
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR( g_context->physical_device, g_context->surface, &surfaceCapabilities );
  width = CLAMP( width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width );
  height = CLAMP( height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height );
  g_context->swapchain_size.width = width;
  g_context->swapchain_size.height = height;

	vkb::SwapchainBuilder swapchainBuilder{ g_context->device };

	auto swapchain_build_result = swapchainBuilder
    //.set_desired_format( VK_FORMAT_B8G8R8A8_UNORM )
		.use_default_format_selection()
		.set_desired_present_mode( VK_PRESENT_MODE_FIFO_KHR )
		.set_desired_extent( width, height )
    .set_old_swapchain( swapchain )
		.build();
  vkb::destroy_swapchain( swapchain );
  swapchain = swapchain_build_result.value();
  */

  surfaceFormat = VkSurfaceFormatKHR{ g_context->swapchain.image_format, g_context->swapchain.color_space };

  swapchain_images = g_context->swapchain.get_images().value();
  swapchainImageCount = swapchain_images.size();

  return true;
}

//global createImageView
VkImageView Vulkan::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
{
  VkImageViewCreateInfo viewInfo = {};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = image;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = format;
  viewInfo.subresourceRange.aspectMask = aspectFlags;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  VkImageView imageView;
  if (vkCreateImageView(g_context->device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create texture image view!");
  }

  return imageView;
}

void Vulkan::Create_ImageViews()
{
  swapchain_image_views = g_context->swapchain.get_image_views().value();
  //swapchain_image_views.resize(swapchain_images.size());

  //for (uint32_t i = 0; i < swapchain_images.size(); i++)
  //{
  //  swapchain_image_views[i] = createImageView(swapchain_images[i], surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT);
  //}
}

VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat *depthFormat)
{
  std::vector<VkFormat> depthFormats = {
    VK_FORMAT_D32_SFLOAT_S8_UINT,
    VK_FORMAT_D32_SFLOAT,
    VK_FORMAT_D24_UNORM_S8_UINT,
    VK_FORMAT_D16_UNORM_S8_UINT,
    VK_FORMAT_D16_UNORM
  };

  for (auto& format : depthFormats)
  {
    VkFormatProperties formatProps;
    vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);
    if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
    {
      *depthFormat = format;
      return true;
    }
  }

  return false;
}

//global findMemoryType
uint32_t Vulkan::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(g_context->physical_device, &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
  {
    if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
    {
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");
}

//global createImage
void Vulkan::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
    VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image,
    VkDeviceMemory& imageMemory)
{
  VkImageCreateInfo imageInfo = {};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = width;
  imageInfo.extent.height = height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateImage(g_context->device, &imageInfo, nullptr, &image) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(g_context->device, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(g_context->device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(g_context->device, image, imageMemory, 0);
}

void Vulkan::Setup_DepthStencil()
{
  VkBool32 validDepthFormat = getSupportedDepthFormat(g_context->physical_device, &depthFormat);
  createImage(g_context->swapchain_size.width, g_context->swapchain_size.height,
      VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_TILING_OPTIMAL,
      VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
      depthImage, depthImageMemory);
  depthImageView = createImageView(depthImage, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_ASPECT_DEPTH_BIT);
}

void Vulkan::Create_RenderPass()
{
  vector<VkAttachmentDescription> attachments(2);

  attachments[0].format = surfaceFormat.format;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  attachments[1].format = depthFormat;
  attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference colorReference = {};
  colorReference.attachment = 0;
  colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depthReference = {};
  depthReference.attachment = 1;
  depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpassDescription = {};
  subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpassDescription.colorAttachmentCount = 1;
  subpassDescription.pColorAttachments = &colorReference;
  subpassDescription.pDepthStencilAttachment = &depthReference;
  subpassDescription.inputAttachmentCount = 0;
  subpassDescription.pInputAttachments = nullptr;
  subpassDescription.preserveAttachmentCount = 0;
  subpassDescription.pPreserveAttachments = nullptr;
  subpassDescription.pResolveAttachments = nullptr;

  vector<VkSubpassDependency> dependencies(1);

  dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
  dependencies[0].dstSubpass = 0;
  dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
  dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
  dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

  VkRenderPassCreateInfo renderPassInfo = {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  renderPassInfo.pAttachments = attachments.data();
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpassDescription;
  renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
  renderPassInfo.pDependencies = dependencies.data();

  vkCreateRenderPass(g_context->device, &renderPassInfo, nullptr, &render_pass);
}

void Vulkan::Create_Framebuffers()
{
  framebuffers.resize(swapchain_image_views.size());

  for (size_t i = 0; i < swapchain_image_views.size(); i++)
  {
    std::vector<VkImageView> attachments(2);
    attachments[0] = swapchain_image_views[i];
    attachments[1] = depthImageView;

    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = render_pass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = g_context->swapchain_size.width;
    framebufferInfo.height = g_context->swapchain_size.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(g_context->device, &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS)
    {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
}

void Vulkan::createCommandPool()
{
  VkResult result;

  VkCommandPoolCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT | VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
  createInfo.queueFamilyIndex = g_context->graphics_QueueFamilyIndex;
  vkCreateCommandPool(g_context->device, &createInfo, nullptr, &commandPool);
}

void Vulkan::createCommandBuffers()
{
  VkResult result;

  VkCommandBufferAllocateInfo allocateInfo = {};
  allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocateInfo.commandPool = commandPool;
  allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocateInfo.commandBufferCount = swapchainImageCount;

  commandBuffers.resize(swapchainImageCount);
  vkAllocateCommandBuffers(g_context->device, &allocateInfo, commandBuffers.data());
}

void Vulkan::createSemaphore(VkSemaphore *semaphore)
{
  VkResult result;

  VkSemaphoreCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  vkCreateSemaphore(g_context->device, &createInfo, nullptr, semaphore);
}

void Vulkan::create_semaphores()
{
  createSemaphore(&imageAvailableSemaphore);
  createSemaphore(&renderingFinishedSemaphore);
}

void Vulkan::createFences()
{
  uint32_t i;
  fences.resize(swapchainImageCount);
  for(i = 0; i < swapchainImageCount; i++)
  {
    VkResult result;

    VkFenceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    vkCreateFence(g_context->device, &createInfo, nullptr, &fences[i]);
  }
}
