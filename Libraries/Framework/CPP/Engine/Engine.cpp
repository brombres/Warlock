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

void Engine::configure( Warlock::Display* new_display )
{
  if (display == new_display) return;
  if (display) delete display;
  display = new_display;
  if (new_display) new_display->configure();
}

Window Engine::create_window()
{
  if (display) return display->create_window();
  return Window();
}
