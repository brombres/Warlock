#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

void VulkanContext::configure_operations()
{
  Context::configure_operations();
  set_operation( "configure.graphics_pipelines", new BALEFIRE::ConfigureGFXTriangleListColor(&gfx_triangle_list_color) );
  add_operation( "configure.graphics_pipelines", new BALEFIRE::ConfigureGFXLineListColor(&gfx_line_list_color) );
  set_operation( "configure.vertex_buffers",     new ConfigureVertexBuffers(sizeof(StandardVertex)) );
}
