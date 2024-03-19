#include "Balefire/Vulkan/WindowRenderContextVulkan.h"
using namespace BALEFIRE;

#include "Vulkanize/Vulkanize.h"
using namespace VULKANIZE;

const Byte fragment_spv[] =
{
  3, 2, 35, 7, 0, 5, 1, 0, 11, 0, 8, 0, 19, 0, 0, 0,
  0, 0, 0, 0, 17, 0, 2, 0, 1, 0, 0, 0, 11, 0, 6, 0,
  1, 0, 0, 0, 71, 76, 83, 76, 46, 115, 116, 100, 46, 52, 53, 48,
  0, 0, 0, 0, 14, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  15, 0, 7, 0, 4, 0, 0, 0, 4, 0, 0, 0, 109, 97, 105, 110,
  0, 0, 0, 0, 9, 0, 0, 0, 12, 0, 0, 0, 16, 0, 3, 0,
  4, 0, 0, 0, 7, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0,
  194, 1, 0, 0, 4, 0, 9, 0, 71, 76, 95, 65, 82, 66, 95, 115,
  101, 112, 97, 114, 97, 116, 101, 95, 115, 104, 97, 100, 101, 114, 95, 111,
  98, 106, 101, 99, 116, 115, 0, 0, 5, 0, 4, 0, 4, 0, 0, 0,
  109, 97, 105, 110, 0, 0, 0, 0, 5, 0, 5, 0, 9, 0, 0, 0,
  111, 117, 116, 67, 111, 108, 111, 114, 0, 0, 0, 0, 5, 0, 5, 0,
  12, 0, 0, 0, 102, 114, 97, 103, 67, 111, 108, 111, 114, 0, 0, 0,
  71, 0, 4, 0, 9, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0,
  71, 0, 4, 0, 12, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0,
  19, 0, 2, 0, 2, 0, 0, 0, 33, 0, 3, 0, 3, 0, 0, 0,
  2, 0, 0, 0, 22, 0, 3, 0, 6, 0, 0, 0, 32, 0, 0, 0,
  23, 0, 4, 0, 7, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0,
  32, 0, 4, 0, 8, 0, 0, 0, 3, 0, 0, 0, 7, 0, 0, 0,
  59, 0, 4, 0, 8, 0, 0, 0, 9, 0, 0, 0, 3, 0, 0, 0,
  23, 0, 4, 0, 10, 0, 0, 0, 6, 0, 0, 0, 3, 0, 0, 0,
  32, 0, 4, 0, 11, 0, 0, 0, 1, 0, 0, 0, 10, 0, 0, 0,
  59, 0, 4, 0, 11, 0, 0, 0, 12, 0, 0, 0, 1, 0, 0, 0,
  43, 0, 4, 0, 6, 0, 0, 0, 14, 0, 0, 0, 0, 0, 128, 63,
  54, 0, 5, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 0, 0, 248, 0, 2, 0, 5, 0, 0, 0, 61, 0, 4, 0,
  10, 0, 0, 0, 13, 0, 0, 0, 12, 0, 0, 0, 81, 0, 5, 0,
  6, 0, 0, 0, 15, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0,
  81, 0, 5, 0, 6, 0, 0, 0, 16, 0, 0, 0, 13, 0, 0, 0,
  1, 0, 0, 0, 81, 0, 5, 0, 6, 0, 0, 0, 17, 0, 0, 0,
  13, 0, 0, 0, 2, 0, 0, 0, 80, 0, 7, 0, 7, 0, 0, 0,
  18, 0, 0, 0, 15, 0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0,
  14, 0, 0, 0, 62, 0, 3, 0, 9, 0, 0, 0, 18, 0, 0, 0,
  253, 0, 1, 0, 56, 0, 1, 0
};

