#include <GLFW/glfw3.h>
#include "VulkanWindow.h"

VulkanWindow::VulkanWindow()
{
    InitWindow();
}

VulkanWindow::~VulkanWindow()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}


void VulkanWindow::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(1920, 1080, "Vulkan", nullptr, nullptr);
}
