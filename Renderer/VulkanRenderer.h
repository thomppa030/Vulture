#ifndef VULKA_RENDERER_H
#define VULKA_RENDERER_H
#include "pch.h"

class VulkanRenderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void Run();
    void RenderLoop();
    void Shutdown();

private:
    std::shared_ptr<class VulkanInstance> m_VulkanInstance;
    std::shared_ptr<class VulkanWindow> m_VulkanWindow;
    // std::shared_ptr<class VulkanDebugMessenger> m_VulkanDebugMessenger;
};

#endif // VULKA_RENDERER_H
