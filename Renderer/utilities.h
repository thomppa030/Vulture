#ifndef VULKAN_UTILITIES_H
#define VULKAN_UTILITIES_H

#include "pch.h"
#include <optional>

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

const bool IsDeviceSuitable(VkPhysicalDevice device);

#endif
