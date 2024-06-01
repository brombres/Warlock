#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

void VulkanContext::configure_operations()
{
  Context::configure_operations();

  set_operation( "configure.descriptors",        new BALEFIRE::ConfigureBalefireDescriptors(&descriptors) );
  set_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListColor(&gfx_triangle_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXLineListColor(&gfx_line_list_color) );
  set_operation( "configure.buffers",            new ConfigureVertexBuffers(sizeof(Vertex)) );
}
