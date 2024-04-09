#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

#include "glslang/Include/glslang_c_interface.h"

bool ConfigureGLSLang::activate()
{
  printf( "------- ACTIVATE GLSLANG -------\n" );
  glslang_initialize_process();
  return true;
}

void ConfigureGLSLang::deactivate()
{
  printf( "------- DEACTIVATE GLSLANG -------\n" );
  glslang_finalize_process();
}

