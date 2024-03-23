#include <cstdio>
#include "Vulkanize/Vulkanize.h"
using namespace VULKANIZE;

// Global instance
Vulkanize VULKANIZE::vulkanize;

Vulkanize::~Vulkanize()
{
  reset();
}

bool Vulkanize::reset()
{
  if (instance_builder)
  {
    delete instance_builder;
    instance_builder = nullptr;
  }

  if (configured)
  {
    configured = false;
    vkb::destroy_instance( vulkan_instance );
  }

  return false;
}

bool Vulkanize::configure( PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr )
{
  if (configured) reset();

  auto builder = vulkan_instance_builder( fp_vkGetInstanceProcAddr );
  builder.request_validation_layers( _request_validation_layers );
  builder.require_api_version( _v_major, _v_minor, _v_bugfix );
  builder.set_app_name( _app_name.c_str() );
  if (_use_default_debug_messenger) builder.use_default_debug_messenger();

  VKZ_SET( vulkan_instance, builder.build(), "creating Vulkan instance", return reset() );
	debug_messenger = vulkan_instance.debug_messenger;
  instance_dispatch = vulkan_instance.make_table();

  configured = true;
  return true;
}

Vulkanize& Vulkanize::request_validation_layers( bool setting )
{
  _request_validation_layers = setting;
  return *this;
}

Vulkanize& Vulkanize::require_api_version( int major, int minor, int bugfix )
{
  _v_major = major;
  _v_minor = minor;
  _v_bugfix = bugfix;
  return *this;
}

Vulkanize& Vulkanize::set_app_name( const char* app_name )
{
  _app_name = app_name;
  return *this;
}

Vulkanize& Vulkanize::use_default_debug_messenger()
{
  _use_default_debug_messenger = true;
  return *this;
}

vkb::InstanceBuilder& Vulkanize::vulkan_instance_builder( PFN_vkGetInstanceProcAddr fp_vkGetInstanceProcAddr )
{
  if ( !instance_builder ) instance_builder = new vkb::InstanceBuilder( fp_vkGetInstanceProcAddr );
  return *instance_builder;
}