const Byte vertex_spv[] =
{
  3, 2, 35, 7, 0, 5, 1, 0, 11, 0, 8, 0, 54, 0, 0, 0,
  0, 0, 0, 0, 17, 0, 2, 0, 1, 0, 0, 0, 11, 0, 6, 0,
  1, 0, 0, 0, 71, 76, 83, 76, 46, 115, 116, 100, 46, 52, 53, 48,
  0, 0, 0, 0, 14, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  15, 0, 10, 0, 0, 0, 0, 0, 4, 0, 0, 0, 109, 97, 105, 110,
  0, 0, 0, 0, 12, 0, 0, 0, 23, 0, 0, 0, 34, 0, 0, 0,
  38, 0, 0, 0, 49, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0,
  194, 1, 0, 0, 4, 0, 9, 0, 71, 76, 95, 65, 82, 66, 95, 115,
  101, 112, 97, 114, 97, 116, 101, 95, 115, 104, 97, 100, 101, 114, 95, 111,
  98, 106, 101, 99, 116, 115, 0, 0, 5, 0, 4, 0, 4, 0, 0, 0,
  109, 97, 105, 110, 0, 0, 0, 0, 5, 0, 5, 0, 12, 0, 0, 0,
  112, 111, 115, 105, 116, 105, 111, 110, 115, 0, 0, 0, 5, 0, 4, 0,
  23, 0, 0, 0, 99, 111, 108, 111, 114, 115, 0, 0, 5, 0, 6, 0,
  32, 0, 0, 0, 103, 108, 95, 80, 101, 114, 86, 101, 114, 116, 101, 120,
  0, 0, 0, 0, 6, 0, 6, 0, 32, 0, 0, 0, 0, 0, 0, 0,
  103, 108, 95, 80, 111, 115, 105, 116, 105, 111, 110, 0, 6, 0, 7, 0,
  32, 0, 0, 0, 1, 0, 0, 0, 103, 108, 95, 80, 111, 105, 110, 116,
  83, 105, 122, 101, 0, 0, 0, 0, 6, 0, 7, 0, 32, 0, 0, 0,
  2, 0, 0, 0, 103, 108, 95, 67, 108, 105, 112, 68, 105, 115, 116, 97,
  110, 99, 101, 0, 6, 0, 7, 0, 32, 0, 0, 0, 3, 0, 0, 0,
  103, 108, 95, 67, 117, 108, 108, 68, 105, 115, 116, 97, 110, 99, 101, 0,
  5, 0, 3, 0, 34, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0,
  38, 0, 0, 0, 103, 108, 95, 86, 101, 114, 116, 101, 120, 73, 110, 100,
  101, 120, 0, 0, 5, 0, 5, 0, 49, 0, 0, 0, 102, 114, 97, 103,
  67, 111, 108, 111, 114, 0, 0, 0, 72, 0, 5, 0, 32, 0, 0, 0,
  0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 72, 0, 5, 0,
  32, 0, 0, 0, 1, 0, 0, 0, 11, 0, 0, 0, 1, 0, 0, 0,
  72, 0, 5, 0, 32, 0, 0, 0, 2, 0, 0, 0, 11, 0, 0, 0,
  3, 0, 0, 0, 72, 0, 5, 0, 32, 0, 0, 0, 3, 0, 0, 0,
  11, 0, 0, 0, 4, 0, 0, 0, 71, 0, 3, 0, 32, 0, 0, 0,
  2, 0, 0, 0, 71, 0, 4, 0, 38, 0, 0, 0, 11, 0, 0, 0,
  42, 0, 0, 0, 71, 0, 4, 0, 49, 0, 0, 0, 30, 0, 0, 0,
  0, 0, 0, 0, 19, 0, 2, 0, 2, 0, 0, 0, 33, 0, 3, 0,
  3, 0, 0, 0, 2, 0, 0, 0, 22, 0, 3, 0, 6, 0, 0, 0,
  32, 0, 0, 0, 23, 0, 4, 0, 7, 0, 0, 0, 6, 0, 0, 0,
  2, 0, 0, 0, 21, 0, 4, 0, 8, 0, 0, 0, 32, 0, 0, 0,
  0, 0, 0, 0, 43, 0, 4, 0, 8, 0, 0, 0, 9, 0, 0, 0,
  3, 0, 0, 0, 28, 0, 4, 0, 10, 0, 0, 0, 7, 0, 0, 0,
  9, 0, 0, 0, 32, 0, 4, 0, 11, 0, 0, 0, 6, 0, 0, 0,
  10, 0, 0, 0, 59, 0, 4, 0, 11, 0, 0, 0, 12, 0, 0, 0,
  6, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0, 13, 0, 0, 0,
  0, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0, 14, 0, 0, 0,
  0, 0, 0, 191, 44, 0, 5, 0, 7, 0, 0, 0, 15, 0, 0, 0,
  13, 0, 0, 0, 14, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0,
  16, 0, 0, 0, 0, 0, 0, 63, 44, 0, 5, 0, 7, 0, 0, 0,
  17, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 44, 0, 5, 0,
  7, 0, 0, 0, 18, 0, 0, 0, 14, 0, 0, 0, 16, 0, 0, 0,
  44, 0, 6, 0, 10, 0, 0, 0, 19, 0, 0, 0, 15, 0, 0, 0,
  17, 0, 0, 0, 18, 0, 0, 0, 23, 0, 4, 0, 20, 0, 0, 0,
  6, 0, 0, 0, 3, 0, 0, 0, 28, 0, 4, 0, 21, 0, 0, 0,
  20, 0, 0, 0, 9, 0, 0, 0, 32, 0, 4, 0, 22, 0, 0, 0,
  6, 0, 0, 0, 21, 0, 0, 0, 59, 0, 4, 0, 22, 0, 0, 0,
  23, 0, 0, 0, 6, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0,
  24, 0, 0, 0, 0, 0, 128, 63, 44, 0, 6, 0, 20, 0, 0, 0,
  25, 0, 0, 0, 24, 0, 0, 0, 13, 0, 0, 0, 13, 0, 0, 0,
  44, 0, 6, 0, 20, 0, 0, 0, 26, 0, 0, 0, 13, 0, 0, 0,
  24, 0, 0, 0, 13, 0, 0, 0, 44, 0, 6, 0, 20, 0, 0, 0,
  27, 0, 0, 0, 13, 0, 0, 0, 13, 0, 0, 0, 24, 0, 0, 0,
  44, 0, 6, 0, 21, 0, 0, 0, 28, 0, 0, 0, 25, 0, 0, 0,
  26, 0, 0, 0, 27, 0, 0, 0, 23, 0, 4, 0, 29, 0, 0, 0,
  6, 0, 0, 0, 4, 0, 0, 0, 43, 0, 4, 0, 8, 0, 0, 0,
  30, 0, 0, 0, 1, 0, 0, 0, 28, 0, 4, 0, 31, 0, 0, 0,
  6, 0, 0, 0, 30, 0, 0, 0, 30, 0, 6, 0, 32, 0, 0, 0,
  29, 0, 0, 0, 6, 0, 0, 0, 31, 0, 0, 0, 31, 0, 0, 0,
  32, 0, 4, 0, 33, 0, 0, 0, 3, 0, 0, 0, 32, 0, 0, 0,
  59, 0, 4, 0, 33, 0, 0, 0, 34, 0, 0, 0, 3, 0, 0, 0,
  21, 0, 4, 0, 35, 0, 0, 0, 32, 0, 0, 0, 1, 0, 0, 0,
  43, 0, 4, 0, 35, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0,
  32, 0, 4, 0, 37, 0, 0, 0, 1, 0, 0, 0, 35, 0, 0, 0,
  59, 0, 4, 0, 37, 0, 0, 0, 38, 0, 0, 0, 1, 0, 0, 0,
  32, 0, 4, 0, 40, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0,
  32, 0, 4, 0, 46, 0, 0, 0, 3, 0, 0, 0, 29, 0, 0, 0,
  32, 0, 4, 0, 48, 0, 0, 0, 3, 0, 0, 0, 20, 0, 0, 0,
  59, 0, 4, 0, 48, 0, 0, 0, 49, 0, 0, 0, 3, 0, 0, 0,
  32, 0, 4, 0, 51, 0, 0, 0, 6, 0, 0, 0, 20, 0, 0, 0,
  54, 0, 5, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 0, 0, 248, 0, 2, 0, 5, 0, 0, 0, 62, 0, 3, 0,
  12, 0, 0, 0, 19, 0, 0, 0, 62, 0, 3, 0, 23, 0, 0, 0,
  28, 0, 0, 0, 61, 0, 4, 0, 35, 0, 0, 0, 39, 0, 0, 0,
  38, 0, 0, 0, 65, 0, 5, 0, 40, 0, 0, 0, 41, 0, 0, 0,
  12, 0, 0, 0, 39, 0, 0, 0, 61, 0, 4, 0, 7, 0, 0, 0,
  42, 0, 0, 0, 41, 0, 0, 0, 81, 0, 5, 0, 6, 0, 0, 0,
  43, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 81, 0, 5, 0,
  6, 0, 0, 0, 44, 0, 0, 0, 42, 0, 0, 0, 1, 0, 0, 0,
  80, 0, 7, 0, 29, 0, 0, 0, 45, 0, 0, 0, 43, 0, 0, 0,
  44, 0, 0, 0, 13, 0, 0, 0, 24, 0, 0, 0, 65, 0, 5, 0,
  46, 0, 0, 0, 47, 0, 0, 0, 34, 0, 0, 0, 36, 0, 0, 0,
  62, 0, 3, 0, 47, 0, 0, 0, 45, 0, 0, 0, 61, 0, 4, 0,
  35, 0, 0, 0, 50, 0, 0, 0, 38, 0, 0, 0, 65, 0, 5, 0,
  51, 0, 0, 0, 52, 0, 0, 0, 23, 0, 0, 0, 50, 0, 0, 0,
  61, 0, 4, 0, 20, 0, 0, 0, 53, 0, 0, 0, 52, 0, 0, 0,
  62, 0, 3, 0, 49, 0, 0, 0, 53, 0, 0, 0, 253, 0, 1, 0,
  56, 0, 1, 0
};

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

    context->device_dispatch.destroyPipeline( graphics_pipeline, nullptr );
    context->device_dispatch.destroyPipelineLayout( pipeline_layout, nullptr );

    context->device_dispatch.freeCommandBuffers( command_pool, command_buffers.size(), command_buffers.data() );
		context->device_dispatch.destroyCommandPool( command_pool, nullptr );
    context->device_dispatch.destroyRenderPass( render_pass, nullptr );

    for (auto framebuffer : framebuffers)
    {
			context->device_dispatch.destroyFramebuffer( framebuffer, nullptr );
		}

    depth_stencil.destroy();

    swapchain.destroy_image_views( swapchain_image_views );

    vkb::destroy_swapchain( swapchain );
    context->device_dispatch.deviceWaitIdle();

    if (context)
    {
      delete context;
      context = nullptr;
    }
  }
}

