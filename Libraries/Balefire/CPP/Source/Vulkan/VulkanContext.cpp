#include "Balefire/Vulkan/GraphicsAPIVulkan.h"
using namespace BALEFIRE;
using namespace VKZ;

struct BalefireRenderBegin : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    context->staging_buffers.resize( context->swapchain_count );
    context->vertex_buffers.resize( context->swapchain_count );

    for (int i=0; i<context->swapchain_count; ++i)
    {
      if ( !context->staging_buffers[i].create_staging_buffer(context,(uint32_t)sizeof(Vertex)) )
      {
        return false;
      }

      if ( !context->vertex_buffers[i].create_vertex_buffer(context,(uint32_t)sizeof(Vertex)) )
      {
        return false;
      }
    }

    return true;
  }

  bool on_execute() override
  {
    context->staging_buffer = &context->staging_buffers[ context->swap_index ];
    context->vertex_buffer  = &context->vertex_buffers[ context->swap_index ];
    return true;
  }

  void on_deactivate() override
  {
    context->staging_buffers.clear();
    context->staging_buffer = nullptr;

    context->vertex_buffers.clear();
    context->vertex_buffer = nullptr;
  }
};

struct ConfigureShaders : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    return true;
  }

  void on_deactivate() override
  {
  }
};

struct ConfigureMaterials : ContextOperation<VulkanContext>
{
  bool on_activate() override
  {
    return true;
  }

  void on_deactivate() override
  {
    context->shaders.clear();
    context->textures.clear();
    context->materials.clear();
  }
};

void VulkanContext::configure_operations()
{
  Context::configure_operations();

  add_operation( "configure.shaders",            new ConfigureShaders() );
  add_operation( "configure.materials",          new ConfigureMaterials() );
  add_operation( "render.begin",                 new BalefireRenderBegin() );
}

void VulkanContext::on_surface_size_change( int width, int height )
{
  window->width = width;
  window->height = height;
}
