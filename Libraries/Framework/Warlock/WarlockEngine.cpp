#include "WarlockEngine.h"
using namespace Warlock;

Engine::~Engine()
{
  if (display_manager)
  {
    delete display_manager;
    display_manager = nullptr;
  }
}

void Engine::configure( Warlock::DisplayManager* manager )
{
  if (this->display_manager) delete this->display_manager;

  this->display_manager = display_manager;

  if (display_manager)
  {
    display_manager->configure();
  }
}

