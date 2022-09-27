#include "VulkanDevice.h"
#include "utilities.h"
#include "VulkanValidation.h"

#include "pch.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(VkInstance instance)
{
    SCOPED_TIMER;
    m_Instance = instance;
    PickPhysicalDevice(m_Instance);
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

void VulkanPhysicalDevice::PickPhysicalDevice(VkInstance instance)
{
    SCOPED_TIMER;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

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

VulkanLogicalDevice::VulkanLogicalDevice(VkInstance instance)
{
    SCOPED_TIMER;
    m_Instance = instance;
    m_PhysicalDevice = VulkanPhysicalDevice(m_Instance).GetPhysicalDevice();
    CreateLogicalDevice(m_PhysicalDevice);
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
    SCOPED_TIMER;
    vkDestroyDevice(m_LogicalDevice, nullptr);
}

void VulkanLogicalDevice::CreateLogicalDevice(VkPhysicalDevice physicalDevice)
{
    SCOPED_TIMER;
    QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;

        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(m_LogicalDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
}
