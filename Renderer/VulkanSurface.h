#ifndef VULKAN_SURFACE_H
#define VULKAN_SURFACE_H

#include "VulkanInstance.h"
#include "pch.h"

class VulkanSurface
{
public:
    VulkanSurface(GLFWwindow *window);
    ~VulkanSurface();

    static VkSurfaceKHR GetSurface()
    {
        return m_Surface;
    }

private:
    inline static VkSurfaceKHR m_Surface;
};

#endif // VULKAN_SURFACE_H