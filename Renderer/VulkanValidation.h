#ifndef VULKAN_VALIDATION_H
#define VULKAN_VALIDATION_H
#include "pch.h"

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanValidation {

    public:
        VulkanValidation();
        ~VulkanValidation() = default;

        bool checkValidationLayerSupport();

    private:
        bool checkLayerSupport(const char* layerName);
};

#endif // VULKAN_VALIDATION_H