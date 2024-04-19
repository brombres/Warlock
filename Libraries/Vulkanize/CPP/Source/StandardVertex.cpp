#include "Vulkanize/StandardVertex.h"
using namespace std;
using namespace VKZ;

std::vector<VkVertexInputAttributeDescription> StandardVertex::get_attribute_descriptions()
{
  std::vector<VkVertexInputAttributeDescription> descriptions;

  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 0, position, VK_FORMAT_R32G32B32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 1, rgba,     VK_FORMAT_R8G8B8A8_SRGB );

  return descriptions;
}

