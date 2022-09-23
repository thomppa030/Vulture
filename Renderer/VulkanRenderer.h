class VulkanRenderer
{
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void Init();
    void Run();
    void RenderLoop();
    void Shutdown();

private:

    class VulkanInstance* m_VulkanInstance;
    class VulkanWindow* m_VulkanWindow;
};

   
