#include "VulkanInterface.h"
#include "Balefire/Vulkan/RendererVulkan.h"
using namespace BALEFIRE;

void init_vulkan_extern(Vulkan *vulkan)
{
}

Vulkan::Vulkan()
{

}

Vulkan::~Vulkan()
{

}

////////////////////////////////////////////////////
/////// [Core]
//////////////////////////////////////////
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

extern SDL_Window *window;
extern char* window_name;

const vector<const char*> validationLayers = {
  ///has bug
  //"VK_LAYER_LUNARG_standard_validation"
};

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanReportFunc(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objType,
    uint64_t obj,
    size_t location,
    int32_t code,
    const char* layerPrefix,
    const char* msg,
    void* userData)
{
  printf("VULKAN VALIDATION: %s\n", msg);
  return VK_FALSE;
}

#include <set>

