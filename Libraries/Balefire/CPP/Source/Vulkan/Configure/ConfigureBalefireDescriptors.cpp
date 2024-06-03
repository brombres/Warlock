#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

void BALEFIRE::ConfigureBalefireDescriptors::on_configure()
{
  auto descriptor = descriptors->add_uniform_buffer<Vec4>( 0, VK_SHADER_STAGE_VERTEX_BIT );
  descriptor->set( Vec4(1,1,0,1) );

  VulkanContext* context = context_as<VulkanContext*>();
}
