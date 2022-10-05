#include "pch.h"

#include "VulkanDevice.h"
#include "VulkanValidation.h"
#include "VulkanInstance.h"
#include "utilities.h"


VulkanPhysicalDevice::VulkanPhysicalDevice()
{
    SCOPED_TIMER;
    PickPhysicalDevice();
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

void VulkanPhysicalDevice::PickPhysicalDevice()
{
    SCOPED_TIMER;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(VulkanInstance::GetInstance(), &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(VulkanInstance::GetInstance(), &deviceCount, devices.data());

    for (const auto &device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            m_PhysicalDevice = device;
            break;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    std::cout << "Physical Device found" << std::endl;
}

VulkanLogicalDevice::VulkanLogicalDevice()
{
    SCOPED_TIMER;
    CreateLogicalDevice();
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
    SCOPED_TIMER;
    vkDestroyDevice(m_LogicalDevice, nullptr);
}

void VulkanLogicalDevice::CreateLogicalDevice()
{
    SCOPED_TIMER;
    QueueFamilyIndices indices = FindQueueFamilies(VulkanPhysicalDevice::GetPhysicalDevice());

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(VulkanPhysicalDevice::GetPhysicalDevice(), &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_LogicalDevice, indices.graphicsFamily, 0, &m_GraphicsQueue);
    vkGetDeviceQueue(m_LogicalDevice, indices.presentFamily, 0, &m_PresentQueue);
}

uint32_t VulkanLogicalDevice::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    SCOPED_TIMER;
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(VulkanPhysicalDevice::GetPhysicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
    {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}
