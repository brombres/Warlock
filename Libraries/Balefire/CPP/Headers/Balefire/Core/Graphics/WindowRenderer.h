#ifndef BALEFIRE_WINDOW_RENDER_CONTEXT_H
#define BALEFIRE_WINDOW_RENDER_CONTEXT_H

#pragma once

#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Window;

  struct WindowRenderer
  {
    // PROPERTIES
    Window* window   = nullptr;
    bool initialized = false;

    std::vector<Vertex>    vertices;
    std::vector<RenderCmd> render_commands;

    glm::mat4x4              projection_transform;
    glm::mat4x4              transform;
    glm::mat4x4              world_transform;
    glm::mat4x4              view_transform;
    glm::mat4x4              object_transform;
    std::vector<glm::mat4x4> view_transform_stack;
    std::vector<glm::mat4x4> object_transform_stack;

    bool transform_modified;
    bool view_transform_modified;
    bool world_transform_modified;

    // CONSTRUCTORS
    WindowRenderer( Window* window ) : window(window) {}
    virtual ~WindowRenderer() {}

    // METHODS
    virtual void configure() {}

    virtual void draw_line( double x1, double y1, double x2, double y2, Color color ) = 0;

    virtual void flush() {}

    virtual void on_begin_render();
    virtual void on_end_render() {}

    virtual void render( unsigned char* data, int count ) {}
  };
};

#endif // BALEFIRE_WINDOW_RENDER_CONTEXT_H
