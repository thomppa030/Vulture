#include "pch.h"
#include "VulkanSurface.h"


VulkanSurface::VulkanSurface(GLFWwindow *window)
{
    SCOPED_TIMER;
    if (glfwCreateWindowSurface(VulkanInstance::GetInstance(), window, nullptr, &m_Surface) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create window surface!");
    }
    std::cout << "Surface created" << std::endl;
}

VulkanSurface::~VulkanSurface()
{
    SCOPED_TIMER;
    vkDestroySurfaceKHR(VulkanInstance::GetInstance(), m_Surface, nullptr);
}