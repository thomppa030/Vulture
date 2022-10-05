//
// Created by thomppa on 10/5/22.
//

#include "pch.h"
#include "VulkanBuffer.h"
#include "VulkanDevice.h"


VulkanVertexBuffer::VulkanVertexBuffer(std::vector<Vertex> vertices)
{
    SCOPED_TIMER;
    createVertexBuffer(vertices);
}

VulkanVertexBuffer::~VulkanVertexBuffer()
{
    cleanup();
}

void VulkanVertexBuffer::createVertexBuffer(std::vector<Vertex> vertices){

    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = sizeof(Vertex) * 3;
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(VulkanLogicalDevice::GetLogicalDevice(), &bufferInfo, nullptr, &m_VertexBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(VulkanLogicalDevice::GetLogicalDevice(), m_VertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = VulkanLogicalDevice::FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(VulkanLogicalDevice::GetLogicalDevice(), &allocInfo, nullptr, &m_VertexBufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(VulkanLogicalDevice::GetLogicalDevice(), m_VertexBuffer, m_VertexBufferMemory, 0);

    void* data;
    vkMapMemory(VulkanLogicalDevice::GetLogicalDevice(), m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
    memcpy(data, vertices.data(), (size_t) bufferInfo.size);
    vkUnmapMemory(VulkanLogicalDevice::GetLogicalDevice(), m_VertexBufferMemory);

}

void VulkanVertexBuffer::cleanup()
{
    vkDestroyBuffer(VulkanLogicalDevice::GetLogicalDevice(), m_VertexBuffer, nullptr);
    vkFreeMemory(VulkanLogicalDevice::GetLogicalDevice(), m_VertexBufferMemory, nullptr);
}