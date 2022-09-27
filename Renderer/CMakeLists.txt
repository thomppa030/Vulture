file(GLOB SRC_FILES *.cpp)
file(GLOB HDR_FILES *.h)

set(RENDERER_INCLUDES
	"../build/_deps/glfw-src/include"
	"../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Vulkan REQUIRED)

add_library(Renderer STATIC 
	${SRC_FILES} 
	${HDR_FILES})

target_include_directories(Renderer PUBLIC 
	${RENDERER_INCLUDES}
	${Vulkan_INCLUDE_DIRS})

target_link_libraries(Renderer PUBLIC
	glfw
	fmt::fmt
	Vulkan::Vulkan)

target_precompile_headers(Renderer PRIVATE "pch.h")

