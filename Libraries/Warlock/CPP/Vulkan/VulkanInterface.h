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
 public:
 Vulkan();
 ~Vulkan();

////////////////////////////////////////////////////
/////// [Core]
//////////////////////////////////////////

 //VkDebugReportCallbackEXT debugCallback;

////////////////////////////////////////////////////
/////// [Screen]
//////////////////////////////////////////


///////////////////////////////////////////////////////////

};

void init_vulkan_extern(Vulkan *vulkan);

#endif // VULKAN_EXTERN_H
