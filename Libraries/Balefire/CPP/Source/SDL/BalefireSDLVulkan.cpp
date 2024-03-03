#include "Balefire/SDL/BalefireSDLVulkan.h"
#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;

void BalefireSDLVulkan::configure()
{
  SDL_Init( SDL_INIT_VIDEO );
  renderer = new RendererVulkan( this );
  renderer->configure();
}
