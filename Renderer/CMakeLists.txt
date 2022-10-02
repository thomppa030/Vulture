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

set(source "${PROJECT_SOURCE_DIR}/shaders")
set(destination "${PROJECT_BINARY_DIR}/Sandbox/shaders")

# Compile shaders
# add_custom_command(TARGET Renderer PRE_BUILD

# COMMAND /bin/sh ${PROJECT_SOURCE_DIR}/shaders/compileShader.sh)

add_custom_command(TARGET Renderer
COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
DEPENDS ${destination}
COMMENT "symbolic link resource folder from ${source} => ${destination}")

target_include_directories(Renderer PUBLIC 
	${RENDERER_INCLUDES}
	${Vulkan_INCLUDE_DIRS})

target_link_libraries(Renderer PUBLIC
	glfw
	fmt::fmt
	Vulkan::Vulkan)

target_precompile_headers(Renderer PRIVATE "pch.h")

