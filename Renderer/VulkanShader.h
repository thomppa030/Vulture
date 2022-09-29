#ifndef VULKAN_SHADER_H
#define VULKAN_SHADER_H

#include "pch.h"

class VulkanShader
{
public:
    VulkanShader(std::string shaderPath);
    ~VulkanShader();

    static VkShaderModule createShaderModule(const std::vector<char> &code);

    VkShaderModule getShaderModule() const
    {
        return m_ShaderModule;
    }

    std::vector<char> ReadFile(const std::string &filename);

private:

    std::string m_ShaderPath;
    VkShaderModule m_ShaderModule;
};

#endif // VULKAN_SHADER_H