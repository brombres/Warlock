#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

#include "glslang/Include/glslang_c_interface.h"

bool ConfigureStandardVertexBuffer::activate()
{
  context->vertices.clear();
  context->vertices.push_back( StandardVertex(0.0f,-0.5f, 0, 0xff0000ff) );
  context->vertices.push_back( StandardVertex(0.5f, 0.5f, 0, 0x00ff00ff) );
  context->vertices.push_back( StandardVertex(-0.5f, 0.5f, 0, 0x0000ffff) );

  VkBufferCreateInfo buffer_info{};
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = sizeof(StandardVertex) * context->vertices.size();
  buffer_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VKZ_REQUIRE(
    "creating vertex buffer",
    vkCreateBuffer( context->device, &buffer_info, nullptr, &context->vertex_buffer )
  );

  VkMemoryRequirements mem_requirements;
  vkGetBufferMemoryRequirements( context->device,  context->vertex_buffer, &mem_requirements );

  VkMemoryAllocateInfo alloc_info{};
  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize = mem_requirements.size;
  int mem_type = context->find_memory_type( mem_requirements.memoryTypeBits,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT );
  if (mem_type == -1)
  {
    VKZ_REPORT_ERROR( "finding memory type for vertex buffer" );
    vkDestroyBuffer( context->device, context->vertex_buffer, nullptr );
    return false;
  }
  alloc_info.memoryTypeIndex = (uint32_t) mem_type;

  VKZ_ON_ERROR(
    "allocating memory for vertex buffer",
    vkAllocateMemory( context->device, &alloc_info, nullptr, &context->vertex_buffer_memory),
    vkDestroyBuffer( context->device, context->vertex_buffer, nullptr );
    return false;
  );

  return true;
}

void ConfigureStandardVertexBuffer::deactivate()
{
  vkDestroyBuffer( context->device, context->vertex_buffer, nullptr );
  vkFreeMemory( context->device, context->vertex_buffer_memory, nullptr );
}

