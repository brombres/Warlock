#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

void BALEFIRE::ConfigureBalefireDescriptors::on_configure()
{
  VulkanContext* context = context_as<VulkanContext*>();

  context->fill_color = descriptors->add_uniform_buffer<Vec4>( 0, VK_SHADER_STAGE_VERTEX_BIT );
  context->fill_color->set( Vec4(0,1,1,1) );

  context->image_sampler = descriptors->add_combined_image_sampler(
    1, VK_SHADER_STAGE_FRAGMENT_BIT,
    &context->test_image, &context->test_sampler
  );
}
