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
    context->standard_pipeline.cmd_bind( context->cmd );
    context->standard_pipeline.cmd_set_default_viewports_and_scissor_rects( context->cmd );

    std::vector<StandardVertex> vertices;
    vertices.push_back( StandardVertex(-0.5f,-0.5f, 0, 0xff0000ff) );
    vertices.push_back( StandardVertex( 0.5f, 0.5f, 0, 0xff00ff00) );
    vertices.push_back( StandardVertex(-0.5f, 0.5f, 0, 0xffff0000) );
    vertices.push_back( StandardVertex(-0.5f,-0.5f, 0, 0xff0000ff) );
    vertices.push_back( StandardVertex( 0.5f,-0.5f, 0, 0xffff0000) );
    vertices.push_back( StandardVertex( 0.5f, 0.5f, 0, 0xff00ff00) );
    context->staging_buffer.clear();
    context->staging_buffer.copy_from( vertices.data(), (uint32_t)vertices.size() );
    context->vertex_buffer.clear();
    context->vertex_buffer.copy_from( context->staging_buffer );

    context->vertex_buffer.cmd_bind( context->cmd );

    context->device_dispatch.cmdDraw( context->cmd, (uint32_t)context->vertex_buffer.count, 1, 0, 0 );

    context->execute( "render.end" );
  }

}
