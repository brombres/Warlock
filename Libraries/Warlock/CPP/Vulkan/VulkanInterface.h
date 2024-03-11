#ifndef VULKAN_INTERFACE_H
#define VULKAN_INTERFACE_H

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#include <iostream>
#include <vector>
using namespace std;

#include "Balefire/SDL/FrameworkSDLVulkan.h"
#include "Balefire/Vulkan/RendererVulkan.h"
#include "Balefire/Vulkan/WindowRenderContextVulkan.h"

extern BALEFIRE::FrameworkSDLVulkan* g_framework;
extern BALEFIRE::RendererVulkan* g_renderer;
extern BALEFIRE::WindowRenderContextVulkan* g_context;

class Vulkan
{
 private:
 void createSemaphore(VkSemaphore *semaphore);
 public:
 Vulkan();
 ~Vulkan();

//global createImageView
 VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
//global createImage
 void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
//global findMemoryType
 uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
////////////////////////////////////////////////////
/////// [Core]
//////////////////////////////////////////

 //VkDebugReportCallbackEXT debugCallback;

////////////////////////////////////////////////////
/////// [Screen]
//////////////////////////////////////////

 VkFormat depthFormat;//
 VkImage depthImage;//
 VkDeviceMemory depthImageMemory;//
 VkImageView depthImageView;//
 void Setup_DepthStencil();//

 VkRenderPass render_pass;//
 void Create_RenderPass();//

 vector<VkFramebuffer> framebuffers;
 void Create_Framebuffers();

///////////////////////////////////////////////////////////

 VkCommandPool commandPool;
 void createCommandPool();

 vector<VkCommandBuffer> commandBuffers;
 void createCommandBuffers();

 VkSemaphore imageAvailableSemaphore;
 VkSemaphore renderingFinishedSemaphore;
 void create_semaphores();

 vector<VkFence> fences;
 void createFences();
};

void init_vulkan_extern(Vulkan *vulkan);

#endif // VULKAN_EXTERN_H
