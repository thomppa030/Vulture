#include "VulkanShader.h"
#include "VulkanDevice.h"
#include "pch.h"
#include <fstream>

VulkanShaderUtils::VulkanShaderUtils()
{
}

VulkanShaderUtils::~VulkanShaderUtils()
{

}

std::vector<char> VulkanShaderUtils::ReadFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file! at: " + filename);
    }

    size_t fileSize = (size_t)file.tellg();
    std::cout << "File size: " << fileSize << std::endl;
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

VkShaderModule VulkanShaderUtils::createShaderModule(const std::vector<char> &code)
{
    SCOPED_TIMER;
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(VulkanLogicalDevice::GetLogicalDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}