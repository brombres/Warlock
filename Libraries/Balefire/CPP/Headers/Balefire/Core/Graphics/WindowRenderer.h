#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  enum class PrimitiveType {
    NONE,
    LINES
  };

  struct Window;

  struct WindowRenderer
  {
    // PROPERTIES
    GraphicsAPI* graphics_api  = nullptr;
    Window*      window      = nullptr;
    bool         initialized = false;

    // CONSTRUCTORS
    WindowRenderer( Window* window ) : window(window) {}
    virtual ~WindowRenderer() {}

    // METHODS
    virtual void configure() {}

    virtual void clear_transforms() = 0;

    virtual Ref<Shader> create_shader( ShaderStage stage, std::string filename, std::string source,
                                       std::string main_function_name="main" ) = 0;

    virtual void draw_line( XY a, XY b, Color color ) = 0;

    virtual void flush() {}

    virtual void on_begin_render() {}
    virtual void on_end_render() {}

    virtual void pop_object_transform( int count=1 ) = 0;
    virtual void pop_view_transform( int count=1 ) = 0;

    virtual void push_object_transform( Matrix m ) = 0;
    virtual void push_view_transform( Matrix m ) = 0;

    virtual void render( unsigned char* data, int count ) {}

    virtual void set_primitive_type( PrimitiveType new_primitive_type ) = 0;
    virtual void set_projection_transform( Matrix m ) = 0;

    virtual Matrix transform() = 0;
    virtual Matrix world_transform() = 0;
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_H
