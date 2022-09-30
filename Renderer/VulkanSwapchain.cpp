#include "VulkanSwapchain.h"
#include "VulkanDevice.h"
#include "VulkanSurface.h"
#include "pch.h"
#include "utilities.h"

VulkanSwapchain::VulkanSwapchain(GLFWwindow *window) : m_Window(window)
{
    SCOPED_TIMER;
    CreateSwapchain(m_Window);
    CreateImageViews();
}

VulkanSwapchain::~VulkanSwapchain()
{
    SCOPED_TIMER;
    vkDestroySwapchainKHR(VulkanLogicalDevice::GetLogicalDevice(), m_Swapchain, nullptr);
}


/**
 * If the available formats contain a format that is VK_FORMAT_B8G8R8A8_SRGB and the color space is
 * VK_COLOR_SPACE_SRGB_NONLINEAR_KHR, then return that format. Otherwise, return the first available
 * format
 * 
 * @param availableFormats The list of available formats that the swapchain can use.
 * 
 * @return The first available format.
 */
VkSurfaceFormatKHR VulkanSwapchain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
    SCOPED_TIMER;
    for (const auto &availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

/**
 * If the swapchain supports the mailbox present mode, use it. Otherwise, use the FIFO present mode
 * 
 * @param availablePresentModes The list of available present modes.
 * 
 * @return The swapchain present mode.
 */
VkPresentModeKHR VulkanSwapchain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
{
    SCOPED_TIMER;
    for (const auto &availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

/**
 * If the swapchain extent is defined, use it. Otherwise, use the window size
 * 
 * @param capabilities The capabilities of the surface.
 * 
 * @return The swap extent is the resolution of the swap chain images.
 */
VkExtent2D VulkanSwapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
    SCOPED_TIMER;
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }
    else
    {
        int width, height;
        glfwGetFramebufferSize(m_Window, &width, &height);

        VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

        actualExtent.width = std::max(capabilities.minImageExtent.width,
                                      std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height,
                                       std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

void VulkanSwapchain::CreateSwapchain(GLFWwindow *window)
{
    SCOPED_TIMER;
    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(VulkanPhysicalDevice::GetPhysicalDevice());

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

    /* Getting the number of images in the swapchain. */
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = VulkanSurface::GetSurface();

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    /* Getting the queue family indices for the graphics and present queues. */
    QueueFamilyIndices indices = FindQueueFamilies(VulkanPhysicalDevice::GetPhysicalDevice());
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};

    /* If the graphics and present queues are different, we need to specify that we want to use concurrent
mode. */
    if (indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;     // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(VulkanLogicalDevice::GetLogicalDevice(), &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    /* Getting the swapchain images and the format and extent of the swapchain. */
    vkGetSwapchainImagesKHR(VulkanLogicalDevice::GetLogicalDevice(), m_Swapchain, &imageCount, nullptr);
    m_SwapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(VulkanLogicalDevice::GetLogicalDevice(),
                            m_Swapchain,
                            &imageCount,
                            m_SwapchainImages.data());

    m_SwapchainImageFormat = surfaceFormat.format;
    m_SwapchainExtent = extent;
}

void VulkanSwapchain::CreateImageViews()
{
    SCOPED_TIMER;
    m_SwapchainImageViews.resize(m_SwapchainImages.size());

    for (size_t i = 0; i < m_SwapchainImages.size(); i++)
    {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = m_SwapchainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = m_SwapchainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(VulkanLogicalDevice::GetLogicalDevice(), &createInfo, nullptr, &m_SwapchainImageViews[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
        }
    }

    std::cout << "Created " << m_SwapchainImageViews.size() << " swapchain image views." << std::endl;
}


