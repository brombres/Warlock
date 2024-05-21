#include "Balefire/Balefire.h"
using namespace BALEFIRE;

#include <thread>
using namespace std;

Balefire* Balefire::instance = nullptr;

Balefire::Balefire( Framework* framework )
{
  instance = this;
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

  instance = nullptr;
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

void Balefire::render()
{
  bool all_paused = true;
  bool any_rendered = false;
  for (Window* window : windows)
  {
    if (window)
    {
      if ( !window->rendering_paused )
      {
        all_paused = false;
        if (begin_render_handler)
        {
          RenderCmdData* data = begin_render_handler( window, handler_app_data );
          if (data)
          {
            any_rendered = true;
            framework->render( window, data );
            if (end_render_handler) end_render_handler( window, handler_app_data );
          }
        }
      }
    }
  }

  if (all_paused)
  {
    this_thread::sleep_for( std::chrono::milliseconds(500) );
  }
  else if ( !any_rendered )
  {
    this_thread::sleep_for( std::chrono::milliseconds(100) );
  }
}

void Balefire::set_render_handlers( BeginRenderHandler begin_render, EndRenderHandler end_render, void* app_data )
{
  begin_render_handler = begin_render;
  end_render_handler = end_render;
  handler_app_data = app_data;
}
