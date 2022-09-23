#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
	
class VulkanInstance {

public:
    VulkanInstance();
    ~VulkanInstance();

    void createInstance();
    VkInstance GetInstance() const { return m_Instance; }


private:
    VkInstance m_Instance;
};
