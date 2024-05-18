#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Window::~Window()
{
  if (render_context)
  {
    delete render_context;
    render_context = nullptr;
  }

  if (framework_context)
  {
    delete framework_context;
    framework_context = nullptr;
  }
}

void Window::render( CmdData* data )
{
  render_context->render( data );
}

void Window::update_pixel_size()
{
  framework->update_pixel_size( this );
}
