#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Balefire::Balefire( Framework* framework )
{
  configure( framework );
}

Balefire::~Balefire()
{
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
