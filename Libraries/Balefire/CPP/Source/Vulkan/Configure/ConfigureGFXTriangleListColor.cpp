#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

void BALEFIRE::ConfigureGFXTriangleListColor::on_configure()
{
  topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

  add_vertex_description( new VertexDescription() );

  VulkanContext* context = context_as<VulkanContext*>();
  set_descriptors( &context->descriptors );

  add_shader_stage( VK_SHADER_STAGE_VERTEX_BIT,
    "shader.vert",
    "#version 450\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "\n"
    "layout (location = 0) in vec4 position;\n"
    "layout (location = 1) in vec4 color;\n"
    "\n"
    "layout (location = 0) out vec4 frag_color;\n"
    "\n"
    "void main ()\n"
    "{\n"
      "gl_Position = position;\n"
      "frag_color = color;\n"
    "}\n"
  );

  add_shader_stage( VK_SHADER_STAGE_FRAGMENT_BIT,
    "shader.frag",
    "#version 450\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "\n"
    "layout (location = 0) in vec4 color;\n"
    "\n"
    "layout (location = 0) out vec4 output_color;\n"
    "\n"
    "void main () { output_color = color; }\n"
  );
}
