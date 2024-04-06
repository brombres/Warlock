#include "VkBootstrap.h"
#include "Vulkanize/Vulkanize.h"
using namespace VKZ;

extern const Byte vertex_spv[1476];
extern const Byte fragment_spv[536];

ConfigureGraphicsPipeline::ConfigureGraphicsPipeline( Context* context ) : context(context)
{
}

bool ConfigureGraphicsPipeline::activate()
{
  VkShaderModule vertex_module =
      _create_shader_module( vertex_spv, sizeof(vertex_spv) );
  VkShaderModule fragment_module =
      _create_shader_module( fragment_spv, sizeof(fragment_spv) );

  if (vertex_module == VK_NULL_HANDLE || fragment_module == VK_NULL_HANDLE)
  {
    return false;
  }

  VkPipelineShaderStageCreateInfo vertex_stage_info = {};
  vertex_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertex_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertex_stage_info.module = vertex_module;
  vertex_stage_info.pName = "main";

  VkPipelineShaderStageCreateInfo fragment_stage_info = {};
  fragment_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragment_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragment_stage_info.module = fragment_module;
  fragment_stage_info.pName = "main";

  VkPipelineShaderStageCreateInfo shader_stages[] =
      { vertex_stage_info, fragment_stage_info };

  VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = 0;
  vertex_input_info.vertexAttributeDescriptionCount = 0;

  VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width  = context->surface_size.width;
  viewport.height = context->surface_size.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = { 0, 0 };
  scissor.extent = context->surface_size;

  VkPipelineViewportStateCreateInfo viewport_state = {};
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;

  VkPipelineMultisampleStateCreateInfo multisampling = {};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineColorBlendAttachmentState color_blend_attachment = {};
  color_blend_attachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;

  VkPipelineColorBlendStateCreateInfo color_blending = {};
  color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending.logicOpEnable = VK_FALSE;
  color_blending.logicOp = VK_LOGIC_OP_COPY;
  color_blending.attachmentCount = 1;
  color_blending.pAttachments = &color_blend_attachment;
  color_blending.blendConstants[0] = 0.0f;
  color_blending.blendConstants[1] = 0.0f;
  color_blending.blendConstants[2] = 0.0f;
  color_blending.blendConstants[3] = 0.0f;

  VkPipelineLayoutCreateInfo pipeline_layout_info = {};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 0;
  pipeline_layout_info.pushConstantRangeCount = 0;

  VKZ_REQUIRE(
    "creating pipeline layout",
    context->device_dispatch.createPipelineLayout(
      &pipeline_layout_info, nullptr, &context->pipeline_layout
    )
  );

  std::vector<VkDynamicState> dynamic_states =
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
    VK_DYNAMIC_STATE_DEPTH_BIAS
  };

  VkPipelineDynamicStateCreateInfo dynamic_info = {};
  dynamic_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_info.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
  dynamic_info.pDynamicStates = dynamic_states.data();

  VkGraphicsPipelineCreateInfo pipeline_info = {};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = 2;
  pipeline_info.pStages = shader_stages;
  pipeline_info.pVertexInputState = &vertex_input_info;
  pipeline_info.pInputAssemblyState = &input_assembly;
  pipeline_info.pViewportState = &viewport_state;
  pipeline_info.pRasterizationState = &rasterizer;
  pipeline_info.pMultisampleState = &multisampling;
  pipeline_info.pColorBlendState = &color_blending;
  pipeline_info.pDynamicState = &dynamic_info;
  pipeline_info.layout = context->pipeline_layout;
  pipeline_info.renderPass = context->render_pass;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

  VKZ_REQUIRE(
    "creating graphics pipeline",
    context->device_dispatch.createGraphicsPipelines(
      VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &context->graphics_pipeline
    )
  );

  context->device_dispatch.destroyShaderModule( fragment_module, nullptr );
  context->device_dispatch.destroyShaderModule( vertex_module, nullptr );
  return true;
}

void ConfigureGraphicsPipeline::deactivate()
{
  context->device_dispatch.destroyPipeline( context->graphics_pipeline, nullptr );
  context->device_dispatch.destroyPipelineLayout( context->pipeline_layout, nullptr );
}

VkShaderModule ConfigureGraphicsPipeline::_create_shader_module( const Byte* code, int count )
{
  VkShaderModuleCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info.codeSize = count;
  create_info.pCode = (const uint32_t*)code;

  VkShaderModule shader_module;
  VKZ_ON_ERROR(
    "creating shader module",
    context->device_dispatch.createShaderModule( &create_info, nullptr, &shader_module ),
    return VK_NULL_HANDLE;
  );

  return shader_module;
}

