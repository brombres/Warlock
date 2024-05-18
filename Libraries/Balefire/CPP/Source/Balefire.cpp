#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Balefire::Balefire( Framework* framework )
{
  configure( framework );
}

Balefire::~Balefire()
{
  for (int i=0; i<windows.size(); ++i)
  {
    Window* window = windows[i];
    if (window) delete window;
  }
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

Window* Balefire::create_window( int index, std::string name )
{
  if (framework)
  {
    return framework->create_window( index, name );
  }
  else
  {
    return 0;
  }
}

bool Balefire::handle_events()
{
  if (framework) return framework->handle_events();
  return false;
}

void Balefire::render( CmdData* data )
{
  for (Window* window : windows)
  {
    if (window) framework->render( window, data );
  }
}

