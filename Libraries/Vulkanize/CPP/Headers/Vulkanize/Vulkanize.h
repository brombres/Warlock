#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include "VkBootstrap.h"

namespace VKZ
{
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

    static const char* vkResult_to_c_string( VkResult result );
  };

  extern Vulkanize vulkanize;
};

#define VKZ_LOG_ERROR(message) fprintf( stderr, "[Vulkanize] Error %s.\n", message );

#define VKZ_SET( variable, expression, description, on_error ) \
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

#define VKZ_ON_ERROR(stage,cmd,body)                     \
	{                                                      \
		VkResult err = cmd;                                  \
		if ((err=cmd))                                       \
		{                                                    \
      fprintf( stderr,                                   \
          "[ERROR] Balefire Vulkan: error %s (%s).\n",   \
          stage, Vulkanize::vkResult_to_c_string(err) ); \
      body;                                              \
		}                                                    \
	}

#define VKZ_REQUIRE(stage,cmd) VKZ_ON_ERROR(stage,cmd,return false;)

#include "Vulkanize/Image.h"
#include "Vulkanize/Node.h"
#include "Vulkanize/Operation.h"
#include "Vulkanize/Context.h"
#include "Vulkanize/ConfigureDevice.h"
#include "Vulkanize/ConfigureFormats.h"
#include "Vulkanize/ConfigureSurfaceSize.h"
#include "Vulkanize/ConfigureSwapchain.h"
#include "Vulkanize/ConfigureDepthStencil.h"
#include "Vulkanize/ConfigureQueues.h"

