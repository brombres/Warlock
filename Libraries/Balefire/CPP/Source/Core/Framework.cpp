#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Framework::~Framework()
{
  if (render_api)
  {
    delete render_api;
    render_api = nullptr;
  }
}

void Framework::configure()
{
}

void Framework::render( Window* window, unsigned char* render_data, int count )
{
}

