#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct ConfigureTestImage : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    uint32_t pixels[] = {0xff00ffff,0xff00ffff,0xff00ffff,0xff00ffff};
    return context->test_image.create( context, pixels, 2, 2 );
  }

  void on_deactivate() override
  {
    context->test_image.destroy();
  }
};

struct ConfigureSamplers : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    SamplerInfo info( context );
    return context->test_sampler.create( info );
  }

  void on_deactivate() override
  {
    context->test_sampler.destroy();
  }
};

void VulkanContext::configure_operations()
{
  Context::configure_operations();

  add_operation( "configure.buffers",            new ConfigureVertexBuffers(sizeof(Vertex)) );
  add_operation( "configure.images",             new ConfigureTestImage() );
  add_operation( "configure.samplers",           new ConfigureSamplers() );
  add_operation( "configure.descriptors",        new ConfigureBalefireDescriptors(&descriptors) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListColor(&gfx_triangle_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXLineListColor(&gfx_line_list_color) );
}
