#include "Balefire/Balefire.h"
using namespace BALEFIRE;

void WindowRenderer::on_begin_render()
{
  projection_transform = transform = world_transform = view_transform = object_transform = glm::mat4(1.0f);
  view_transform_stack.clear();
  object_transform_stack.clear();
  transform_modified = view_transform_modified = world_transform_modified = false;
}

