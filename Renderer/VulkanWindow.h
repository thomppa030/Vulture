class GLFWwindow;

class VulkanWindow
{
public:
    VulkanWindow();
    ~VulkanWindow();

    void InitWindow();
    GLFWwindow* GetWindow() const { return m_Window; }

private:
    GLFWwindow* m_Window;
};

