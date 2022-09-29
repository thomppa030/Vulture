#include "VulkanShader.h"
#include "VulkanDevice.h"
#include "pch.h"
#include <fstream>

VulkanShader::VulkanShader(std::string shaderPath)
    : m_ShaderPath(shaderPath)
{
    std::vector<char> ShaderCode = ReadFile(m_ShaderPath);

    m_ShaderModule = createShaderModule(ShaderCode);
}

VulkanShader::~VulkanShader()
{
    vkDestroyShaderModule(VulkanLogicalDevice::GetLogicalDevice(), m_ShaderModule, nullptr);
}

VkShaderModule VulkanShader::createShaderModule(const std::vector<char> &code)
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(VulkanLogicalDevice::GetLogicalDevice(), &createInfo, nullptr, &shaderModule) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create shader module!");
    }

    return shaderModule;
}

std::vector<char> VulkanShader::ReadFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}