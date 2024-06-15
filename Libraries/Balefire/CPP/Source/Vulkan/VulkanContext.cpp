#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct ConfigureTextures : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    uint32_t pixels[] = {0xff0000ff,0xff0000ff,0xff0000ff,0xff0000ff};
    return context->test_image.create( context, pixels, 2, 2 );
  }

  void on_deactivate() override
  {
    context->test_image.destroy();

    for (Image* texture : context->textures)
    {
      if (texture)
      {
        texture->destroy();
        delete texture;
      }
    }
    context->textures.clear();
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
  add_operation( "configure.images",             new ConfigureTextures() );
  add_operation( "configure.samplers",           new ConfigureSamplers() );
  add_operation( "configure.descriptors",        new ConfigureBalefireDescriptors(&descriptors) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXLineListColor(&gfx_line_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListColor(&gfx_triangle_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListTexture(&gfx_triangle_list_texture) );
}
