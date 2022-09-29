#ifndef VULKAN_GRAPHICS_PIPELINE_H
#define VULKAN_GRAPHICS_PIPELINE_H

#include "pch.h"

class VulkanGraphicsPipeline
{

public:
    VulkanGraphicsPipeline();
    ~VulkanGraphicsPipeline();

    void createGraphicsPipeline();

private:
    VkPipelineLayout m_PipelineLayout;
    VkPipeline m_GraphicsPipeline;
};


#endif // VULKAN_GRAPHICS_PIPELINE_H