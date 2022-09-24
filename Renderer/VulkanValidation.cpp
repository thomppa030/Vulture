#include "pch.h"
#include "VulkanValidation.h"

VulkanValidation::VulkanValidation()
{
    if (checkValidationLayerSupport())
    {
        std::cout << "Validation layers supported" << std::endl;
    }
    else
    {
        std::cout << "Validation layers not supported" << std::endl;
    }
}

bool VulkanValidation::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers)
    {
        if (!checkLayerSupport(layerName))
        {
            return false;
        }
    }

    return true;
}


bool VulkanValidation::checkLayerSupport(const char* layerName)
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const auto& layerProperties : availableLayers)
    {
        if (strcmp(layerName, layerProperties.layerName) == 0)
        {
            return true;
        }
    }

    return false;
}