#ifndef BALEFIRE_H
#define BALEFIRE_H

#pragma once

#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Balefire/Core/Types.h"
#include "Balefire/Core/RefCounted.h"
#include "Balefire/Core/Geometry/XY.h"
#include "Balefire/Core/Geometry/XYZ.h"
#include "Balefire/Core/Geometry/XYZW.h"
#include "Balefire/Core/Math/Matrix.h"
#include "Balefire/Core/Graphics/Vertex.h"
#include "Balefire/Core/Graphics/Color.h"
#include "Balefire/Core/Graphics/TextureLayer.h"
#include "Balefire/Core/DataReader.h"
#include "Balefire/Core/Graphics/OldRenderCmd.h"
#include "Balefire/Core/Graphics/RenderCmd.h"
#include "Balefire/Core/Window.h"
#include "Balefire/Core/Framework/Framework.h"
#include "Balefire/Core/Graphics/ShaderStage.h"
#include "Balefire/Core/Graphics/Shader.h"
#include "Balefire/Core/Graphics/GraphicsAPI.h"
#include "Balefire/Core/Framework/WindowFrameworkContext.h"
#include "Balefire/Core/Graphics/WindowRenderer.h"
#include "Balefire/Core/EventHandler.h"

namespace BALEFIRE
{
  const int VERTEX_PROPERTY_COUNT = 7;

  struct Balefire
  {
    static Balefire* instance;

    EventHandler* event_handler = nullptr;

    std::vector<Window*> windows;

    Framework* framework = nullptr;

    Balefire() { instance = this; }
    Balefire( Framework* framework );

    virtual ~Balefire();
    virtual void     configure( Framework* framework );
    virtual Window*  create_window( int index, std::string name );
    virtual bool     handle_events();
    virtual void     render();
  };
};

#endif // BALEFIRE_H
