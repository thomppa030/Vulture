#include "pch.h"
#include "VulkanRenderer.h"
#include "VulkanInstance.h"
#include "VulkanWindow.h"
#include "VulkanDebugMessenger.h"

VulkanRenderer::VulkanRenderer()
{
    SCOPED_TIMER;
    m_VulkanInstance = std::make_shared<VulkanInstance>();
    m_VulkanWindow =  std::make_shared<VulkanWindow>();
}

VulkanRenderer::~VulkanRenderer()
{
}

void VulkanRenderer::Run()
{
    SCOPED_TIMER;
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
