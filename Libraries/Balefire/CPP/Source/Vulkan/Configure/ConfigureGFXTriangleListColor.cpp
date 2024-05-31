#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

void BALEFIRE::ConfigureGFXTriangleListColor::on_configure()
{
  topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

  add_vertex_description( new VertexDescription() );

  set_descriptors( &(dynamic_cast<VulkanContext*>(context)->descriptors) );

  add_shader_stage( VK_SHADER_STAGE_VERTEX_BIT,
    "shader.vert",
    "#version 450\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "\n"
    "layout (binding = 0) uniform Global {vec4 color;} global;\n"
    "\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "\n"
    "layout (location = 0) out vec3 fragColor;\n"
    "\n"
    "void main ()\n"
    "{\n"
      "gl_Position = vec4 (position, 0.0, 1.0);\n"
      "//fragColor = color;\n"
      "fragColor = global.color.rgb;\n"
    "}\n"
  );

  add_shader_stage( VK_SHADER_STAGE_FRAGMENT_BIT,
    "shader.frag",
    "#version 450\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "\n"
    "layout (location = 0) in vec3 fragColor;\n"
    "\n"
    "layout (location = 0) out vec4 outColor;\n"
    "\n"
    "void main () { outColor = vec4 (fragColor, 1.0); }\n"
  );
}