void WindowRenderContextVulkan::configure()
{
  // noAction
}

void WindowRenderContextVulkan::configure( VkSurfaceKHR surface )
{
  context = new VkzContext( surface );
  context->configure();
  _configure_swapchain();
  _configure_queues();
  _configure_depth_stencil();
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
  window->update_pixel_size();
  int width = window->pixel_width;
  int height = window->pixel_height;

  VkSurfaceCapabilitiesKHR surface_capabilities;
  vulkanize.instance_dispatch.getPhysicalDeviceSurfaceCapabilitiesKHR( context->physical_device, context->surface, &surface_capabilities );
  width = BFCLAMP( width, surface_capabilities.minImageExtent.width, surface_capabilities.maxImageExtent.width );
  height = BFCLAMP( height, surface_capabilities.minImageExtent.height, surface_capabilities.maxImageExtent.height );
  swapchain_size.width = width;
  swapchain_size.height = height;
	vkb::SwapchainBuilder swapchain_builder{ context->device };
	auto swapchain_build_result = swapchain_builder
    //.set_desired_format( VK_FORMAT_B8G8R8A8_UNORM )
    .set_desired_format( {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR} )
		//.use_default_format_selection()
		.set_desired_present_mode( VK_PRESENT_MODE_FIFO_KHR )
		.set_desired_extent( width, height )
    .set_old_swapchain( swapchain )
		.build();
  vkb::destroy_swapchain( swapchain );
  swapchain = swapchain_build_result.value();

  swapchain_images = swapchain.get_images().value();
  swapchain_image_views = swapchain.get_image_views().value();
}

