#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct ConfigureTextures : ContextOperation<VulkanContext>
{
  void on_deactivate() override
  {
    context->textures.clear();
  }
};

struct ConfigureShaders : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    context->color_shader = new Shader( context );

    context->color_shader->add_vertex_shader(
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

    context->color_shader->add_fragment_shader(
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

    context->texture_shader = new Shader( context );

    context->texture_shader->add_vertex_shader(
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

    context->texture_shader->add_fragment_shader(
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
  //bool on_activate() override
  //{
  //        Material* material = new Material( context );
  //        context->materials[id] = material;
  //        material->add_vertex_description( new VertexDescription() );
  //        material->set_shader( context->texture_shader );
  //        material->add_combined_image_sampler( 0, image );
  //        material->create();
  //}

  void on_deactivate() override
  {
    context->materials.clear();
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
  add_operation( "configure.shaders",            new ConfigureShaders() );
  add_operation( "configure.materials",          new ConfigureMaterials() );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXLineListColor(&gfx_line_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListColor(&gfx_triangle_list_color) );
  add_operation( "configure.graphics_pipelines", new ConfigureGFXTriangleListTexture(&gfx_triangle_list_texture) );
}

void VulkanContext::on_surface_size_change( int width, int height )
{
  window->width = width;
  window->height = height;
}
