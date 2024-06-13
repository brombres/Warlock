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
  context = new VulkanContext( surface );

  if ( !context->configure() )
  {
    fprintf( stderr, "[Balefire] Error creating Vulkan rendering context.\n" );
    return;
  }

	initialized = true;
}

void WindowRenderContextVulkan::render( const char* data, int count )
{
  if ( !initialized ) return;

  if (context->execute("render.begin"))
  {
    DataReader reader( data, count );

    reader.read_int32();  // version

    int total_vertex_count = reader.read_int32();
    vertices.clear();
    vertices.reserve( total_vertex_count );

    // First pass: collect vertices
    int pass_start_pos = reader.position;
    for (;;)
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
            int   color = reader.read_int32();
            vertices.push_back( Vertex(x,y,z,color) );
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
            int   color = reader.read_int32();
            vertices.push_back( Vertex(x,y,z,color) );
          }
          break;
        }

        case RenderCmd::DRAW_TEXTURED_TRIANGLES:
        {
          int vertex_count = reader.read_int32x() * 3;
          reader.read_int32(); // discard data skip count
          for (int i=vertex_count; --i>=0; )
          {
            float x = reader.read_real32();
            float y = reader.read_real32();
            float z = reader.read_real32();
            int   color = reader.read_int32();
            float u = reader.read_real32();
            float v = reader.read_real32();
            vertices.push_back( Vertex(x,y,z,color,u,v) );
          }
          break;
        }

        default:
        {
          char message[120];
          snprintf(
            message, 120,
            "Internal error in WindowRenderContextVulkan::render() - command code %d is unsupported (pass 1).",
            cmd
          );
          BALEFIRE_LOG_ERROR( message );
        }
      }
    }

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
    for (;;)
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
          int vertex_count = reader.read_int32x() * 3;
          reader.skip( reader.read_int32() );
          break;
        }

        default:
        {
          char message[120];
          snprintf(
            message, 120,
            "Internal error in WindowRenderContextVulkan::render() - command code %d is unsupported (pass 2).",
            cmd
          );
          BALEFIRE_LOG_ERROR( message );
        }
      }
    }

    context->execute( "render.end" );
  }

}

