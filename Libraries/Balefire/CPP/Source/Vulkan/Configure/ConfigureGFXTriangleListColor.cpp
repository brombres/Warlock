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
    "//layout (binding = 0) uniform Global {vec4 color;} global;\n"
    "\n"
    "layout (location = 0) in vec4 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "layout (location = 2) in vec2 uv;\n"
    "\n"
    "layout (location = 0) out vec3 frag_color;\n"
    "layout (location = 1) out vec2 frag_uv;\n"
    "\n"
    "void main ()\n"
    "{\n"
      "gl_Position = position;\n"
      "frag_color = color;\n"
      "//frag_color = global.color.rgb;\n"
      "frag_uv = uv;\n"
    "}\n"
  );

  add_shader_stage( VK_SHADER_STAGE_FRAGMENT_BIT,
    "shader.frag",
    "#version 450\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "\n"
    "//layout (binding = 1) uniform sampler2D texture_sampler;\n"
    "\n"
    "layout (location = 0) in vec3 color;\n"
    "layout (location = 1) in vec2 uv;\n"
    "\n"
    "layout (location = 0) out vec4 output_color;\n"
    "\n"
    "void main () { output_color = vec4 (color, 1.0); }\n"
    "//void main () { output_color = vec4(uv, 0, 1); }\n"
    "//void main () { output_color = texture( texture_sampler, uv ); }\n"
  );
}
