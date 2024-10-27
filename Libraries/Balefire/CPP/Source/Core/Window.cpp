#include "Balefire/Balefire.h"
using namespace BALEFIRE;

Window::~Window()
{
  if (renderer)
  {
    delete renderer;
    renderer = nullptr;
  }

  if (framework_context)
  {
    delete framework_context;
    framework_context = nullptr;
  }
}

void Window::render( unsigned char* render_data, int count )
{
  renderer->render( render_data, count );
}

void Window::update_pixel_size()
{
  framework->update_pixel_size( this );
}
