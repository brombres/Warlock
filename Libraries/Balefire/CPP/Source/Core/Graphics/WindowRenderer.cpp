#include "Balefire/Balefire.h"
using namespace BALEFIRE;

void WindowRenderer::draw_line( XY a, XY b, Color color )
{
  set_primitive_type( PrimitiveType::LINES );
  vertices.reserve( vertices.size() + 2 );
  vertices.push_back( Vertex( a.x, a.y, 0, 0, color.argb ) );
  vertices.push_back( Vertex( b.x, b.y, 0, 0, color.argb ) );
  ++primitive_count;
}

void WindowRenderer::flush()
{
  if (primitive_count) {
    switch (primitive_type) {
      case PrimitiveType::LINES:
        render_commands.push_back( RenderCmd(RenderCmdType::DRAW_LINES, primitive_count*2) );
        break;
    }
    primitive_count = 0;
    primitive_type = PrimitiveType::NONE;
  }
}

void WindowRenderer::on_begin_render()
{
  projection_transform = transform = world_transform = view_transform = object_transform = glm::mat4(1.0f);
  view_transform_stack.clear();
  object_transform_stack.clear();
  transform_modified = view_transform_modified = world_transform_modified = false;
  primitive_type = PrimitiveType::NONE;
  primitive_count = 0;
}

void WindowRenderer::set_primitive_type( PrimitiveType new_primitive_type )
{
  if (primitive_type == new_primitive_type) return;
  flush();
  primitive_type = new_primitive_type;
}

