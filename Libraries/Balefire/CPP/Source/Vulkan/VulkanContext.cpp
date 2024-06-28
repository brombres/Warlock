#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct BalefireRenderBegin : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    context->staging_buffers.resize( context->swapchain_count );
    context->vertex_buffers.resize( context->swapchain_count );

    for (int i=0; i<context->swapchain_count; ++i)
    {
      if ( !context->staging_buffers[i].create_staging_buffer(context,(uint32_t)sizeof(Vertex)) )
      {
        return false;
      }

      if ( !context->vertex_buffers[i].create_vertex_buffer(context,(uint32_t)sizeof(Vertex)) )
      {
        return false;
      }
    }

    return true;
  }

  bool on_execute() override
  {
    context->staging_buffer = &context->staging_buffers[ context->swap_index ];
    context->vertex_buffer  = &context->vertex_buffers[ context->swap_index ];
    return true;
  }

  void on_deactivate() override
  {
    context->staging_buffers.clear();
    context->staging_buffer = nullptr;

    context->vertex_buffers.clear();
    context->vertex_buffer = nullptr;
  }
};

struct ConfigureShaders : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    context->color_vertex_shader = new Shader(
      context,
      VK_SHADER_STAGE_VERTEX_BIT,
      "color_shader.vert",

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

    context->color_fragment_shader = new Shader(
      context,
      VK_SHADER_STAGE_FRAGMENT_BIT,
      "color_shader.frag",

      "#version 450\n"
      "#extension GL_ARB_separate_shader_objects : enable\n"
      "\n"
      "layout (location = 0) in vec4 color;\n"
      "\n"
      "layout (location = 0) out vec4 output_color;\n"
      "\n"
      "void main () { output_color = color; }\n"
    );

    context->texture_vertex_shader = new Shader(
      context,
      VK_SHADER_STAGE_VERTEX_BIT,
      "texture_shader.vert",

      "#version 450\n"
      "#extension GL_ARB_separate_shader_objects : enable\n"
      "\n"
      "//layout (binding = 1) uniform Global {vec4 color;} global;\n"
      "\n"
      "layout (location = 0) in vec4 position;\n"
      "layout (location = 1) in vec4 color;\n"
      "layout (location = 2) in vec2 uv;\n"
      "\n"
      "layout (location = 0) out vec4 frag_color;\n"
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

    context->texture_fragment_shader = new Shader(
      context,
      VK_SHADER_STAGE_FRAGMENT_BIT,
      "shader.frag",

      "#version 450\n"
      "#extension GL_ARB_separate_shader_objects : enable\n"
      "\n"
      "layout (binding = 0) uniform sampler2D texture_sampler;\n"
      "\n"
      "layout (location = 0) in vec4 color;\n"
      "layout (location = 1) in vec2 uv;\n"
      "\n"
      "layout (location = 0) out vec4 output_color;\n"
      "\n"
      "void main () { output_color = texture( texture_sampler, uv ); }\n"
    );

    return true;
  }

  void on_deactivate() override
  {
  }
};

struct ConfigureMaterials : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    Ref<Material> material;

    material = new Material( context );
    material->set_topology( VK_PRIMITIVE_TOPOLOGY_LINE_LIST );
    material->add_vertex_description( new BalefireVertexDescription() );
    material->add_shader( context->color_vertex_shader );
    material->add_shader( context->color_fragment_shader );
    if ( !material->create() ) return false;
    context->color_line_list_material = material;

    //material = new Material( context );
    //material->set_topology( VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST );
    //material->add_vertex_description( new BalefireVertexDescription() );
    //material->add_shader( context->color_vertex_shader );
    //material->add_shader( context->color_fragment_shader );
    //if ( !material->create() ) return false;
    //context->color_triangle_list_material = material;

    return true;
  }

  void on_deactivate() override
  {
    context->shaders.clear();
    context->textures.clear();
    context->materials.clear();
    context->color_line_list_material = nullptr;
    context->color_triangle_list_material = nullptr;
  }
};

void VulkanContext::configure_operations()
{
  Context::configure_operations();

  add_operation( "configure.shaders",            new ConfigureShaders() );
  add_operation( "configure.materials",          new ConfigureMaterials() );
  add_operation( "render.begin",                 new BalefireRenderBegin() );
}

void VulkanContext::on_surface_size_change( int width, int height )
{
  window->width = width;
  window->height = height;
}
