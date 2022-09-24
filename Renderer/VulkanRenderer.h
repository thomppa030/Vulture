class VulkanRenderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void Run();
    void RenderLoop();
    void Shutdown();

private:
    class VulkanInstance *m_VulkanInstance;
    class VulkanWindow *m_VulkanWindow;
    class VulkanDebugMessenger *m_VulkanDebugMessenger;
};
