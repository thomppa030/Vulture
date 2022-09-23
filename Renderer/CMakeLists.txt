set(RENDERER_SOURCES
	"VulkanInstance.cpp")

set(RENDERER_HEADERS
	"VulkanInstance.h")

set(RENDERER_INCLUDES
	"../include/GLFW/"
	"${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Renderer STATIC 
	${RENDERER_SOURCES} 
	${RENDERER_HEADERS})

target_include_directories(Renderer PUBLIC 
	${RENDERER_INCLUDES})

target_link_libraries(Renderer STATIC
	glfw)

