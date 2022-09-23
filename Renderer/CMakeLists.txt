set(RENDERER_SOURCES
	"VulkanInstance.cpp"
	"VulkanRenderer.cpp"
	"VulkanWindow.cpp")

set(RENDERER_HEADERS
	"VulkanInstance.h"
	"VulkanRenderer.h"
	"VulkanWindow.h")

set(RENDERER_INCLUDES
	"../build/_deps/glfw-src/include"
	"${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Vulkan REQUIRED)

add_library(Renderer STATIC 
	${RENDERER_SOURCES} 
	${RENDERER_HEADERS})

target_include_directories(Renderer PUBLIC 
	${RENDERER_INCLUDES}
	${Vulkan_INCLUDE_DIRS})

target_link_libraries(Renderer PUBLIC
	glfw
	Vulkan::Vulkan)

