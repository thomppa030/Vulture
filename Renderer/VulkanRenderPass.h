#ifndef VULKAN_RENDER_PASS_H
#define VULKAN_RENDER_PASS_H

#include "pch.h"

class VulkanRenderPass
{
public:
    VulkanRenderPass();
    ~VulkanRenderPass();

    void createRenderPass();

private:
    inline static VkRenderPass m_RenderPass;
};

#endif // VULKAN_RENDER_PASS_H