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
    VulkanPhysicalDevice(VkInstance instance);
    ~VulkanPhysicalDevice();

    void PickPhysicalDevice(VkInstance instance);
    void CreateLogicalDevice();

    VkPhysicalDevice GetPhysicalDevice()
    {
        return m_PhysicalDevice;
    }

private:
    VkInstance m_Instance;
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
};

class VulkanLogicalDevice
{
public:
    VulkanLogicalDevice(VkInstance instance);
    ~VulkanLogicalDevice();

    void CreateLogicalDevice(VkPhysicalDevice physicalDevice);

    VkDevice GetLogicalDevice()
    {
        return m_LogicalDevice;
    }

private:
    VkInstance m_Instance;
    VkPhysicalDevice m_PhysicalDevice;
    VkDevice m_LogicalDevice;
    VkQueue m_GraphicsQueue;
};

#endif // VULKADEVICE_H
