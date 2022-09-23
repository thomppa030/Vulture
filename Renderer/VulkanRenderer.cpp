#include "VulkanRenderer.h"
#include "VulkanInstance.h"
#include "VulkanWindow.h"

VulkanRenderer::VulkanRenderer()
{
    m_VulkanInstance = new VulkanInstance();
    m_VulkanWindow = new VulkanWindow();
}

VulkanRenderer::~VulkanRenderer()
{
    delete m_VulkanInstance;
    delete m_VulkanWindow;
}

void VulkanRenderer::Init()
{
}

void VulkanRenderer::Run()
{
   Init();
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