void WindowRenderContextVulkan::_configure_queues()
{
  graphics_QueueFamilyIndex = context->device.get_queue_index( vkb::QueueType::graphics ).value();
  present_QueueFamilyIndex  = context->device.get_queue_index( vkb::QueueType::present ).value();

	graphics_queue = vkb_require( context->device.get_queue(vkb::QueueType::graphics) );
	present_queue  = vkb_require( context->device.get_queue(vkb::QueueType::present) );
}

void WindowRenderContextVulkan::_configure_graphics_pipeline()
{
  VkShaderModule vertex_module =
      _create_shader_module( vertex_spv, sizeof(vertex_spv) );
  VkShaderModule fragment_module =
      _create_shader_module( fragment_spv, sizeof(fragment_spv) );

  if (vertex_module == VK_NULL_HANDLE || fragment_module == VK_NULL_HANDLE)
  {
    fprintf( stderr, "[ERROR] Balefire Vulkan: failed to create shader module.\n" );
    abort();
  }

  VkPipelineShaderStageCreateInfo vertex_stage_info = {};
  vertex_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertex_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertex_stage_info.module = vertex_module;
  vertex_stage_info.pName = "main";

  VkPipelineShaderStageCreateInfo fragment_stage_info = {};
  fragment_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragment_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragment_stage_info.module = fragment_module;
  fragment_stage_info.pName = "main";

  VkPipelineShaderStageCreateInfo shader_stages[] =
      { vertex_stage_info, fragment_stage_info };

  VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = 0;
  vertex_input_info.vertexAttributeDescriptionCount = 0;

  VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width  = swapchain.extent.width;
  viewport.height = swapchain.extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = { 0, 0 };
  scissor.extent = swapchain.extent;

  VkPipelineViewportStateCreateInfo viewport_state = {};
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling = {};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineColorBlendAttachmentState color_blend_attachment = {};
  color_blend_attachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo color_blending = {};
  color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable = VK_FALSE;
  color_blending.logicOp = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = 1;
  color_blending.pAttachments = &color_blend_attachment;
  color_blending.blendConstants[0] = 0.0f;
  color_blending.blendConstants[1] = 0.0f;
  color_blending.blendConstants[2] = 0.0f;
  color_blending.blendConstants[3] = 0.0f;

  VkPipelineLayoutCreateInfo pipeline_layout_info = {};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 0;
  pipeline_layout_info.pushConstantRangeCount = 0;

  if (VK_SUCCESS != context->device_dispatch.createPipelineLayout(
      &pipeline_layout_info, nullptr, &pipeline_layout))
  {
    fprintf( stderr, "[ERROR] Balefire Vulkan: failed to create pipeline layout.\n" );
    abort();
  }

  std::vector<VkDynamicState> dynamic_states =
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
    VK_DYNAMIC_STATE_DEPTH_BIAS
  };

  VkPipelineDynamicStateCreateInfo dynamic_info = {};
  dynamic_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_info.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
  dynamic_info.pDynamicStates = dynamic_states.data();

  VkGraphicsPipelineCreateInfo pipeline_info = {};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = 2;
  pipeline_info.pStages = shader_stages;
  pipeline_info.pVertexInputState = &vertex_input_info;
  pipeline_info.pInputAssemblyState = &input_assembly;
  pipeline_info.pViewportState = &viewport_state;
  pipeline_info.pRasterizationState = &rasterizer;
  pipeline_info.pMultisampleState = &multisampling;
  pipeline_info.pColorBlendState = &color_blending;
  pipeline_info.pDynamicState = &dynamic_info;
  pipeline_info.layout = pipeline_layout;
  pipeline_info.renderPass = render_pass;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

  VK_CHECK( "creating graphics pipeline",
    context->device_dispatch.createGraphicsPipelines(
      VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &graphics_pipeline
    )
  );

  context->device_dispatch.destroyShaderModule( fragment_module, nullptr );
  context->device_dispatch.destroyShaderModule( vertex_module, nullptr );
}

