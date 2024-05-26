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

void WindowRenderContextVulkan::render( RenderCmdData* data )
{
  if ( !initialized ) return;

  if (context->execute("render.begin"))
  {
    int data_count = data[0].int32;
    // int version = data[1].int32;
    int i = 2;

    // The first RenderCmd will be VERTEX_DATA, supplying the vertex data for
    // all dynamic drawing commands. Copy
    // vertex_data -> vertices -> staging_buffer -> vertex_buffer
    if (data[i].int32 == RenderCmd::VERTEX_DATA)
    {
      ++i;
      int n = data[i++].int32;
      //vertices.reserve( vertices.size() + n );

      // Convert color ARGB -> ABGR
      int color_offset = 3;
      int vertex_step  = BALEFIRE::VERTEX_PROPERTY_COUNT;
      int remaining = n;
      int* cur = &data[i].int32 + color_offset;
      while (--remaining >=0)
      {
        int argb = *cur;
        *cur = (argb & 0xFF00FF00) | ((argb<<16) & 0x00FF0000) | ((argb>>16) & 0x000000FF);
        cur += vertex_step;
      }

      context->staging_buffer->clear();
      context->staging_buffer->copy_from( &data[i], (uint32_t)n );
      context->vertex_buffer->clear();
      context->vertex_buffer->copy_from( context->staging_buffer );
      context->vertex_buffer->cmd_bind( context->cmd );
      i += n * BALEFIRE::VERTEX_PROPERTY_COUNT;
    }

    int vertex_i = 0;

    // Perform render
    for (; i<data_count; )
    {
      switch (data[i++].int32)
      {
        case RenderCmd::DRAW_TRIANGLES:
        {
          context->gfx_triangle_list_color.cmd_bind( context->cmd );
          context->gfx_triangle_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );
          int vertex_count = data[i++].int32;
          context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );
          vertex_i += vertex_count;
          continue;
        }
        case RenderCmd::DRAW_LINES:
        {
          context->gfx_line_list_color.cmd_bind( context->cmd );
          context->gfx_line_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );

          int vertex_count = data[i++].int32;
          context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );
          vertex_i += vertex_count;
          continue;
        }
        default:
          fprintf( stderr, "[Balefire] Unhandled RenderCmd opcode %d (%f)\n", data[i-1].int32, data[i-1].real32 );
      }
      break;
    }

    context->execute( "render.end" );
  }

}

