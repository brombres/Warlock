#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct ConfigureTestImage : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    Buffer staging_buffer;
    staging_buffer.create_staging_buffer( context, 4, 16 );
    int pixels[] = {-1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1 };
    staging_buffer.copy_from( pixels, 16 );

    ImageInfo info(
      4, 4,
      VK_FORMAT_R8G8B8A8_SRGB,
      VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
      VK_IMAGE_ASPECT_COLOR_BIT,
      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
    );

    if ( !context->test_image.create(context, info) ) return true;

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

void VulkanContext::configure_operations()
{
  Context::configure_operations();

  set_operation( "configure.descriptors",        new ConfigureBalefireDescriptors(&descriptors) );
  set_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListColor(&gfx_triangle_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXLineListColor(&gfx_line_list_color) );
  set_operation( "configure.buffers",            new ConfigureVertexBuffers(sizeof(Vertex)) );
  add_operation( "configure.test_image",         new ConfigureTestImage() );
}
