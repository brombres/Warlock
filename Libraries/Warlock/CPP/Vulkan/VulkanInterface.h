#ifndef VULKAN_INTERFACE_H
#define VULKAN_INTERFACE_H

#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#include <iostream>
#include <vector>
using namespace std;

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
 vkb::Instance instance;
 vector<VkExtensionProperties> instance_extension;
 void Create_Instance();

 VkDebugUtilsMessengerEXT debug_messenger;
 //VkDebugReportCallbackEXT debugCallback;
 void Create_Debug();

 VkSurfaceKHR surface;
 void Create_Surface();

 vkb::PhysicalDevice physical_device;
 void Select_PhysicalDevice();

 uint32_t graphics_QueueFamilyIndex;
 uint32_t present_QueueFamilyIndex;
 void Select_QueueFamily();

 vkb::Device device;
 VkQueue graphicsQueue;
 VkQueue presentQueue;
 void Create_Device();

////////////////////////////////////////////////////
/////// [Screen]
//////////////////////////////////////////
 //VkSwapchainKHR swapchain;
 vkb::Swapchain swapchain;

 VkSurfaceCapabilitiesKHR surfaceCapabilities;//
 VkSurfaceFormatKHR surfaceFormat;//
 VkExtent2D swapchainSize;//

 vector<VkImage> swapchain_images;
 uint32_t swapchainImageCount;//
 bool Create_Swapchain(bool resize);

 vector<VkImageView> swapchainImageViews;
 void Create_ImageViews();

 VkFormat depthFormat;//
 VkImage depthImage;//
 VkDeviceMemory depthImageMemory;//
 VkImageView depthImageView;//
 void Setup_DepthStencil();//

 VkRenderPass render_pass;//
 void Create_RenderPass();//

 vector<VkFramebuffer> swapchainFramebuffers;
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
