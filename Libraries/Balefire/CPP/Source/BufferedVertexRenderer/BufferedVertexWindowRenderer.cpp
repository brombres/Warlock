#include "Balefire/BufferedVertexRenderer/BufferedVertexRenderer.h"
using namespace BALEFIRE;

BufferedVertexWindowRenderer::BufferedVertexWindowRenderer( Window* window )
  : WindowRenderer(window)
{
}

void BufferedVertexWindowRenderer::clear_transforms()
{
  _transform = _projection_transform = _world_transform = _view_transform = _object_transform = Matrix();
  view_transform_stack.clear();
  object_transform_stack.clear();
  transform_modified = world_transform_modified = false;
}

void BufferedVertexWindowRenderer::draw_line( XY a, XY b, Color color )
{
  set_primitive_type( PrimitiveType::LINES );
  vertices.reserve( vertices.size() + 2 );
  Matrix m = transform();

  vertices.push_back( Vertex( m*a, color.argb ) );
  vertices.push_back( Vertex( m*b, color.argb ) );
  ++primitive_count;
}

void BufferedVertexWindowRenderer::flush()
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

void BufferedVertexWindowRenderer::on_begin_render()
{
  clear_transforms();
  primitive_type = PrimitiveType::NONE;
  primitive_count = 0;
}

void BufferedVertexWindowRenderer::pop_object_transform( int count )
{
  for (int i=count; --i>=0; )
  {
    if (object_transform_stack.size())
    {
      object_transform_stack.pop_back();
      world_transform_modified = true;
      transform_modified = true;
    }
    else
    {
      BALEFIRE_LOG_ERROR( "pop_object_transform() on empty stack." );
    }
  }
}

void BufferedVertexWindowRenderer::pop_view_transform( int count )
{
  for (int i=count; --i>=0; )
  {
    if (view_transform_stack.size())
    {
      view_transform_stack.pop_back();
      world_transform_modified = true;
      transform_modified = true;
    }
    else
    {
      BALEFIRE_LOG_ERROR( "pop_view_transform() on empty stack." );
    }
  }
}

void BufferedVertexWindowRenderer::push_object_transform( Matrix m )
{
  if (object_transform_stack.size())
  {
    object_transform_stack.push_back( object_transform_stack.back() * m );
  }
  else
  {
    object_transform_stack.push_back( m );
  }
  _object_transform = object_transform_stack.back();
  world_transform_modified = true;
  transform_modified = true;
}

void BufferedVertexWindowRenderer::push_view_transform( Matrix m )
{
  if (view_transform_stack.size())
  {
    view_transform_stack.push_back( view_transform_stack.back() * m );
  }
  else
  {
    view_transform_stack.push_back( m );
  }
  _view_transform = view_transform_stack.back();
  world_transform_modified = true;
  transform_modified = true;
}

void BufferedVertexWindowRenderer::set_primitive_type( PrimitiveType new_primitive_type )
{
  if (primitive_type == new_primitive_type) return;
  flush();
  primitive_type = new_primitive_type;
}

void BufferedVertexWindowRenderer::set_projection_transform( Matrix m )
{
  _projection_transform = m;
  transform_modified = true;
}

Matrix BufferedVertexWindowRenderer::transform()
{
  if (transform_modified)
  {
    transform_modified = false;
    _transform = _projection_transform * world_transform();
  }
  return _transform;
}

Matrix BufferedVertexWindowRenderer::world_transform()
{
  if ( !world_transform_modified ) return _world_transform;

  world_transform_modified = false;
  if (view_transform_stack.size())
  {
    if (object_transform_stack.size())
    {
      _world_transform = _view_transform * _object_transform;
    }
    else
    {
      _world_transform = _view_transform;
    }
  }
  else
  {
    if (object_transform_stack.size())
    {
      _world_transform = _object_transform;
    }
    else
    {
      _world_transform = Matrix();
    }
  }
  return _world_transform;
}
