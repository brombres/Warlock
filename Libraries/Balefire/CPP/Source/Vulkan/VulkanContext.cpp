#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct ConfigureTestImage : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    Buffer staging_buffer;
    staging_buffer.create_staging_buffer( context, 4, 4 );
    uint32_t pixels[] = {0xffffffff,0xffffffff,0xff0000ff,0xff0000ff};
    staging_buffer.copy_from( pixels, 4 );

    ImageInfo info(
      context,
      2, 2,
      VK_FORMAT_R8G8B8A8_SRGB,
      VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
      VK_IMAGE_ASPECT_COLOR_BIT,
      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );

    if ( !context->test_image.create(info) ) return true;

    context->test_image.transition_layout( VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL );
    context->test_image.copy_from( staging_buffer );
    context->test_image.transition_layout( VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL );

    staging_buffer.destroy();
    return true;
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
