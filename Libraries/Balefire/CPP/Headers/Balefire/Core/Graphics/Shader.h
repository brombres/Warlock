#pragma once

#include "Balefire/Core/Graphics/ShaderStage.h"
#include "Balefire/Balefire.h"

namespace BALEFIRE
{
  struct Shader : RefCounted
  {
    // PROPERTIES
    ShaderStage stage;

    Shader( ShaderStage stage ) : stage(stage) {}
  };
};
