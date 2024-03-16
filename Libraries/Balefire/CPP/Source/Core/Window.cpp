#include "Balefire/Core/Framework.h"
#include "Balefire/Core/Window.h"
using namespace BALEFIRE;


void Window::render()
{
  render_context->render();
}

void Window::update_pixel_size()
{
  framework->update_pixel_size( this );
}
