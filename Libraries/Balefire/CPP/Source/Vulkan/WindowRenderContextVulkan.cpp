#include "Balefire/Vulkan/WindowRenderContextVulkan.h"
using namespace BALEFIRE;

#include "Vulkanize/Vulkanize.h"
#include "Vulkanize/Context.h"
using namespace VKZ;

WindowRenderContextVulkan::~WindowRenderContextVulkan()
{
  if (initialized)
  {
    initialized = false;

    context->destroy();

    delete context;
    context = nullptr;
  }
}

void WindowRenderContextVulkan::configure()
{
  // noAction
}

void WindowRenderContextVulkan::configure( VkSurfaceKHR surface )
{
  context = new VulkanContext( window, surface );

  if ( !context->configure() )
  {
    fprintf( stderr, "[Balefire] Error creating Vulkan rendering context.\n" );
    return;
  }

	initialized = true;
}

void WindowRenderContextVulkan::render( unsigned char* data, int count )
{
  if ( !initialized ) return;

  if (context->execute("render.begin"))
  {
    DataReader reader( data, count );

    reader.read_int32();  // version

    int total_vertex_count = reader.read_int32();
    vertices.clear();
    vertices.reserve( total_vertex_count );

    bool error = false;

    // First pass: collect vertices
    int pass_start_pos = reader.position;
    while ( !error )
    {
      int cmd = reader.read_int32x();
      if (cmd == RenderCmd::END_DRAWING) break;

      switch (cmd)
      {
        case RenderCmd::DRAW_LINES:
        {
          int vertex_count = reader.read_int32x() * 2;
          reader.read_int32(); // discard data skip count
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
          int vertex_count = reader.read_int32x() * 3;
          reader.read_int32(); // discard data skip count
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

        case RenderCmd::DRAW_TEXTURED_TRIANGLES:
        {
          reader.read_int32x(); // discard texture ID
          int vertex_count = reader.read_int32x() * 3;
          reader.read_int32(); // discard data skip count
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
          if (id >= context->textures.size()) context->textures.resize( id + 1 );

          Image* image = new Image();
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
            BALEFIRE_LOG_ERROR_WITH_INT( "Error creating texture %d.", id );
          }
          break;
        };

        case RenderCmd::FREE_TEXTURE:
        {
          int id = reader.read_int32x();
          if (id > 0 && id < context->textures.size())
          {
            Image* texture = context->textures[id];
            texture->destroy();
            delete texture;
            context->textures[id] = nullptr;
          }
          break;
        }

        default:
        {
          BALEFIRE_LOG_ERROR_WITH_INT(
            "Internal error in WindowRenderContextVulkan::render() - command code %d is unsupported (pass 1).",
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
      Image* texture = nullptr;

      reader.position = pass_start_pos;
      int vertex_i = 0;
      while ( !error )
      {
        int cmd = reader.read_int32x();
        if (cmd == RenderCmd::END_DRAWING) break;

        switch (cmd)
        {
          case RenderCmd::DRAW_LINES:
          {
            int vertex_count = reader.read_int32x() * 2;
            reader.skip( reader.read_int32() );

            context->gfx_line_list_color.cmd_bind( context->cmd );
            context->gfx_line_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );
            context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );
            vertex_i += vertex_count;
            break;
          }

          case RenderCmd::DRAW_TRIANGLES:
          {
            int vertex_count = reader.read_int32x() * 3;
            reader.skip( reader.read_int32() );

            context->gfx_triangle_list_color.cmd_bind( context->cmd );
            context->gfx_triangle_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );
            context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );
            vertex_i += vertex_count;
            break;
          }

          case RenderCmd::DRAW_TEXTURED_TRIANGLES:
          {
            int texture_id = reader.read_int32x();
            if (texture_id > 0 && texture_id < context->textures.size())
            {
              Image* new_texture = context->textures[texture_id];
              texture = _set_texture( texture, new_texture );
            }
            int vertex_count = reader.read_int32x() * 3;
            reader.skip( reader.read_int32() );

            context->gfx_triangle_list_texture.cmd_bind( context->cmd );
            context->gfx_triangle_list_texture.cmd_set_default_viewports_and_scissor_rects( context->cmd );
            context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );

            vertex_i += vertex_count;
            break;
          }

          case RenderCmd::DEFINE_TEXTURE:
            reader.read_int32x();  // id
            reader.read_int32x();  // width
            reader.read_int32x();  // height
            reader.read_int32s(nullptr);  // argb pixel data
            break;

          case RenderCmd::FREE_TEXTURE:
            reader.read_int32x();  // id
            break;

          default:
          {
            BALEFIRE_LOG_ERROR_WITH_INT(
              "Internal error in WindowRenderContextVulkan::render() - command code %d is unsupported (pass 2).",
              cmd
            );
            error = true;
            break;
          }
        }
      }
    }

    context->execute( "render.end" );
  }
}

Image* WindowRenderContextVulkan::_set_texture( Image* cur_texture, Image* new_texture )
{
  if (cur_texture == new_texture || !new_texture) return cur_texture;

  if (cur_texture) cur_texture->cmd_wait_until_drawing_complete( context->cmd );
  context->image_sampler->set( new_texture );
  return new_texture;
}

