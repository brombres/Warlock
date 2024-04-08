#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

//#include "glslang/Include/glslang_c_interface.h"

CompileShader::CompileShader( Context* context ) : context(context)
{
}

bool CompileShader::activate()
{
  //glslang_initialize_process();
  return true;
}

void CompileShader::deactivate()
{
  //glslang_finalize_process();
}


bool CompileShader::execute()
{
  return true;
}

