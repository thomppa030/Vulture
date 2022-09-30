#ifndef VULKAN_SHADER_UTILS_H
#define VULKAN_SHADER_UTILS_H

#include "pch.h"

class VulkanShaderUtils
{
public:
    VulkanShaderUtils();
    ~VulkanShaderUtils();

    static std::vector<char> ReadFile(const std::string &filename);

    static VkShaderModule createShaderModule(const std::vector<char> &code);

private:

};

#endif // VULKAN_SHADER_UTILS_H