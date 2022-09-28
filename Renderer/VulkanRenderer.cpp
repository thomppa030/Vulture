#include "pch.h"
#include "VulkanRenderer.h"
#include "VulkanInstance.h"

VulkanRenderer::VulkanRenderer()
{
    SCOPED_TIMER;
    
    initWindow();
    m_VulkanInstance = std::make_shared<VulkanInstance>(m_Window);
}

VulkanRenderer::~VulkanRenderer()
{
}

void VulkanRenderer::initWindow()
{
    SCOPED_TIMER;
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(1920, 1080, "Vulkan", nullptr, nullptr);
}

void VulkanRenderer::Run()
{
    SCOPED_TIMER;
    RenderLoop();
    Shutdown();
}

void VulkanRenderer::RenderLoop()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();
    }
    {
        glfwPollEvents();
    }
}

void VulkanRenderer::Shutdown()
{
}
