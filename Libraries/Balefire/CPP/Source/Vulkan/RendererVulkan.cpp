#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;

#include "VkBootstrap.h"

void RendererVulkan::configure()
{
	vkb::InstanceBuilder builder( vkGetInstanceProcAddr );

	//make the vulkan instance, with basic debug features
	auto inst_ret = builder.set_app_name( "Warlock" )
		.request_validation_layers( true )
		.use_default_debug_messenger()
		.require_api_version(1, 2, 0)
		.build();

	vkb::Instance vkb_inst = inst_ret.value();

	instance = vkb_inst.instance;
	debug_messenger = vkb_inst.debug_messenger;
}
