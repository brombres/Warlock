#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

#include "Vulkanize/Context.h"

namespace VULKANIZE
{
  struct Context;

  struct Vulkanize
  {
    // PROPERTIES
    vkb::InstanceBuilder* instance_builder = nullptr;
    bool _request_validation_layers = false;
    bool _v_major  = 1;
    bool _v_minor  = 2;
    bool _v_bugfix = 0;
    std::string _app_name = "Vulkanized App";
    bool _use_default_debug_messenger = true;
    bool configured = false;

    vkb::Instance              vulkan_instance;
    vkb::InstanceDispatchTable instance_dispatch;
    VkDebugUtilsMessengerEXT   debug_messenger;

    // METHODS
    ~Vulkanize();
    bool        reset();

    bool        configure( PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr );
    Vulkanize&  request_validation_layers( bool setting=true );
    Vulkanize&  require_api_version( int major=1, int minor=2, int bugfix=0 );
    Vulkanize&  set_app_name( const char* app_name );
    Vulkanize&  use_default_debug_messenger();
    vkb::InstanceBuilder& vulkan_instance_builder( PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr );

    Context* create_context( VkSurfaceKHR surface );
  };

  extern Vulkanize vulkanize;
};

#define LOG_VULKANIZE_ERROR(message) fprintf( stderr, "[Vulkanize] %s.\n", message );

#define VKB_SET( variable, expression, description, on_error ) \
{                                                              \
  auto result = expression;                                    \
  if (result)                                                  \
  {                                                            \
    variable = result.value();                                 \
  }                                                            \
  else                                                         \
  {                                                            \
    fprintf( stderr, "[Vulkanize] Error %s; %s.\n",            \
             description, result.error().message().c_str() );  \
    on_error;                                                  \
  }                                                            \
}
