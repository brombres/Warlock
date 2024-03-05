#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Balefire::Balefire( Framework* framework )
{
  configure( framework );
}

Balefire::~Balefire()
{
  windows.clear();
}

void Balefire::configure( Framework* framework )
{
  framework->balefire = this;
  this->framework = framework;
  if (framework) framework->configure();
}

WindowID Balefire::create_window( String name )
{
  Framework* framework;
  if ((framework = this->framework.data))
  {
    return framework->create_window( name );
  }
  else
  {
    return 0;
  }
}

void Balefire::render()
{
  for (int i=0; i<windows.ids.count; ++i)
  {
    Window* window = windows[windows.ids[i]];
    framework->render( window );
  }
}

