#include "Balefire/Vulkan/WindowRenderContextVulkan.h"
using namespace BALEFIRE;

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
using namespace VKZ;

WindowRenderContextVulkan::~WindowRenderContextVulkan()
{
  if (initialized)
  {
    initialized = false;

    context->destroy();

    delete context;
    context = nullptr;
  }
}

void WindowRenderContextVulkan::configure()
{
  // noAction
}

void WindowRenderContextVulkan::configure( VkSurfaceKHR surface )
{
  context = new Context( surface );

  if ( !context->configure() )
  {
    fprintf( stderr, "[Balefire] Error creating Vulkan rendering context.\n" );
    return;
  }

	initialized = true;
}

void WindowRenderContextVulkan::_recreate_swapchain()
{
  context->recreate_swapchain();
}

VkShaderModule WindowRenderContextVulkan::_create_shader_module( const Byte* code, int count )
{
  return VK_NULL_HANDLE; // failed to create shader module
}

void WindowRenderContextVulkan::render()
{
  if ( !initialized ) return;

  VkResult result = context->device_dispatch.acquireNextImageKHR(
    context->swapchain,
    UINT64_MAX,
    context->image_available_semaphore,
    VK_NULL_HANDLE,
    &frame_index
  );

  switch (result)
  {
    case VK_SUCCESS:
      break;
    case VK_SUBOPTIMAL_KHR:
    case VK_ERROR_OUT_OF_DATE_KHR:
      _recreate_swapchain();
      return;
    //case VK_ERROR_SURFACE_LOST_KHR: destroy & recreate surface
    default:
      fprintf(
        stderr,
        "[ERROR] Balefire Vulkan: %s (%s).\n",
        "error acquiring swapchain image",
        RendererVulkan::vkResult_to_c_string(result)
      );
      return;
  }

  context->device_dispatch.waitForFences( 1, &context->fences[frame_index], VK_FALSE, UINT64_MAX );
  context->device_dispatch.resetFences( 1, &context->fences[frame_index] );

  context->cmd = context->command_buffers[ frame_index ];

  context->device_dispatch.resetCommandBuffer( context->cmd, 0 );

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
  context->device_dispatch.beginCommandBuffer( context->cmd, &begin_info );

  VkClearColorValue clear_color = { 0.0f, 0.0f, 1.0f, 1.0f };
  VkClearDepthStencilValue clear_depth_stencil = { 1.0f, 0 };

  // Begin render pass
  VkRenderPassBeginInfo render_pass_info = {};
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  render_pass_info.renderPass = context->render_pass;
  render_pass_info.framebuffer = context->framebuffers[frame_index];
  render_pass_info.renderArea.offset = {0, 0};
  render_pass_info.renderArea.extent = context->surface_size;
  render_pass_info.clearValueCount = 1;

  std::vector<VkClearValue> clear_values(2);
  clear_values[0].color = clear_color;
  clear_values[1].depthStencil = clear_depth_stencil;

  render_pass_info.clearValueCount = static_cast<uint32_t>( clear_values.size() );
  render_pass_info.pClearValues = clear_values.data();


  context->device_dispatch.cmdBeginRenderPass( context->cmd, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE );

  // Render
  context->device_dispatch.cmdBindPipeline(
    context->cmd,
    VK_PIPELINE_BIND_POINT_GRAPHICS,
    context->graphics_pipeline
  );

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = context->surface_size.width;
  viewport.height = context->surface_size.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = { 0, 0 };
  scissor.extent = context->surface_size;
  context->device_dispatch.cmdSetViewport( context->cmd, 0, 1, &viewport );
  context->device_dispatch.cmdSetScissor(  context->cmd, 0, 1, &scissor );

  context->device_dispatch.cmdDraw( context->cmd, 3, 1, 0, 0 );

  // End render pass
  context->device_dispatch.cmdEndRenderPass( context->cmd );
  context->device_dispatch.endCommandBuffer( context->cmd );

  VkPipelineStageFlags wait_dest_stage_mask = VK_PIPELINE_STAGE_TRANSFER_BIT;
  VkSubmitInfo submitInfo = {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = &context->image_available_semaphore;
  submitInfo.pWaitDstStageMask = &wait_dest_stage_mask;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &context->cmd;
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = &context->rendering_finished_semaphore;
  context->device_dispatch.queueSubmit( context->graphics_queue, 1, &submitInfo, context->fences[frame_index] );

  VkPresentInfoKHR present_info = {};
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present_info.waitSemaphoreCount = 1;
  present_info.pWaitSemaphores = &context->rendering_finished_semaphore;
  present_info.swapchainCount = 1;
  present_info.pSwapchains = &context->swapchain.swapchain;
  present_info.pImageIndices = &frame_index;

  result = context->device_dispatch.queuePresentKHR( context->present_queue, &present_info );
  switch (result)
  {
    case VK_SUCCESS:
      break;
    case VK_ERROR_OUT_OF_DATE_KHR:
    case VK_SUBOPTIMAL_KHR:
      _recreate_swapchain();
      return;
        // SUBOPTIMAL could be due to resize
        //VkSurfaceCapabilitiesKHR surface_capabilities;
        //vkGetPhysicalDeviceSurfaceCapabilitiesKHR( context->physical_device, surface, &surface_capabilities );
        //if (surface_capabilities.currentExtent.width != context->surface_size.width ||
        //    surface_capabilities.currentExtent.height != context->surface_size.height)
        //{
        //  _recreate_swapchain();
        //}
        //return;
    default:
      fprintf(
        stderr,
        "[ERROR] Balefire Vulkan: %s (%s).\n",
        "error presenting swapchain image",
        RendererVulkan::vkResult_to_c_string(result)
      );
      return;
  }

  context->device_dispatch.queueWaitIdle( context->present_queue );
}
