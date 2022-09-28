#ifndef VULKAN_UTILITIES_H
#define VULKAN_UTILITIES_H

#include "pch.h"

struct QueueFamilyIndices
{
    int32_t graphicsFamily{-1};
    int32_t presentFamily{-1};

    bool isComplete()
    {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

const bool IsDeviceSuitable(VkPhysicalDevice device);

#endif
