#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

#include "glslang/Include/glslang_c_interface.h"

CompileShader::CompileShader( Context* context ) : context(context)
{
}

bool CompileShader::activate()
{
  return true;
}

void CompileShader::deactivate()
{
}


bool CompileShader::execute()
{
  return true;
}

