cmake_minimum_required(VERSION 3.0.0)
project(VulkanRenderer VERSION 0.1.0)

include(CTest)
include(FetchContent)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(FetchList)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(Renderer)
add_subdirectory(Sandbox)