void WindowRenderContextVulkan::_configure_depth_stencil()
{
  VkFormat depth_format;
  if ( !_find_supported_depth_format( &depth_format ) )
  {
    VK_LOG_ERROR( "finding supported depth format" );
    abort();
  }

  depth_stencil.create(
    this,
    swapchain_size.width,
    swapchain_size.height,
    depth_format,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    VK_IMAGE_ASPECT_DEPTH_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
  );
}

void WindowRenderContextVulkan::_configure_render_pass()
{
  std::vector<VkAttachmentDescription> attachments(2);

  attachments[0].format = swapchain.image_format;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  attachments[1].format = depth_stencil.format;
  attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference color_reference = {};
  color_reference.attachment = 0;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depth_reference = {};
  depth_reference.attachment = 1;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpassDescription = {};
  subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpassDescription.colorAttachmentCount = 1;
  subpassDescription.pColorAttachments = &color_reference;
  subpassDescription.pDepthStencilAttachment = &depth_reference;
  subpassDescription.inputAttachmentCount = 0;
  subpassDescription.pInputAttachments = nullptr;
  subpassDescription.preserveAttachmentCount = 0;
  subpassDescription.pPreserveAttachments = nullptr;
  subpassDescription.pResolveAttachments = nullptr;

  std::vector<VkSubpassDependency> dependencies(1);

  dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
  dependencies[0].dstSubpass = 0;
  dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
  dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
  dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

  VkRenderPassCreateInfo render_pass_info = {};
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount = static_cast<uint32_t>(attachments.size());
  render_pass_info.pAttachments = attachments.data();
  render_pass_info.subpassCount = 1;
  render_pass_info.pSubpasses = &subpassDescription;
  render_pass_info.dependencyCount = static_cast<uint32_t>(dependencies.size());
  render_pass_info.pDependencies = dependencies.data();

	VK_CHECK(
    "creating render pass",
    context->device_dispatch.createRenderPass(
      &render_pass_info,
      nullptr,
      &render_pass
    )
  );
}

