#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Framework::~Framework()
{
  if (graphics_api)
  {
    delete graphics_api;
    graphics_api = nullptr;
  }
}

void Framework::configure()
{
}

void Framework::render( Window* window, unsigned char* render_data, int count )
{
}

