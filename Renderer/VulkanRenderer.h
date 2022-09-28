#ifndef VULKA_RENDERER_H
#define VULKA_RENDERER_H
#include "pch.h"

class VulkanRenderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void initWindow();
    void Run();
    void RenderLoop();
    void Shutdown();

private:
    std::shared_ptr<class VulkanInstance> m_VulkanInstance;
    GLFWwindow *m_Window;
};

#endif // VULKA_RENDERER_H