const Byte vertex_spv[] =
{
  3, 2, 35, 7, 0, 5, 1, 0, 11, 0, 8, 0, 54, 0, 0, 0,
  0, 0, 0, 0, 17, 0, 2, 0, 1, 0, 0, 0, 11, 0, 6, 0,
  1, 0, 0, 0, 71, 76, 83, 76, 46, 115, 116, 100, 46, 52, 53, 48,
  0, 0, 0, 0, 14, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  15, 0, 10, 0, 0, 0, 0, 0, 4, 0, 0, 0, 109, 97, 105, 110,
  0, 0, 0, 0, 12, 0, 0, 0, 23, 0, 0, 0, 34, 0, 0, 0,
  38, 0, 0, 0, 49, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0,
  194, 1, 0, 0, 4, 0, 9, 0, 71, 76, 95, 65, 82, 66, 95, 115,
  101, 112, 97, 114, 97, 116, 101, 95, 115, 104, 97, 100, 101, 114, 95, 111,
  98, 106, 101, 99, 116, 115, 0, 0, 5, 0, 4, 0, 4, 0, 0, 0,
  109, 97, 105, 110, 0, 0, 0, 0, 5, 0, 5, 0, 12, 0, 0, 0,
  112, 111, 115, 105, 116, 105, 111, 110, 115, 0, 0, 0, 5, 0, 4, 0,
  23, 0, 0, 0, 99, 111, 108, 111, 114, 115, 0, 0, 5, 0, 6, 0,
  32, 0, 0, 0, 103, 108, 95, 80, 101, 114, 86, 101, 114, 116, 101, 120,
  0, 0, 0, 0, 6, 0, 6, 0, 32, 0, 0, 0, 0, 0, 0, 0,
  103, 108, 95, 80, 111, 115, 105, 116, 105, 111, 110, 0, 6, 0, 7, 0,
  32, 0, 0, 0, 1, 0, 0, 0, 103, 108, 95, 80, 111, 105, 110, 116,
  83, 105, 122, 101, 0, 0, 0, 0, 6, 0, 7, 0, 32, 0, 0, 0,
  2, 0, 0, 0, 103, 108, 95, 67, 108, 105, 112, 68, 105, 115, 116, 97,
  110, 99, 101, 0, 6, 0, 7, 0, 32, 0, 0, 0, 3, 0, 0, 0,
  103, 108, 95, 67, 117, 108, 108, 68, 105, 115, 116, 97, 110, 99, 101, 0,
  5, 0, 3, 0, 34, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0,
  38, 0, 0, 0, 103, 108, 95, 86, 101, 114, 116, 101, 120, 73, 110, 100,
  101, 120, 0, 0, 5, 0, 5, 0, 49, 0, 0, 0, 102, 114, 97, 103,
  67, 111, 108, 111, 114, 0, 0, 0, 72, 0, 5, 0, 32, 0, 0, 0,
  0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 72, 0, 5, 0,
  32, 0, 0, 0, 1, 0, 0, 0, 11, 0, 0, 0, 1, 0, 0, 0,
  72, 0, 5, 0, 32, 0, 0, 0, 2, 0, 0, 0, 11, 0, 0, 0,
  3, 0, 0, 0, 72, 0, 5, 0, 32, 0, 0, 0, 3, 0, 0, 0,
  11, 0, 0, 0, 4, 0, 0, 0, 71, 0, 3, 0, 32, 0, 0, 0,
  2, 0, 0, 0, 71, 0, 4, 0, 38, 0, 0, 0, 11, 0, 0, 0,
  42, 0, 0, 0, 71, 0, 4, 0, 49, 0, 0, 0, 30, 0, 0, 0,
  0, 0, 0, 0, 19, 0, 2, 0, 2, 0, 0, 0, 33, 0, 3, 0,
  3, 0, 0, 0, 2, 0, 0, 0, 22, 0, 3, 0, 6, 0, 0, 0,
  32, 0, 0, 0, 23, 0, 4, 0, 7, 0, 0, 0, 6, 0, 0, 0,
  2, 0, 0, 0, 21, 0, 4, 0, 8, 0, 0, 0, 32, 0, 0, 0,
  0, 0, 0, 0, 43, 0, 4, 0, 8, 0, 0, 0, 9, 0, 0, 0,
  3, 0, 0, 0, 28, 0, 4, 0, 10, 0, 0, 0, 7, 0, 0, 0,
  9, 0, 0, 0, 32, 0, 4, 0, 11, 0, 0, 0, 6, 0, 0, 0,
  10, 0, 0, 0, 59, 0, 4, 0, 11, 0, 0, 0, 12, 0, 0, 0,
  6, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0, 13, 0, 0, 0,
  0, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0, 14, 0, 0, 0,
  0, 0, 0, 191, 44, 0, 5, 0, 7, 0, 0, 0, 15, 0, 0, 0,
  13, 0, 0, 0, 14, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0,
  16, 0, 0, 0, 0, 0, 0, 63, 44, 0, 5, 0, 7, 0, 0, 0,
  17, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 0, 44, 0, 5, 0,
  7, 0, 0, 0, 18, 0, 0, 0, 14, 0, 0, 0, 16, 0, 0, 0,
  44, 0, 6, 0, 10, 0, 0, 0, 19, 0, 0, 0, 15, 0, 0, 0,
  17, 0, 0, 0, 18, 0, 0, 0, 23, 0, 4, 0, 20, 0, 0, 0,
  6, 0, 0, 0, 3, 0, 0, 0, 28, 0, 4, 0, 21, 0, 0, 0,
  20, 0, 0, 0, 9, 0, 0, 0, 32, 0, 4, 0, 22, 0, 0, 0,
  6, 0, 0, 0, 21, 0, 0, 0, 59, 0, 4, 0, 22, 0, 0, 0,
  23, 0, 0, 0, 6, 0, 0, 0, 43, 0, 4, 0, 6, 0, 0, 0,
  24, 0, 0, 0, 0, 0, 128, 63, 44, 0, 6, 0, 20, 0, 0, 0,
  25, 0, 0, 0, 24, 0, 0, 0, 13, 0, 0, 0, 13, 0, 0, 0,
  44, 0, 6, 0, 20, 0, 0, 0, 26, 0, 0, 0, 13, 0, 0, 0,
  24, 0, 0, 0, 13, 0, 0, 0, 44, 0, 6, 0, 20, 0, 0, 0,
  27, 0, 0, 0, 13, 0, 0, 0, 13, 0, 0, 0, 24, 0, 0, 0,
  44, 0, 6, 0, 21, 0, 0, 0, 28, 0, 0, 0, 25, 0, 0, 0,
  26, 0, 0, 0, 27, 0, 0, 0, 23, 0, 4, 0, 29, 0, 0, 0,
  6, 0, 0, 0, 4, 0, 0, 0, 43, 0, 4, 0, 8, 0, 0, 0,
  30, 0, 0, 0, 1, 0, 0, 0, 28, 0, 4, 0, 31, 0, 0, 0,
  6, 0, 0, 0, 30, 0, 0, 0, 30, 0, 6, 0, 32, 0, 0, 0,
  29, 0, 0, 0, 6, 0, 0, 0, 31, 0, 0, 0, 31, 0, 0, 0,
  32, 0, 4, 0, 33, 0, 0, 0, 3, 0, 0, 0, 32, 0, 0, 0,
  59, 0, 4, 0, 33, 0, 0, 0, 34, 0, 0, 0, 3, 0, 0, 0,
  21, 0, 4, 0, 35, 0, 0, 0, 32, 0, 0, 0, 1, 0, 0, 0,
  43, 0, 4, 0, 35, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0,
  32, 0, 4, 0, 37, 0, 0, 0, 1, 0, 0, 0, 35, 0, 0, 0,
  59, 0, 4, 0, 37, 0, 0, 0, 38, 0, 0, 0, 1, 0, 0, 0,
  32, 0, 4, 0, 40, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0,
  32, 0, 4, 0, 46, 0, 0, 0, 3, 0, 0, 0, 29, 0, 0, 0,
  32, 0, 4, 0, 48, 0, 0, 0, 3, 0, 0, 0, 20, 0, 0, 0,
  59, 0, 4, 0, 48, 0, 0, 0, 49, 0, 0, 0, 3, 0, 0, 0,
  32, 0, 4, 0, 51, 0, 0, 0, 6, 0, 0, 0, 20, 0, 0, 0,
  54, 0, 5, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 0, 0, 248, 0, 2, 0, 5, 0, 0, 0, 62, 0, 3, 0,
  12, 0, 0, 0, 19, 0, 0, 0, 62, 0, 3, 0, 23, 0, 0, 0,
  28, 0, 0, 0, 61, 0, 4, 0, 35, 0, 0, 0, 39, 0, 0, 0,
  38, 0, 0, 0, 65, 0, 5, 0, 40, 0, 0, 0, 41, 0, 0, 0,
  12, 0, 0, 0, 39, 0, 0, 0, 61, 0, 4, 0, 7, 0, 0, 0,
  42, 0, 0, 0, 41, 0, 0, 0, 81, 0, 5, 0, 6, 0, 0, 0,
  43, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 81, 0, 5, 0,
  6, 0, 0, 0, 44, 0, 0, 0, 42, 0, 0, 0, 1, 0, 0, 0,
  80, 0, 7, 0, 29, 0, 0, 0, 45, 0, 0, 0, 43, 0, 0, 0,
  44, 0, 0, 0, 13, 0, 0, 0, 24, 0, 0, 0, 65, 0, 5, 0,
  46, 0, 0, 0, 47, 0, 0, 0, 34, 0, 0, 0, 36, 0, 0, 0,
  62, 0, 3, 0, 47, 0, 0, 0, 45, 0, 0, 0, 61, 0, 4, 0,
  35, 0, 0, 0, 50, 0, 0, 0, 38, 0, 0, 0, 65, 0, 5, 0,
  51, 0, 0, 0, 52, 0, 0, 0, 23, 0, 0, 0, 50, 0, 0, 0,
  61, 0, 4, 0, 20, 0, 0, 0, 53, 0, 0, 0, 52, 0, 0, 0,
  62, 0, 3, 0, 49, 0, 0, 0, 53, 0, 0, 0, 253, 0, 1, 0,
  56, 0, 1, 0
};

