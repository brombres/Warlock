#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Framework::~Framework()
{
  if (renderer)
  {
    delete renderer;
    renderer = nullptr;
  }
}

void Framework::configure()
{
}

void Framework::render( Window* window, CmdData* data )
{
}

