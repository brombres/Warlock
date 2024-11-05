#pragma once

namespace BALEFIRE
{
  struct Window;

  struct BufferedVertexWindowRenderer : WindowRenderer
  {
    // PROPERTIES
    std::vector<Vertex>      old_vertices;

    std::vector<Vertex>      vertices;
    std::vector<RenderCmd>   render_commands;
    PrimitiveType            primitive_type = PrimitiveType::NONE;
    int                      primitive_count = 0;

    Matrix                   _transform;            // the combination of projection and world transforms
    Matrix                   _projection_transform;
    Matrix                   _world_transform;      // the combination of object and view transforms
    Matrix                   _view_transform;       // the camera or 2D coordinate space transform
    Matrix                   _object_transform;     // the object's position within the world, or in 2D

    std::vector<Matrix>      view_transform_stack;
    std::vector<Matrix>      object_transform_stack;

    bool transform_modified;
    bool world_transform_modified;

    // CONSTRUCTORS
    BufferedVertexWindowRenderer( Window* window );
    virtual ~BufferedVertexWindowRenderer() {}

    // METHODS
    virtual void clear_transforms();

    virtual void draw_line( XY a, XY b, Color color );

    virtual void flush();

    virtual void on_begin_render();

    virtual void pop_object_transform( int count=1 );
    virtual void pop_view_transform( int count=1 );

    virtual void push_object_transform( Matrix m );
    virtual void push_view_transform( Matrix m );

    virtual void set_primitive_type( PrimitiveType new_primitive_type );
    virtual void set_projection_transform( Matrix m );

    virtual Matrix transform();
    virtual Matrix world_transform();
  };
};

