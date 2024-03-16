#include "VulkanFunctions.h"

void AcquireNextImage()
{
  /*
  vkAcquireNextImageKHR(
    g_context->device,
    g_context->swapchain,
    UINT64_MAX,
    g_context->image_available_semaphore,
    VK_NULL_HANDLE,
    &g_context->frame_index
  );

  vkWaitForFences( g_context->device, 1, &g_context->fences[g_context->frame_index], VK_FALSE, UINT64_MAX );
  vkResetFences( g_context->device, 1, &g_context->fences[g_context->frame_index] );

  commandBuffer = g_context->command_buffers[g_context->frame_index];
  */
}

void ResetCommandBuffer()
{
}

void BeginCommandBuffer()
{
}

void EndCommandBuffer()
{
}

void FreeCommandBuffers()
{
  vkFreeCommandBuffers(g_context->device, g_context->command_pool, 1, &g_context->cmd);
}

void BeginRenderPass(VkClearColorValue clear_color,VkClearDepthStencilValue clear_depth_stencil)
{
}

void EndRenderPass()
{
}

void QueueSubmit()
{
}

void QueuePresent()
{
}

void SetViewport(int width,int height)
{
  VkViewport viewport;
  viewport.width = (float)width / 2;
  viewport.height = (float)height;
  viewport.minDepth = (float)0.0f;
  viewport.maxDepth = (float)1.0f;
  viewport.x = 0;
  viewport.y = 0;
  vkCmdSetViewport(g_context->cmd, 0, 1, &viewport);
}

void SetScissor(int width,int height)
{
  VkRect2D scissor;
  scissor.extent.width = width / 2;
  scissor.extent.height = height;
  scissor.offset.x = 0;
  scissor.offset.y = 0;
  vkCmdSetScissor(g_context->cmd, 0, 1, &scissor);
}
