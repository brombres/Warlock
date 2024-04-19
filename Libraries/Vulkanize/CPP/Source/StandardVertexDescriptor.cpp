#include "Vulkanize/StandardVertexDescriptor.h"
using namespace std;
using namespace VKZ;

std::vector<VkVertexInputAttributeDescription> StandardVertexDescriptor::get_attribute_descriptions()
{
  std::vector<VkVertexInputAttributeDescription> descriptions;
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 0, position, VK_FORMAT_R32G32B32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 1, normal,   VK_FORMAT_R32G32B32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 2, uv,       VK_FORMAT_R32G32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 3, uv2,      VK_FORMAT_R32G32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 4, color,    VK_FORMAT_R8G8B8A8_SRGB );
  return descriptions;
}

