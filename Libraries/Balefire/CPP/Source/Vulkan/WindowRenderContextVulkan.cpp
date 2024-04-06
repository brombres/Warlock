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

    context->device_dispatch.deviceWaitIdle();
    context->device_dispatch.destroySemaphore( image_available_semaphore, nullptr );
    context->device_dispatch.destroySemaphore( rendering_finished_semaphore, nullptr );

    for (auto fence : fences)
    {
      context->device_dispatch.destroyFence( fence, nullptr );
    }

    context->device_dispatch.freeCommandBuffers( command_pool, (uint32_t)command_buffers.size(), command_buffers.data() );
		context->device_dispatch.destroyCommandPool( command_pool, nullptr );

    for (auto framebuffer : framebuffers)
    {
			context->device_dispatch.destroyFramebuffer( framebuffer, nullptr );
		}

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

  _configure_swapchain();
  _configure_depth_stencil();

  _configure_queues();
  _configure_render_pass();
  _configure_graphics_pipeline();

  _configure_framebuffers();
  _configure_command_pool();
  _configure_command_buffers();

  _configure_semaphores();
  _configure_fences();

	initialized = true;
}

int WindowRenderContextVulkan::find_memory_type( uint32_t typeFilter, VkMemoryPropertyFlags properties )
{
  VkPhysicalDeviceMemoryProperties memory_properties;
  vulkanize.instance_dispatch.getPhysicalDeviceMemoryProperties( context->physical_device, &memory_properties );

  for (uint32_t i=0; i<memory_properties.memoryTypeCount; ++i)
  {
    if ( (typeFilter & (1 << i)) &&
        (memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
    {
      return i;
    }
  }

  return -1;
}


#define BFCLAMP(x, lo, hi) ((x) < (lo) ? (lo) : (x) > (hi) ? (hi) : (x))
void WindowRenderContextVulkan::_configure_swapchain()
{
  //window->update_pixel_size();
}

void WindowRenderContextVulkan::_configure_queues()
{
}

void WindowRenderContextVulkan::_configure_graphics_pipeline()
{
}

void WindowRenderContextVulkan::_configure_depth_stencil()
{
}

void WindowRenderContextVulkan::_configure_render_pass()
{
}

void WindowRenderContextVulkan::_configure_framebuffers()
{
  framebuffers.resize( context->swapchain_image_views.size() );

  for (size_t i=0; i<context->swapchain_image_views.size(); ++i)
  {
    std::vector<VkImageView> attachments(2);
    attachments[0] = context->swapchain_image_views[i];
    attachments[1] = context->depth_stencil.view;

    VkFramebufferCreateInfo framebuffer_info = {};
    framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass = context->render_pass;
    framebuffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebuffer_info.pAttachments = attachments.data();
    framebuffer_info.width = context->surface_size.width;
    framebuffer_info.height = context->surface_size.height;
    framebuffer_info.layers = 1;

    VK_CHECK(
      "creating framebuffer",
      context->device_dispatch.createFramebuffer( &framebuffer_info, nullptr, &framebuffers[i] )
    );
  }
}

void WindowRenderContextVulkan::_configure_command_pool()
{
  VkCommandPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT | VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
  pool_info.queueFamilyIndex = context->graphics_QueueFamilyIndex;

  VK_CHECK(
    "creating command pool",
    context->device_dispatch.createCommandPool( &pool_info, nullptr, &command_pool )
  );
}

void WindowRenderContextVulkan::_configure_command_buffers()
{
  VkCommandBufferAllocateInfo allocateInfo = {};
  allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocateInfo.commandPool = command_pool;
  allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocateInfo.commandBufferCount = (uint32_t)context->swapchain_images.size();

  command_buffers.resize( context->swapchain_images.size() );
  context->device_dispatch.allocateCommandBuffers( &allocateInfo, command_buffers.data() );
}

void WindowRenderContextVulkan::_configure_semaphores()
{
  _create_semaphore( &image_available_semaphore );
  _create_semaphore( &rendering_finished_semaphore );
}

void WindowRenderContextVulkan::_configure_fences()
{
  fences.resize( context->swapchain_images.size() );
  for (uint32_t i=0; i<context->swapchain_images.size(); ++i)
  {
    VkFenceCreateInfo fence_info = {};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VK_CHECK(
      "creating fence",
      context->device_dispatch.createFence( &fence_info, nullptr, &fences[i] )
    );
  }
}

void WindowRenderContextVulkan::_create_semaphore( VkSemaphore *semaphore )
{
  VkSemaphoreCreateInfo semaphore_info = {};
  semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  context->device_dispatch.createSemaphore( &semaphore_info, nullptr, semaphore );
}

bool WindowRenderContextVulkan::_find_supported_depth_format( VkFormat* depth_format )
{
  std::vector<VkFormat> depth_format_candidates = {
    VK_FORMAT_D32_SFLOAT_S8_UINT,
    VK_FORMAT_D32_SFLOAT,
    VK_FORMAT_D24_UNORM_S8_UINT,
    VK_FORMAT_D16_UNORM_S8_UINT,
    VK_FORMAT_D16_UNORM
  };

  auto instance_dispatch = vulkanize.instance_dispatch;
  for (auto& format_candidate : depth_format_candidates)
  {
    VkFormatProperties format_properties;
    instance_dispatch.getPhysicalDeviceFormatProperties( context->physical_device, format_candidate, &format_properties );
    if (format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
    {
      *depth_format = format_candidate;
      return true;
    }
  }

  return false;
}

void WindowRenderContextVulkan::_recreate_swapchain()
{
  context->device_dispatch.deviceWaitIdle();
  context->device_dispatch.freeCommandBuffers( command_pool, (uint32_t)command_buffers.size(), command_buffers.data() );
  context->device_dispatch.destroyCommandPool( command_pool, nullptr );

  for (auto framebuffer : framebuffers)
  {
    context->device_dispatch.destroyFramebuffer( framebuffer, nullptr );
  }

  context->recreate_swapchain();

  _configure_swapchain();  // utilizes existing swapchain to create new swapchain
  _configure_depth_stencil();
  _configure_framebuffers();
  _configure_command_pool();
  _configure_command_buffers();
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
    image_available_semaphore,
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

  context->device_dispatch.waitForFences( 1, &fences[frame_index], VK_FALSE, UINT64_MAX );
  context->device_dispatch.resetFences( 1, &fences[frame_index] );

  cmd = command_buffers[ frame_index ];

  context->device_dispatch.resetCommandBuffer( cmd, 0 );

  VkCommandBufferBeginInfo begin_info = {};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
  context->device_dispatch.beginCommandBuffer( cmd, &begin_info );

  VkClearColorValue clear_color = { 0.0f, 0.0f, 1.0f, 1.0f };
  VkClearDepthStencilValue clear_depth_stencil = { 1.0f, 0 };

  // Begin render pass
  VkRenderPassBeginInfo render_pass_info = {};
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  render_pass_info.renderPass = context->render_pass;
  render_pass_info.framebuffer = framebuffers[frame_index];
  render_pass_info.renderArea.offset = {0, 0};
  render_pass_info.renderArea.extent = context->surface_size;
  render_pass_info.clearValueCount = 1;

  std::vector<VkClearValue> clear_values(2);
  clear_values[0].color = clear_color;
  clear_values[1].depthStencil = clear_depth_stencil;

  render_pass_info.clearValueCount = static_cast<uint32_t>( clear_values.size() );
  render_pass_info.pClearValues = clear_values.data();


  context->device_dispatch.cmdBeginRenderPass( cmd, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE );

  // Render
  context->device_dispatch.cmdBindPipeline(
    cmd,
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
  context->device_dispatch.cmdSetViewport( cmd, 0, 1, &viewport );
  context->device_dispatch.cmdSetScissor(  cmd, 0, 1, &scissor );

  context->device_dispatch.cmdDraw( cmd, 3, 1, 0, 0 );

  // End render pass
  context->device_dispatch.cmdEndRenderPass( cmd );
  context->device_dispatch.endCommandBuffer( cmd );

  VkPipelineStageFlags wait_dest_stage_mask = VK_PIPELINE_STAGE_TRANSFER_BIT;
  VkSubmitInfo submitInfo = {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = &image_available_semaphore;
  submitInfo.pWaitDstStageMask = &wait_dest_stage_mask;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &cmd;
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = &rendering_finished_semaphore;
  context->device_dispatch.queueSubmit( context->graphics_queue, 1, &submitInfo, fences[frame_index] );

  VkPresentInfoKHR present_info = {};
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present_info.waitSemaphoreCount = 1;
  present_info.pWaitSemaphores = &rendering_finished_semaphore;
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
