#include "Vulkanize/Vertex.h"
using namespace VKZ;

VkVertexInputBindingDescription Vertex::get_binding_description()
{
  VkVertexInputBindingDescription description = {};
  // description.binding = (set during graphics pipeline construction)
  description.stride = this->size();
  description.inputRate = per_instance() ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;
  return description;
}