const Byte fragment_spv[] =
{
  3, 2, 35, 7, 0, 5, 1, 0, 11, 0, 8, 0, 19, 0, 0, 0,
  0, 0, 0, 0, 17, 0, 2, 0, 1, 0, 0, 0, 11, 0, 6, 0,
  1, 0, 0, 0, 71, 76, 83, 76, 46, 115, 116, 100, 46, 52, 53, 48,
  0, 0, 0, 0, 14, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  15, 0, 7, 0, 4, 0, 0, 0, 4, 0, 0, 0, 109, 97, 105, 110,
  0, 0, 0, 0, 9, 0, 0, 0, 12, 0, 0, 0, 16, 0, 3, 0,
  4, 0, 0, 0, 7, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0,
  194, 1, 0, 0, 4, 0, 9, 0, 71, 76, 95, 65, 82, 66, 95, 115,
  101, 112, 97, 114, 97, 116, 101, 95, 115, 104, 97, 100, 101, 114, 95, 111,
  98, 106, 101, 99, 116, 115, 0, 0, 5, 0, 4, 0, 4, 0, 0, 0,
  109, 97, 105, 110, 0, 0, 0, 0, 5, 0, 5, 0, 9, 0, 0, 0,
  111, 117, 116, 67, 111, 108, 111, 114, 0, 0, 0, 0, 5, 0, 5, 0,
  12, 0, 0, 0, 102, 114, 97, 103, 67, 111, 108, 111, 114, 0, 0, 0,
  71, 0, 4, 0, 9, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0,
  71, 0, 4, 0, 12, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0,
  19, 0, 2, 0, 2, 0, 0, 0, 33, 0, 3, 0, 3, 0, 0, 0,
  2, 0, 0, 0, 22, 0, 3, 0, 6, 0, 0, 0, 32, 0, 0, 0,
  23, 0, 4, 0, 7, 0, 0, 0, 6, 0, 0, 0, 4, 0, 0, 0,
  32, 0, 4, 0, 8, 0, 0, 0, 3, 0, 0, 0, 7, 0, 0, 0,
  59, 0, 4, 0, 8, 0, 0, 0, 9, 0, 0, 0, 3, 0, 0, 0,
  23, 0, 4, 0, 10, 0, 0, 0, 6, 0, 0, 0, 3, 0, 0, 0,
  32, 0, 4, 0, 11, 0, 0, 0, 1, 0, 0, 0, 10, 0, 0, 0,
  59, 0, 4, 0, 11, 0, 0, 0, 12, 0, 0, 0, 1, 0, 0, 0,
  43, 0, 4, 0, 6, 0, 0, 0, 14, 0, 0, 0, 0, 0, 128, 63,
  54, 0, 5, 0, 2, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 0, 0, 248, 0, 2, 0, 5, 0, 0, 0, 61, 0, 4, 0,
  10, 0, 0, 0, 13, 0, 0, 0, 12, 0, 0, 0, 81, 0, 5, 0,
  6, 0, 0, 0, 15, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0,
  81, 0, 5, 0, 6, 0, 0, 0, 16, 0, 0, 0, 13, 0, 0, 0,
  1, 0, 0, 0, 81, 0, 5, 0, 6, 0, 0, 0, 17, 0, 0, 0,
  13, 0, 0, 0, 2, 0, 0, 0, 80, 0, 7, 0, 7, 0, 0, 0,
  18, 0, 0, 0, 15, 0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0,
  14, 0, 0, 0, 62, 0, 3, 0, 9, 0, 0, 0, 18, 0, 0, 0,
  253, 0, 1, 0, 56, 0, 1, 0
};

