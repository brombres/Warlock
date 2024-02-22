#include "Engine.h"
using namespace Warlock;

Engine::~Engine()
{
  if (display)
  {
    delete display;
    display = nullptr;
  }
}

void Engine::configure( Warlock::Display* manager )
{
  if (this->display) delete this->display;

  this->display = display;

  if (display)
  {
    display->configure();
  }
}

