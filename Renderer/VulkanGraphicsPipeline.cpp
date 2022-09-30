#include "pch.h"
#include "VulkanGraphicsPipeline.h"
#include "VulkanDevice.h"
#include "VulkanShader.h"


VulkanGraphicsPipeline::VulkanGraphicsPipeline()
{
    SCOPED_TIMER;
    createGraphicsPipeline();
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline()
{
    SCOPED_TIMER;
    vkDestroyPipelineLayout(VulkanLogicalDevice::GetLogicalDevice(), m_PipelineLayout, nullptr);
    vkDestroyPipeline(VulkanLogicalDevice::GetLogicalDevice(), m_GraphicsPipeline, nullptr);
}

void VulkanGraphicsPipeline::createGraphicsPipeline()
{
    SCOPED_TIMER;
    std::string vertexShaderPath = "shaders/vert.spv";
    std::string fragmentShaderPath = "shaders/frag.spv";

    auto vertShaderCode = VulkanShaderUtils::ReadFile(vertexShaderPath);
    auto fragShaderCode = VulkanShaderUtils::ReadFile(fragmentShaderPath);

    auto vertShaderModule = VulkanShaderUtils::createShaderModule(vertShaderCode);
    auto fragShaderModule = VulkanShaderUtils::createShaderModule(fragShaderCode);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    vkDestroyShaderModule(VulkanLogicalDevice::GetLogicalDevice(), vertShaderModule, nullptr);
    vkDestroyShaderModule(VulkanLogicalDevice::GetLogicalDevice(), fragShaderModule, nullptr);
}

