#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Balefire::Balefire( Framework* framework )
{
  configure( framework );
}

Balefire::~Balefire()
{
  while (windows.count) delete windows.remove_last();
  windows.clear();

  if (this->framework)
  {
    delete this->framework;
    this->framework = nullptr;
  }
}

void Balefire::configure( Framework* framework )
{
  framework->balefire = this;
  if (this->framework) delete this->framework;
  this->framework = framework;
  if (framework) framework->configure();
}

WindowID Balefire::create_window( std::string name )
{
  if (framework)
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
  for (WindowID id : windows.ids)
  {
    Window* window = windows[id];
    framework->render( window );
  }
}

