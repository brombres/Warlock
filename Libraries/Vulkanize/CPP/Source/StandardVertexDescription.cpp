#include "Vulkanize/StandardVertexDescription.h"
using namespace std;
using namespace VKZ;

void StandardVertexDescription::collect_attribute_descriptions( vector<VkVertexInputAttributeDescription>& list )
{
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 0, position, VK_FORMAT_R32G32B32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 1, uv,       VK_FORMAT_R32G32_SFLOAT );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 2, color,    VK_FORMAT_R8G8B8A8_SRGB );
  VKZ_VERTEX_ATTRIBUTE( StandardVertex, 3, data,     VK_FORMAT_R32_UINT );
}