void WindowRenderContextVulkan::_configure_framebuffers()
{
  framebuffers.resize( swapchain_image_views.size() );

  for (size_t i=0; i<swapchain_image_views.size(); ++i)
  {
    std::vector<VkImageView> attachments(2);
    attachments[0] = swapchain_image_views[i];
    attachments[1] = depth_stencil.view;

    VkFramebufferCreateInfo framebuffer_info = {};
    framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass = render_pass;
    framebuffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebuffer_info.pAttachments = attachments.data();
    framebuffer_info.width = swapchain_size.width;
    framebuffer_info.height = swapchain_size.height;
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
  pool_info.queueFamilyIndex = graphics_QueueFamilyIndex;

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
  allocateInfo.commandBufferCount = swapchain_images.size();

  command_buffers.resize( swapchain_images.size() );
  context->device_dispatch.allocateCommandBuffers( &allocateInfo, command_buffers.data() );

  /*
  for (size_t i=0; i<command_buffers.size(); ++i)
  {
    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VK_CHECK(
      "beginning command buffer",
      context->device_dispatch.beginCommandBuffer( command_buffers[i], &begin_info )
    );

    VkRenderPassBeginInfo render_pass_info = {};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = render_pass;
    render_pass_info.framebuffer = framebuffers[i];
    render_pass_info.renderArea.offset = { 0, 0 };
    render_pass_info.renderArea.extent = swapchain.extent;
    VkClearValue clearColor{ { { 0.0f, 0.0f, 0.0f, 1.0f } } };
    render_pass_info.clearValueCount = 1;
    render_pass_info.pClearValues = &clearColor;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapchain.extent.width;
    viewport.height = (float)swapchain.extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = swapchain.extent;

    context->device_dispatch.cmdSetViewport(command_buffers[i], 0, 1, &viewport);
    context->device_dispatch.cmdSetScissor(command_buffers[i], 0, 1, &scissor);

    context->device_dispatch.cmdBeginRenderPass(
      command_buffers[i],
      &render_pass_info,
      VK_SUBPASS_CONTENTS_INLINE
    );

    context->device_dispatch.cmdBindPipeline(
      command_buffers[i],
      VK_PIPELINE_BIND_POINT_GRAPHICS,
      graphics_pipeline
    );

    context->device_dispatch.cmdDraw( command_buffers[i], 3, 1, 0, 0 );
    context->device_dispatch.cmdEndRenderPass(command_buffers[i]);

    VK_CHECK(
      "ending command buffer",
      context->device_dispatch.endCommandBuffer( command_buffers[i] )
    );
  }
  */
}

void WindowRenderContextVulkan::_configure_semaphores()
{
  _create_semaphore( &image_available_semaphore );
  _create_semaphore( &rendering_finished_semaphore );
}

void WindowRenderContextVulkan::_configure_fences()
{
  uint32_t i;
  fences.resize( swapchain_images.size() );
  for (uint32_t i=0; i<swapchain_images.size(); ++i)
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
  context->device_dispatch.freeCommandBuffers( command_pool, command_buffers.size(), command_buffers.data() );
  context->device_dispatch.destroyCommandPool( command_pool, nullptr );

  for (auto framebuffer : framebuffers)
  {
    context->device_dispatch.destroyFramebuffer( framebuffer, nullptr );
  }

  swapchain.destroy_image_views( swapchain_image_views );

  _configure_swapchain();  // utilizes existing swapchain to create new swapchain
  _configure_framebuffers();
  _configure_command_pool();
  _configure_command_buffers();
}

VkShaderModule WindowRenderContextVulkan::_create_shader_module( const Byte* code, int count )
{
  VkShaderModuleCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = count;
  create_info.pCode = (const uint32_t*)code;

  VkShaderModule shader_module;
  if (VK_SUCCESS !=
      context->device_dispatch.createShaderModule(&create_info, nullptr, &shader_module))
  {
    return VK_NULL_HANDLE; // failed to create shader module
  }

  return shader_module;
}

void WindowRenderContextVulkan::render()
{

  VkResult result = context->device_dispatch.acquireNextImageKHR(
    swapchain,
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
        "[ERROR] Balefire Vulkan: % (%s).\n",
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
  render_pass_info.renderPass = render_pass;
  render_pass_info.framebuffer = framebuffers[frame_index];
  render_pass_info.renderArea.offset = {0, 0};
  render_pass_info.renderArea.extent = swapchain_size;
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
    graphics_pipeline
  );

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = swapchain_size.width;
  viewport.height = swapchain_size.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = { 0, 0 };
  scissor.extent = swapchain_size;
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
  context->device_dispatch.queueSubmit( graphics_queue, 1, &submitInfo, fences[frame_index] );

  VkPresentInfoKHR present_info = {};
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  present_info.waitSemaphoreCount = 1;
  present_info.pWaitSemaphores = &rendering_finished_semaphore;
  present_info.swapchainCount = 1;
  present_info.pSwapchains = &swapchain.swapchain;
  present_info.pImageIndices = &frame_index;

  result = context->device_dispatch.queuePresentKHR( present_queue, &present_info );
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
        //if (surface_capabilities.currentExtent.width != swapchain_size.width ||
        //    surface_capabilities.currentExtent.height != swapchain_size.height)
        //{
        //  _recreate_swapchain();
        //}
        //return;
    default:
      fprintf(
        stderr,
        "[ERROR] Balefire Vulkan: % (%s).\n",
        "error presenting swapchain image",
        RendererVulkan::vkResult_to_c_string(result)
      );
      return;
  }

  context->device_dispatch.queueWaitIdle( present_queue );
}
