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
  context = new Context( surface );

  if ( !context->configure() )
  {
    fprintf( stderr, "[Balefire] Error creating Vulkan rendering context.\n" );
    return;
  }

	initialized = true;
}

void WindowRenderContextVulkan::render( CmdData* data )
{
  if ( !initialized ) return;

  if (context->execute("render.begin"))
  {
    std::vector<StandardVertex> vertices;
    vertices.push_back( StandardVertex(-0.5f,-0.5f, 0, 0xff0000ff) );
    vertices.push_back( StandardVertex( 0.5f, 0.5f, 0, 0xff00ff00) );
    vertices.push_back( StandardVertex(-0.5f, 0.5f, 0, 0xffff0000) );
    vertices.push_back( StandardVertex(-0.5f,-0.5f, 0, 0xff0000ff) );
    vertices.push_back( StandardVertex( 0.5f,-0.5f, 0, 0xffff0000) );
    vertices.push_back( StandardVertex( 0.5f, 0.5f, 0, 0xff00ff00) );

    // Copy all vertices from all draw commands into same 'vertices' buffer.
    int data_count = data[0].int32;
    for (int i=3; i<data_count; )
    {
      switch (data[i++].int32)
      {
        case RenderCmd::DRAW_TRIANGLES:
          i = _add_verticles( data, i, vertices );
          continue;
        case RenderCmd::DRAW_LINES:
          i = _add_verticles( data, i, vertices );
          continue;
        default:
          fprintf( stderr, "[Balefire] Unhandled RenderCmd opcode %d (%f)\n", data[i-1].int32, data[i-1].real32 );
      }
      break;
    }

    context->staging_buffer.clear();
    context->staging_buffer.copy_from( vertices.data(), (uint32_t)vertices.size() );
    context->vertex_buffer.clear();
    context->vertex_buffer.copy_from( context->staging_buffer );
    context->vertex_buffer.cmd_bind( context->cmd );

    // TEST
    context->gfx_triangle_list_color.cmd_bind( context->cmd );
    context->gfx_triangle_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );
    context->device_dispatch.cmdDraw( context->cmd, 6, 1, 0, 0 );
    int vertex_i = 6;

    // Perform render
    for (int i=3; i<data_count; )
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
          i += vertex_count * 6;
          continue;
        }
        case RenderCmd::DRAW_LINES:
        {
          context->gfx_line_list_color.cmd_bind( context->cmd );
          context->gfx_line_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );

          int vertex_count = data[i++].int32;
          context->device_dispatch.cmdDraw( context->cmd, vertex_count, 1, vertex_i, 0 );
          vertex_i += vertex_count;
          i += vertex_count * 6;
          continue;
        }
        default:
          fprintf( stderr, "[Balefire] Unhandled RenderCmd opcode %d (%f)\n", data[i-1].int32, data[i-1].real32 );
      }
      break;
    }

    //context->gfx_line_list_color.cmd_bind( context->cmd );
    //context->gfx_line_list_color.cmd_set_default_viewports_and_scissor_rects( context->cmd );

    context->execute( "render.end" );
  }

}

int WindowRenderContextVulkan::_add_verticles( CmdData* data, int i, std::vector<StandardVertex>& vertices )
{
  int n = data[i++].int32;
  while (--n >= 0)
  {
    vertices.push_back( StandardVertex(data[i].real32, data[i+1].real32, data[i+2].real32, data[i+3].int32) );
    i += 6;
  }
  return i;
}
