#include "Balefire/Vulkan/WindowRendererVulkan.h"
using namespace BALEFIRE;

using namespace glm;
using namespace std;

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
using namespace VKZ;

WindowRendererVulkan::~WindowRendererVulkan()
{
  if (initialized)
  {
    initialized = false;

    context->destroy();

    delete context;
    context = nullptr;
  }
}

void WindowRendererVulkan::configure()
{
  // noAction
}

void WindowRendererVulkan::configure( VkSurfaceKHR surface )
{
  context = new VulkanContext( window, surface );

  if ( !context->configure() )
  {
    fprintf( stderr, "[Balefire] Error creating Vulkan rendering context.\n" );
    return;
  }

	initialized = true;
}

void WindowRendererVulkan::draw_line( double x1, double y1, double x2, double y2, Color color )
{
  vertices.reserve( vertices.size() + 2 );
}

void WindowRendererVulkan::flush()
{
}

void WindowRendererVulkan::render( unsigned char* data, int count )
{
  if ( !initialized ) return;

  if (context->execute("render.begin"))
  {
    on_begin_render();

    DataReader reader( data, count );

    reader.read_int32();  // version

    int total_vertex_count = reader.read_int32();
    vertices.clear();
    vertices.reserve( total_vertex_count );

    bool error = false;

    // First pass: collect vertices, define and free assets
    int pass_start_pos = reader.position;
    while ( !error )
    {
      reader.read_int32x(); // skip count
      int cmd = reader.read_int32x();
      if (cmd == RenderCmd::END_DRAWING) break;

      switch (cmd)
      {
        case RenderCmd::DRAW_LINES:
        {
          reader.read_int32x(); // skip material ID
          int vertex_count = reader.read_int32x() * 2;
          for (int i=vertex_count; --i>=0; )
          {
            float x = reader.read_real32();
            float y = reader.read_real32();
            float z = reader.read_real32();
            float w = reader.read_real32();
            int   color = reader.read_int32();
            vertices.push_back( Vertex(x,y,z,w,color) );
          }
          break;
        }

        case RenderCmd::DRAW_TRIANGLES:
        {
          reader.read_int32x(); // skip material ID
          int vertex_count = reader.read_int32x() * 3;
          for (int i=vertex_count; --i>=0; )
          {
            float x = reader.read_real32();
            float y = reader.read_real32();
            float z = reader.read_real32();
            float w = reader.read_real32();
            int   color = reader.read_int32();
            float u = reader.read_real32();
            float v = reader.read_real32();
            vertices.push_back( Vertex(x,y,z,w,color,u,v) );
          }
          break;
        }

        case RenderCmd::DEFINE_TEXTURE:
        {
          int  id = reader.read_int32x();
          int  width = reader.read_int32x();
          int  height = reader.read_int32x();
          int* pixels;
          int  pixel_count = reader.read_int32s( &pixels );

          if (id <= 0) break;
          if (id >= context->textures.size())
          {
            context->textures.resize( id + 1 );
            context->materials.resize( id + 1 );
          }

          Ref<Image> image = new Image();
          context->textures[id] = image;

          // Swap red and blue
          int* cur = pixels + pixel_count;
          int  n = pixel_count;
          while (--n >= 0)
          {
            int argb = *(--cur);
            *cur = (argb & 0xff00ff00) | ((argb << 16) & 0x00ff0000) | ((argb >> 16) & 0x000000ff);
          }

          if ( !image->create(context, pixels, width, height) )
          {
            BALEFIRE_LOG_ERROR( "[Balefire] Error creating texture %d.", id );
          }

          break;
        };

        case RenderCmd::FREE_TEXTURE:
        {
          int id = reader.read_int32x();
          if (id > 0 && id < context->textures.size())
          {
            context->textures[id] = nullptr;
            context->materials[id] = nullptr;
          }
          break;
        }

        case DEFINE_SHADER:
        {
          int id = reader.read_int32x();
          if (id >= context->shaders.size()) context->shaders.resize( id + 1 );
          auto stage = (VkShaderStageFlagBits)reader.read_int32x();
          string filename = reader.read_string();
          string main_fn_name = reader.read_string();
          bool is_string = reader.read_logical();
          if (is_string)
          {
            string source = reader.read_string();
            context->shaders[id] = new Shader(
              context,
              stage,
              filename,
              source,
              main_fn_name
            );
          }
          else
          {
            unsigned char* spirv_bytes;
            int byte_count = reader.read_bytes( &spirv_bytes );
            context->shaders[id] = new Shader(
              context,
              stage,
              filename,
              (char*)spirv_bytes,
              byte_count,
              main_fn_name
            );
          }
          break;
        }

        case FREE_SHADER:
        {
          int id = reader.read_int32x();
          if (id > 0 && id < context->shaders.size())
          {
            context->shaders[id] = nullptr;
          }
          break;
        }

        case DEFINE_MATERIAL:
        {
          int id = reader.read_int32x();
          auto topology = (VkPrimitiveTopology)reader.read_int32x();
          bool primitive_restart_enabled = reader.read_int32x();
          int shader_count = reader.read_int32x();

          Ref<Material> material = new Material( context );
          material->set_topology( topology );
          material->add_vertex_description( new BalefireVertexDescription() );
          material->enable_primitive_restart( primitive_restart_enabled );

          for (int i=0; i<shader_count; ++i)
          {
            material->add_shader( context->shaders[reader.read_int32x()] );
          }

          int texture_count = reader.read_int32x();
          if (texture_count)
          {
            auto descriptor = material->add_combined_image_sampler( 0, TextureLayer::COUNT );
            for (int i=0; i<texture_count; ++i)
            {
              TextureLayer layer = (TextureLayer) reader.read_int32x();
              Image* texture = context->textures[reader.read_int32x()];
              descriptor->set( layer, texture );
            }
          }
          material->create();

          if (id >= context->materials.size()) context->materials.resize( id + 1 );
          context->materials[id] = material;
          break;
        }

        case FREE_MATERIAL:
        {
          int id = reader.read_int32x();
          if (id > 0 && id < context->materials.size())
          {
            context->materials[id] = nullptr;
          }
          break;
        }

        default:
        {
          BALEFIRE_LOG_ERROR(
            "Internal error in WindowRendererVulkan::render() - command code %d is unsupported (pass 1).",
            cmd
          );
          error = true;
          break;
        }
      }
    }

    if ( !error )
    {
      // Convert color ARGB -> ABGR
      int remaining = total_vertex_count;
      Vertex* vertex = vertices.data();
      while (--remaining >=0)
      {
        uint32_t argb = vertex->color;
        vertex->color = (argb & 0xFF00FF00) | ((argb<<16) & 0x00FF0000) | ((argb>>16) & 0x000000FF);
        ++vertex;
      }

      // Copy vertex data to staging buffer to vertex buffer
      context->staging_buffer->clear();
      context->staging_buffer->copy_from( vertices.data(), (uint32_t)vertices.size() );
      context->vertex_buffer->clear();
      context->vertex_buffer->copy_from( *context->staging_buffer );
      context->vertex_buffer->cmd_bind( context->cmd );

      // Second pass: draw
      reader.position = pass_start_pos;
      int vertex_i = 0;
      while ( !error )
      {
        int skip_count = reader.read_int32x();
        int skip_pos   = reader.position + skip_count;
        int cmd = reader.read_int32x();
        if (cmd == RenderCmd::END_DRAWING) break;

        switch (cmd)
        {
          case RenderCmd::DRAW_LINES:
          {
            int material_id = reader.read_int32x();
            int vertex_count = reader.read_int32x() * 2;
            reader.seek( skip_pos );

            Material* material = context->materials[material_id];
            material->cmd_bind( context->cmd );
            material->cmd_set_default_viewports_and_scissor_rects( context->cmd );
            context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );
            vertex_i += vertex_count;
            break;
          }

          case RenderCmd::DRAW_TRIANGLES:
          {
            int material_id = reader.read_int32x();
            int vertex_count = reader.read_int32x() * 3;
            reader.seek( skip_pos );

            Material* material = context->materials[material_id];
            material->cmd_bind( context->cmd );
            material->cmd_set_default_viewports_and_scissor_rects( context->cmd );
            context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );

            vertex_i += vertex_count;
            break;
          }

          case RenderCmd::DEFINE_TEXTURE:
          case RenderCmd::FREE_TEXTURE:
          case RenderCmd::DEFINE_SHADER:
          case RenderCmd::FREE_SHADER:
          case RenderCmd::DEFINE_MATERIAL:
          case RenderCmd::FREE_MATERIAL:
            reader.seek( skip_pos );
            break;

          default:
          {
            BALEFIRE_LOG_ERROR(
              "Internal error in WindowRendererVulkan::render() - command code %d is unsupported (pass 2).",
              cmd
            );
            error = true;
            break;
          }
        }
      }
    }

    on_end_render();

    context->execute( "render.end" );
  }
}

