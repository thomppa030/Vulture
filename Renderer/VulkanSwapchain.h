#ifndef VULKAN_SWAPCHAIN_H
#define VULKAN_SWAPCHAIN_H

#include "pch.h"


class VulkanSwapchain {

    public:
        VulkanSwapchain(GLFWwindow *window);
        ~VulkanSwapchain();

        void CreateSwapchain(GLFWwindow *window);

        VkSwapchainKHR GetSwapchain()
        {
            return m_Swapchain;
        }

        std::vector<VkImage> GetSwapchainImages()
        {
            return m_SwapchainImages;
        }

    private:
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
        VkFormat FindSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat FindDepthFormat();
        bool HasStencilComponent(VkFormat format);

        GLFWwindow *m_Window;

        VkSwapchainKHR m_Swapchain;
        std::vector<VkImage> m_SwapchainImages;

        VkFormat m_SwapchainImageFormat;
        VkExtent2D m_SwapchainExtent;
        std::vector<VkImageView> m_SwapchainImageViews;
};

#endif // VULKAN_SWAPCHAIN_H