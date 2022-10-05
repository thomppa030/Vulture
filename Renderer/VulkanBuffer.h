//
// Created by thomppa on 10/5/22.
//
#ifndef VULKANRENDERER_VULKANBUFFER_H
#define VULKANRENDERER_VULKANBUFFER_H

#include "pch.h"
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec2 Position;
    glm::vec3 Color;

    static VkVertexInputBindingDescription GetBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
    {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, Position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, Color);

        return attributeDescriptions;
    }
};

class VulkanVertexBuffer
{
public:
    VulkanVertexBuffer(std::vector<Vertex> vertices);
    ~VulkanVertexBuffer();

    void createVertexBuffer(std::vector<Vertex> vertices);
    void cleanup();

    VkBuffer GetVertexBuffer() const { return m_VertexBuffer; }
    VkDeviceMemory GetVertexBufferMemory() const { return m_VertexBufferMemory; }

private:
    VkBuffer m_VertexBuffer;
    VkDeviceMemory m_VertexBufferMemory;
};


#endif //VULKANRENDERER_VULKANBUFFER_H
