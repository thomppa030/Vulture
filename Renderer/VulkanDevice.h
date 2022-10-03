#ifndef VULKADEVICE_H
#define VULKADEVICE_H

#include "pch.h"

typedef struct
{
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkQueue transferQueue;
    VkQueue computeQueue;
    VkQueue sparseBindingQueue;
    VkQueue protectedQueue;
    VkQueue videoDecodeQueue;
    VkQueue videoEncodeQueue;
    VkQueue videoQueue;
} VulkanDevice;

class VulkanPhysicalDevice
{
public:
    VulkanPhysicalDevice();
    ~VulkanPhysicalDevice();

    void PickPhysicalDevice();

    static VkPhysicalDevice GetPhysicalDevice()
    {
        return m_PhysicalDevice;
    }

private:
    inline static VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
};

class VulkanLogicalDevice
{
public:
    VulkanLogicalDevice();
    ~VulkanLogicalDevice();

    void CreateLogicalDevice();

    static VkDevice GetLogicalDevice()
    {
        return m_LogicalDevice;
    }

    VkQueue GetGraphicsQueue()
    {
        return m_GraphicsQueue;
    }

    VkQueue GetPresentQueue()
    {
        return m_PresentQueue;
    }

private:
    VkSurfaceKHR m_Surface;
    VkPhysicalDevice m_PhysicalDevice;
    inline static VkDevice m_LogicalDevice;

    VkQueue m_GraphicsQueue;
    VkQueue m_PresentQueue;
};

#endif // VULKADEVICE_H
