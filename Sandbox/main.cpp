#include <iostream>
#include <VulkanRenderer.h>
#include <fmt/format.h>
#include <memory>

int main() {

	std::unique_ptr<VulkanRenderer> renderer = std::make_unique<VulkanRenderer>();

	renderer->Run();
}
