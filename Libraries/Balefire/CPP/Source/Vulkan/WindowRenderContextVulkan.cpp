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

void WindowRenderContextVulkan::render()
{
  if ( !initialized ) return;

  if (context->execute("render.begin"))
  {
    context->device_dispatch.cmdDraw( context->cmd, context->vertices.size(), 1, 0, 0 );
    context->execute( "render.end" );
  }

}
