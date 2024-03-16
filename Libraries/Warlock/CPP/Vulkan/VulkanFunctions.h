#ifndef VULKAN_FUNCTION_H
#define VULKAN_FUNCTION_H

#include <iostream>
#include <vector>
using namespace std;

#include <vulkan/vulkan.h>

#include "Balefire/SDL/FrameworkSDLVulkan.h"
#include "Balefire/Vulkan/RendererVulkan.h"
#include "Balefire/Vulkan/WindowRenderContextVulkan.h"

extern BALEFIRE::WindowRenderContextVulkan* g_context;

void AcquireNextImage();

void ResetCommandBuffer();
void BeginCommandBuffer();
void EndCommandBuffer();
void FreeCommandBuffers();

void BeginRenderPass(VkClearColorValue clear_color,VkClearDepthStencilValue clear_depth_stencil);
void EndRenderPass();

void QueueSubmit();
void QueuePresent();

void SetViewport(int width,int height);
void SetScissor(int width,int height);

#endif // VULKAN_FUNCTION_H
