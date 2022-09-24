#include "pch.h"
#include "VulkanRenderer.h"
#include "VulkanWindow.h"
#include "VulkanDebugMessenger.h"

VulkanRenderer::VulkanRenderer()
{
    m_VulkanInstance = new VulkanInstance();
    m_VulkanWindow = new VulkanWindow();
    m_VulkanDebugMessenger = new VulkanDebugMessenger(m_VulkanInstance->GetInstance());
}

VulkanRenderer::~VulkanRenderer()
{
    delete m_VulkanInstance;
    delete m_VulkanWindow;
}

void VulkanRenderer::Run()
{
    RenderLoop();
    Shutdown();
}

void VulkanRenderer::RenderLoop()
{
    while (!glfwWindowShouldClose(m_VulkanWindow->GetWindow()))
    {
        glfwPollEvents();
    }
}

void VulkanRenderer::Shutdown()
{
}
