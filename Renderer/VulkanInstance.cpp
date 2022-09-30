#include "pch.h"
#include "VulkanInstance.h"
#include "VulkanDebugMessenger.h"
#include "VulkanDevice.h"
#include "VulkanValidation.h"
#include "VulkanSurface.h"
#include "VulkanSwapchain.h"
#include "VulkanGraphicsPipeline.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

VulkanInstance::VulkanInstance(GLFWwindow *window)
    : m_Window(window)
{
    SCOPED_TIMER;
    createInstance();
    m_VulkanDebugMessenger = new VulkanDebugMessenger();
    m_VulkanSurface = new VulkanSurface(m_Window);
    m_VulkanPhysicalDevice = new VulkanPhysicalDevice();
    m_VulkanLogicalDevice = new VulkanLogicalDevice();
    m_VulkanSwapchain = new VulkanSwapchain(m_Window);
    m_VulkanGraphicsPipeline = new VulkanGraphicsPipeline();
}

VulkanInstance::~VulkanInstance()
{
    SCOPED_TIMER;
    for (auto && imageView : m_VulkanSwapchain->GetSwapchainImageViews())
    {
        vkDestroyImageView(m_VulkanLogicalDevice->GetLogicalDevice(), imageView, nullptr);
    }  
    delete m_VulkanSwapchain;
    delete m_VulkanGraphicsPipeline;
    delete m_VulkanDebugMessenger;
    delete m_VulkanLogicalDevice;
    delete m_VulkanSurface;
    vkDestroyInstance(m_Instance, nullptr);
}


std::vector<const char *> getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void VulkanInstance::createInstance()
{
    SCOPED_TIMER;

    auto validation = new VulkanValidation();

    if (enableValidationLayers && !validation->checkValidationLayerSupport())
    {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        m_VulkanDebugMessenger->PopulateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance!");
    }
}