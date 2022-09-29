#ifndef VULKAN_UTILITIES_H
#define VULKAN_UTILITIES_H

#include "pch.h"

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices
{
    uint32_t graphicsFamily{0};
    uint32_t presentFamily{0};

    bool isComplete()
    {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

const bool IsDeviceSuitable(VkPhysicalDevice device);
bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

#endif
