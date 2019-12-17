#pragma once

/* C LIBRARIES */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ShellScalingAPI.h>

/* STANDARD LIBRARIES */
#include <algorithm>
#include <array>
#include <chrono>
#include <condition_variable>
#include <exception>
#include <functional>
#include <iomanip>
#include <limits>
#include <map>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <thread>
#include <vector>

/* WINDOWS LIBRARIES */
#if defined(_WIN32)
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#endif

/* GRAPHICS LIBRARIES */
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/intersect.hpp>

#include "vulkan/vulkan.h"

#include "lib/assimp/Importer.hpp"
#include "lib/assimp/scene.h"
#include "lib/assimp/postprocess.h"
#include "lib/assimp/cimport.h"
#include "lib/imgui/imgui.h"

#include "lib/gli/gli.hpp"

//Engine Files
#include "Enums.h"


/* APPLICATION HEADERS */
//#include "Renderer.h"
class Renderer {
private:
public:
};


// DEFINES
#if defined(_WIN32)
#define KEY_ESCAPE VK_ESCAPE 
#define KEY_F1 VK_F1
#define KEY_F2 VK_F2
#define KEY_F3 VK_F3
#define KEY_F4 VK_F4
#define KEY_F5 VK_F5
#define KEY_W 0x57
#define KEY_A 0x41
#define KEY_S 0x53
#define KEY_D 0x44
#define KEY_P 0x50
#define KEY_SPACE 0x20
#define KEY_KPADD 0x6B
#define KEY_KPSUB 0x6D
#define KEY_B 0x42
#define KEY_F 0x46
#define KEY_L 0x4C
#define KEY_N 0x4E
#define KEY_O 0x4F
#define KEY_T 0x54
#define KEY_R 0x52

#elif defined(VK_USE_PLATFORM_MACOS_MVK)
#define KEY_ESCAPE 0x33
#define KEY_F1 0x12
#define KEY_F2 0x13
#define KEY_F3 0x14
#define KEY_F4 0x15
#define KEY_W 0x0D
#define KEY_A 0x00
#define KEY_S 0x01
#define KEY_D 0x02
#define KEY_P 0x23
#define KEY_SPACE 0x31
#define KEY_KPADD 0x18
#define KEY_KPSUB 0x1B
#define KEY_B 0x0B
#define KEY_F 0x03
#define KEY_L 0x25
#define KEY_N 0x2D
#define KEY_O 0x1F
#define KEY_T 0x11
#define KEY_R 0x0F

#elif defined(__linux__)
#define KEY_ESCAPE 0x9
#define KEY_F1 0x43
#define KEY_F2 0x44
#define KEY_F3 0x45
#define KEY_F4 0x46
#define KEY_W 0x19
#define KEY_A 0x26
#define KEY_S 0x27
#define KEY_D 0x28
#define KEY_P 0x21
#define KEY_SPACE 0x41
#define KEY_KPADD 0x56
#define KEY_KPSUB 0x52
#define KEY_B 0x38
#define KEY_F 0x29
#define KEY_L 0x2E
#define KEY_N 0x39
#define KEY_O 0x20
#define KEY_T 0x1C
#endif

#define ASSET_PATH "./../data/"
#define ENABLE_VALIDATION false

// Custom define for better code readability
#define VK_FLAGS_NONE 0
// Default fence timeout in nanoseconds
#define DEFAULT_FENCE_TIMEOUT 100000000000

#define VK_NV_ray_tracing 1
typedef struct VkAccelerationStructureNV_T* VkAccelerationStructureNV;

#define VK_NV_RAY_TRACING_SPEC_VERSION    3
#define VK_NV_RAY_TRACING_EXTENSION_NAME  "VK_NV_ray_tracing"
#define VK_SHADER_UNUSED_NV               (~0U)

#define BILLIARD_RIGHT 20
#define BILLIARD_TOP 12
#define BILLIARD_LEFT 0
#define BILLIARD_BOTTOM 0


// Macro to get a procedure address based on a vulkan instance
#define GET_INSTANCE_PROC_ADDR(inst, entrypoint) {                      \
	fp##entrypoint = reinterpret_cast<PFN_vk##entrypoint>(vkGetInstanceProcAddr(inst, "vk"#entrypoint)); \
	if (fp##entrypoint == NULL)                                         \
	{																    \
		exit(1);                                                        \
	}                                                                   \
}


// Macro to get a procedure address based on a vulkan device
#define GET_DEVICE_PROC_ADDR(dev, entrypoint) {                         \
	fp##entrypoint = reinterpret_cast<PFN_vk##entrypoint>(vkGetDeviceProcAddr(dev, "vk"#entrypoint));   \
	if (fp##entrypoint == NULL)                                         \
	{																    \
		exit(1);                                                        \
	}                                                                   \
}


namespace initializers {
	inline VkMemoryAllocateInfo memoryAllocateInfo() {
		VkMemoryAllocateInfo memAllocInfo{};
		memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		return memAllocInfo;
	}

	inline VkMappedMemoryRange mappedMemoryRange() {
		VkMappedMemoryRange mappedMemoryRange{};
		mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		return mappedMemoryRange;
	}

	inline VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t bufferCount) {
		VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = commandPool;
		commandBufferAllocateInfo.level = level;
		commandBufferAllocateInfo.commandBufferCount = bufferCount;
		return commandBufferAllocateInfo;
	}

	inline VkCommandPoolCreateInfo commandPoolCreateInfo() {
		VkCommandPoolCreateInfo cmdPoolCreateInfo{};
		cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		return cmdPoolCreateInfo;
	}

	inline VkCommandBufferBeginInfo commandBufferBeginInfo() {
		VkCommandBufferBeginInfo cmdBufferBeginInfo{};
		cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		return cmdBufferBeginInfo;
	}

	inline VkCommandBufferInheritanceInfo commandBufferInheritanceInfo() {
		VkCommandBufferInheritanceInfo cmdBufferInheritanceInfo{};
		cmdBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		return cmdBufferInheritanceInfo;
	}

	inline VkRenderPassBeginInfo renderPassBeginInfo() {
		VkRenderPassBeginInfo renderPassBeginInfo{};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		return renderPassBeginInfo;
	}

	inline VkRenderPassCreateInfo renderPassCreateInfo() {
		VkRenderPassCreateInfo renderPassCreateInfo{};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		return renderPassCreateInfo;
	}

	/** @brief Initialize an image memory barrier with no image transfer ownership */
	inline VkImageMemoryBarrier imageMemoryBarrier() {
		VkImageMemoryBarrier imageMemoryBarrier{};
		imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		return imageMemoryBarrier;
	}

	/** @brief Initialize a buffer memory barrier with no image transfer ownership */
	inline VkBufferMemoryBarrier bufferMemoryBarrier() {
		VkBufferMemoryBarrier bufferMemoryBarrier{};
		bufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		bufferMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		bufferMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		return bufferMemoryBarrier;
	}

	inline VkMemoryBarrier memoryBarrier() {
		VkMemoryBarrier memoryBarrier{};
		memoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
		return memoryBarrier;
	}

	inline VkImageCreateInfo imageCreateInfo() {
		VkImageCreateInfo imageCreateInfo{};
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		return imageCreateInfo;
	}

	inline VkSamplerCreateInfo samplerCreateInfo() {
		VkSamplerCreateInfo samplerCreateInfo{};
		samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerCreateInfo.maxAnisotropy = 1.0f;
		return samplerCreateInfo;
	}

	inline VkImageViewCreateInfo imageViewCreateInfo() {
		VkImageViewCreateInfo imageViewCreateInfo{};
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		return imageViewCreateInfo;
	}

	inline VkFramebufferCreateInfo framebufferCreateInfo() {
		VkFramebufferCreateInfo framebufferCreateInfo{};
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		return framebufferCreateInfo;
	}

	inline VkSemaphoreCreateInfo semaphoreCreateInfo() {
		VkSemaphoreCreateInfo semaphoreCreateInfo{};
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		return semaphoreCreateInfo;
	}

	inline VkFenceCreateInfo fenceCreateInfo(VkFenceCreateFlags flags = 0) {
		VkFenceCreateInfo fenceCreateInfo{};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = flags;
		return fenceCreateInfo;
	}

	inline VkEventCreateInfo eventCreateInfo() {
		VkEventCreateInfo eventCreateInfo{};
		eventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
		return eventCreateInfo;
	}

	inline VkSubmitInfo submitInfo() {
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		return submitInfo;
	}

	inline VkViewport viewport(float width, float height, float minDepth, float maxDepth) {
		VkViewport viewport{};
		viewport.width = width;
		viewport.height = height;
		viewport.minDepth = minDepth;
		viewport.maxDepth = maxDepth;
		return viewport;
	}

	inline VkRect2D rect2D(int32_t width, int32_t height, int32_t offsetX, int32_t offsetY) {
		VkRect2D rect2D{};
		rect2D.extent.width = width;
		rect2D.extent.height = height;
		rect2D.offset.x = offsetX;
		rect2D.offset.y = offsetY;
		return rect2D;
	}

	inline VkBufferCreateInfo bufferCreateInfo() {
		VkBufferCreateInfo bufCreateInfo{};
		bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		return bufCreateInfo;
	}

	inline VkBufferCreateInfo bufferCreateInfo(VkBufferUsageFlags usage, VkDeviceSize size) {
		VkBufferCreateInfo bufCreateInfo{};
		bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufCreateInfo.usage = usage;
		bufCreateInfo.size = size;
		return bufCreateInfo;
	}

	inline VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(uint32_t poolSizeCount, VkDescriptorPoolSize* pPoolSizes, uint32_t maxSets) {
		VkDescriptorPoolCreateInfo descriptorPoolInfo{};
		descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorPoolInfo.poolSizeCount = poolSizeCount;
		descriptorPoolInfo.pPoolSizes = pPoolSizes;
		descriptorPoolInfo.maxSets = maxSets;
		return descriptorPoolInfo;
	}

	inline VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(const std::vector<VkDescriptorPoolSize>& poolSizes, uint32_t maxSets) {
		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = maxSets;
		return poolInfo;
	}

	inline VkDescriptorPoolSize descriptorPoolSize(VkDescriptorType type, uint32_t count) {
		VkDescriptorPoolSize poolSize{};
		poolSize.type = type;
		poolSize.descriptorCount = count;
		return poolSize;
	}

	inline VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(VkDescriptorType type, VkShaderStageFlags stageFlags, uint32_t binding, uint32_t descriptorCount = 1) {
		VkDescriptorSetLayoutBinding setLayoutBinding{};
		setLayoutBinding.descriptorType = type;
		setLayoutBinding.stageFlags = stageFlags;
		setLayoutBinding.binding = binding;
		setLayoutBinding.descriptorCount = descriptorCount;
		return setLayoutBinding;
	}

	inline VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(const VkDescriptorSetLayoutBinding* pBindings, uint32_t bindingCount) {
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
		descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutCreateInfo.pBindings = pBindings;
		descriptorSetLayoutCreateInfo.bindingCount = bindingCount;
		return descriptorSetLayoutCreateInfo;
	}

	inline VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(const std::vector<VkDescriptorSetLayoutBinding>& bindings) {
		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{};
		descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutCreateInfo.pBindings = bindings.data();
		descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		return descriptorSetLayoutCreateInfo;
	}

	inline VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(const VkDescriptorSetLayout* pSetLayouts, uint32_t setLayoutCount = 1) {
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
		pipelineLayoutCreateInfo.pSetLayouts = pSetLayouts;
		return pipelineLayoutCreateInfo;
	}

	inline VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(uint32_t setLayoutCount = 1) {
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
		return pipelineLayoutCreateInfo;
	}

	inline VkDescriptorSetAllocateInfo descriptorSetAllocateInfo(VkDescriptorPool descriptorPool, const VkDescriptorSetLayout* pSetLayouts, uint32_t descriptorSetCount) {
		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo{};
		descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		descriptorSetAllocateInfo.descriptorPool = descriptorPool;
		descriptorSetAllocateInfo.pSetLayouts = pSetLayouts;
		descriptorSetAllocateInfo.descriptorSetCount = descriptorSetCount;
		return descriptorSetAllocateInfo;
	}

	inline VkDescriptorImageInfo descriptorImageInfo(VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout) {
		VkDescriptorImageInfo descriptorImageInfo{};
		descriptorImageInfo.sampler = sampler;
		descriptorImageInfo.imageView = imageView;
		descriptorImageInfo.imageLayout = imageLayout;
		return descriptorImageInfo;
	}

	inline VkWriteDescriptorSet writeDescriptorSet(
		VkDescriptorSet dstSet,
		VkDescriptorType type,
		uint32_t binding,
		VkDescriptorBufferInfo* bufferInfo,
		uint32_t descriptorCount = 1)
	{
		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.dstSet = dstSet;
		writeDescriptorSet.descriptorType = type;
		writeDescriptorSet.dstBinding = binding;
		writeDescriptorSet.pBufferInfo = bufferInfo;
		writeDescriptorSet.descriptorCount = descriptorCount;
		return writeDescriptorSet;
	}

	inline VkWriteDescriptorSet writeDescriptorSet(
		VkDescriptorSet dstSet,
		VkDescriptorType type,
		uint32_t binding,
		VkDescriptorImageInfo* imageInfo,
		uint32_t descriptorCount = 1)
	{
		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.dstSet = dstSet;
		writeDescriptorSet.descriptorType = type;
		writeDescriptorSet.dstBinding = binding;
		writeDescriptorSet.pImageInfo = imageInfo;
		writeDescriptorSet.descriptorCount = descriptorCount;
		return writeDescriptorSet;
	}

	inline VkVertexInputBindingDescription vertexInputBindingDescription(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate) {
		VkVertexInputBindingDescription vInputBindDescription{};
		vInputBindDescription.binding = binding;
		vInputBindDescription.stride = stride;
		vInputBindDescription.inputRate = inputRate;
		return vInputBindDescription;
	}

	inline VkVertexInputAttributeDescription vertexInputAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset) {
		VkVertexInputAttributeDescription vInputAttribDescription{};
		vInputAttribDescription.location = location;
		vInputAttribDescription.binding = binding;
		vInputAttribDescription.format = format;
		vInputAttribDescription.offset = offset;
		return vInputAttribDescription;
	}

	inline VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo() {
		VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{};
		pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		return pipelineVertexInputStateCreateInfo;
	}

	inline VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo(
		VkPrimitiveTopology topology,
		VkPipelineInputAssemblyStateCreateFlags flags,
		VkBool32 primitiveRestartEnable)
	{
		VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{};
		pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		pipelineInputAssemblyStateCreateInfo.topology = topology;
		pipelineInputAssemblyStateCreateInfo.flags = flags;
		pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = primitiveRestartEnable;
		return pipelineInputAssemblyStateCreateInfo;
	}

	inline VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo(
		VkPolygonMode polygonMode,
		VkCullModeFlags cullMode,
		VkFrontFace frontFace,
		VkPipelineRasterizationStateCreateFlags flags = 0)
	{
		VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo{};
		pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		pipelineRasterizationStateCreateInfo.polygonMode = polygonMode;
		pipelineRasterizationStateCreateInfo.cullMode = cullMode;
		pipelineRasterizationStateCreateInfo.frontFace = frontFace;
		pipelineRasterizationStateCreateInfo.flags = flags;
		pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
		pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
		return pipelineRasterizationStateCreateInfo;
	}

	inline VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(VkColorComponentFlags colorWriteMask, VkBool32 blendEnable) {
		VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState{};
		pipelineColorBlendAttachmentState.colorWriteMask = colorWriteMask;
		pipelineColorBlendAttachmentState.blendEnable = blendEnable;
		return pipelineColorBlendAttachmentState;
	}

	inline VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo(
		uint32_t attachmentCount,
		const VkPipelineColorBlendAttachmentState* pAttachments)
	{
		VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo{};
		pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		pipelineColorBlendStateCreateInfo.attachmentCount = attachmentCount;
		pipelineColorBlendStateCreateInfo.pAttachments = pAttachments;
		return pipelineColorBlendStateCreateInfo;
	}

	inline VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo(
		VkBool32 depthTestEnable,
		VkBool32 depthWriteEnable,
		VkCompareOp depthCompareOp)
	{
		VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo{};
		pipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		pipelineDepthStencilStateCreateInfo.depthTestEnable = depthTestEnable;
		pipelineDepthStencilStateCreateInfo.depthWriteEnable = depthWriteEnable;
		pipelineDepthStencilStateCreateInfo.depthCompareOp = depthCompareOp;
		pipelineDepthStencilStateCreateInfo.front = pipelineDepthStencilStateCreateInfo.back;
		pipelineDepthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
		return pipelineDepthStencilStateCreateInfo;
	}

	inline VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo(
		uint32_t viewportCount,
		uint32_t scissorCount,
		VkPipelineViewportStateCreateFlags flags = 0)
	{
		VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo{};
		pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		pipelineViewportStateCreateInfo.viewportCount = viewportCount;
		pipelineViewportStateCreateInfo.scissorCount = scissorCount;
		pipelineViewportStateCreateInfo.flags = flags;
		return pipelineViewportStateCreateInfo;
	}

	inline VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo(
		VkSampleCountFlagBits rasterizationSamples,
		VkPipelineMultisampleStateCreateFlags flags = 0)
	{
		VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo{};
		pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		pipelineMultisampleStateCreateInfo.rasterizationSamples = rasterizationSamples;
		pipelineMultisampleStateCreateInfo.flags = flags;
		return pipelineMultisampleStateCreateInfo;
	}

	inline VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
		const VkDynamicState* pDynamicStates,
		uint32_t dynamicStateCount,
		VkPipelineDynamicStateCreateFlags flags = 0)
	{
		VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
		pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates;
		pipelineDynamicStateCreateInfo.dynamicStateCount = dynamicStateCount;
		pipelineDynamicStateCreateInfo.flags = flags;
		return pipelineDynamicStateCreateInfo;
	}

	inline VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo(
		const std::vector<VkDynamicState>& pDynamicStates,
		VkPipelineDynamicStateCreateFlags flags = 0)
	{
		VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{};
		pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates.data();
		pipelineDynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(pDynamicStates.size());
		pipelineDynamicStateCreateInfo.flags = flags;
		return pipelineDynamicStateCreateInfo;
	}

	inline VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo(uint32_t patchControlPoints) {
		VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo{};
		pipelineTessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		pipelineTessellationStateCreateInfo.patchControlPoints = patchControlPoints;
		return pipelineTessellationStateCreateInfo;
	}

	inline VkGraphicsPipelineCreateInfo pipelineCreateInfo(
		VkPipelineLayout layout,
		VkRenderPass renderPass,
		VkPipelineCreateFlags flags = 0)
	{
		VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.layout = layout;
		pipelineCreateInfo.renderPass = renderPass;
		pipelineCreateInfo.flags = flags;
		pipelineCreateInfo.basePipelineIndex = -1;
		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		return pipelineCreateInfo;
	}

	inline VkGraphicsPipelineCreateInfo pipelineCreateInfo() {
		VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.basePipelineIndex = -1;
		pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		return pipelineCreateInfo;
	}

	inline VkComputePipelineCreateInfo computePipelineCreateInfo(VkPipelineLayout layout, VkPipelineCreateFlags flags = 0) {
		VkComputePipelineCreateInfo computePipelineCreateInfo{};
		computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		computePipelineCreateInfo.layout = layout;
		computePipelineCreateInfo.flags = flags;
		return computePipelineCreateInfo;
	}

	inline VkPushConstantRange pushConstantRange(
		VkShaderStageFlags stageFlags,
		uint32_t size,
		uint32_t offset)
	{
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = stageFlags;
		pushConstantRange.offset = offset;
		pushConstantRange.size = size;
		return pushConstantRange;
	}

	inline VkBindSparseInfo bindSparseInfo() {
		VkBindSparseInfo bindSparseInfo{};
		bindSparseInfo.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
		return bindSparseInfo;
	}

	/** @brief Initialize a map entry for a shader specialization constant */
	inline VkSpecializationMapEntry specializationMapEntry(uint32_t constantID, uint32_t offset, size_t size) {
		VkSpecializationMapEntry specializationMapEntry{};
		specializationMapEntry.constantID = constantID;
		specializationMapEntry.offset = offset;
		specializationMapEntry.size = size;
		return specializationMapEntry;
	}

	/** @brief Initialize a specialization constant info structure to pass to a shader stage */
	inline VkSpecializationInfo specializationInfo(uint32_t mapEntryCount, const VkSpecializationMapEntry* mapEntries, size_t dataSize, const void* data) {
		VkSpecializationInfo specializationInfo{};
		specializationInfo.mapEntryCount = mapEntryCount;
		specializationInfo.pMapEntries = mapEntries;
		specializationInfo.dataSize = dataSize;
		specializationInfo.pData = data;
		return specializationInfo;
	}
}

struct KeyframeData {
	float time;					// time of the keyframe
	float x, y, z;				// position in the keyframe
	float xa, ya, za, theta;	// rotational vector in the keyframe, along with the angle around that vector
	glm::mat4 trans;
	glm::quat rot;
	glm::mat4 matrix;			// the resulting matrix generated from the above data
};

class Camera {
private:
	float fov;
	float znear, zfar;

	void updateViewMatrix() {
		glm::mat4 rotM = glm::mat4(1.0f);
		glm::mat4 transM;

		rotM = glm::rotate(rotM, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rotM = glm::rotate(rotM, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotM = glm::rotate(rotM, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		transM = glm::translate(glm::mat4(1.0f), position);

		if (type == CameraType::firstperson)
		{
			matrices.view = rotM * transM;
		}
		else
		{
			matrices.view = transM * rotM;
		}

		updated = true;
	};
public:
	enum CameraType { lookat, firstperson };
	CameraType type = CameraType::firstperson;// CameraType::lookat;

	glm::vec3 rotation = glm::vec3();
	glm::vec3 position = glm::vec3();

	float rotationSpeed = 0.8f; // 1.0f = default
	float movementSpeed = 0.1f; // 1.0f = default

	bool updated = false;

	struct {
		glm::mat4 perspective;
		glm::mat4 view;
	} matrices;

	struct {
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
	} keys;

	bool moving() {
		return keys.left || keys.right || keys.up || keys.down;
	}

	float getNearClip() {
		return znear;
	}

	float getFarClip() {
		return zfar;
	}

	void setPerspective(float fov, float aspect, float znear, float zfar) {
		this->fov = fov;
		this->znear = znear;
		this->zfar = zfar;
		matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
	};

	void updateAspectRatio(float aspect) {
		matrices.perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
		updateViewMatrix();
	}

	void setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
		updateViewMatrix();
	};

	void rotate(glm::vec3 delta) {
		this->rotation += delta;
		updateViewMatrix();
	}

	void setTranslation(glm::vec3 translation) {
		this->position = translation;
		updateViewMatrix();
	};

	void translate(glm::vec3 delta) {
		this->position += delta;
		updateViewMatrix();
	}

	void setDirection(glm::vec3 loc, glm::vec3 target, glm::vec3 up) {
		matrices.view = glm::lookAt(loc, target, up);
		updated = true;
		// We skip updateViewMatrix() here because glm::lookAt() creates the entire matricies.view matrix for us
	}

	void update(float deltaTime) {
		updated = false;
		if (type == CameraType::firstperson) {
			if (moving()) {
				glm::vec3 camFront;
				camFront.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
				camFront.y = sin(glm::radians(rotation.x));
				camFront.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
				camFront = glm::normalize(camFront);

				float moveSpeed = deltaTime * movementSpeed;

				if (keys.up)	position += camFront * moveSpeed;
				if (keys.down)	position -= camFront * moveSpeed;
				if (keys.left)	position -= glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;
				if (keys.right)	position += glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * moveSpeed;

				updateViewMatrix();
			}
		}
	};

	// Update camera passing separate axis data (gamepad)
	// Returns true if view or position has been changed
	bool updatePad(glm::vec2 axisLeft, glm::vec2 axisRight, float deltaTime) {
		bool retVal = false;

		if (type == CameraType::firstperson) {
			// Use the common console thumbstick layout		
			// Left = view, right = move

			const float deadZone = 0.0015f;
			const float range = 1.0f - deadZone;

			glm::vec3 camFront;
			camFront.x = -cos(glm::radians(rotation.x)) * sin(glm::radians(rotation.y));
			camFront.y = sin(glm::radians(rotation.x));
			camFront.z = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
			camFront = glm::normalize(camFront);

			float moveSpeed = deltaTime * movementSpeed;// *2.0f;
			float rotSpeed = deltaTime * rotationSpeed * 50.0f;

			// Move
			if (fabsf(axisLeft.y) > deadZone) {
				float pos = (fabsf(axisLeft.y) - deadZone) / range;
				position -= camFront * pos * ((axisLeft.y < 0.0f) ? -1.0f : 1.0f) * moveSpeed;
				retVal = true;
			}

			if (fabsf(axisLeft.x) > deadZone) {
				float pos = (fabsf(axisLeft.x) - deadZone) / range;
				position += glm::normalize(glm::cross(camFront, glm::vec3(0.0f, 1.0f, 0.0f))) * pos * ((axisLeft.x < 0.0f) ? -1.0f : 1.0f) * moveSpeed;
				retVal = true;
			}

			// Rotate
			if (fabsf(axisRight.x) > deadZone) {
				float pos = (fabsf(axisRight.x) - deadZone) / range;
				rotation.y += pos * ((axisRight.x < 0.0f) ? -1.0f : 1.0f) * rotSpeed;
				retVal = true;
			}

			if (fabsf(axisRight.y) > deadZone) {
				float pos = (fabsf(axisRight.y) - deadZone) / range;
				rotation.x -= pos * ((axisRight.y < 0.0f) ? -1.0f : 1.0f) * rotSpeed;
				retVal = true;
			}
		} else {
			// todo: move code from example base class for look-at
		}

		if (retVal) {
			updateViewMatrix();
		}

		return retVal;
	}
};

namespace debug {
	// Default validation layers
	extern int validationLayerCount;
	extern const char* validationLayerNames[];

	// On desktop the LunarG loaders exposes a meta layer that contains all layers
	int32_t validationLayerCount = 1;
	const char* validationLayerNames[] = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback = VK_NULL_HANDLE;
	PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback = VK_NULL_HANDLE;
	PFN_vkDebugReportMessageEXT dbgBreakCallback = VK_NULL_HANDLE;

	VkDebugReportCallbackEXT msgCallback;

	VKAPI_ATTR VkBool32 VKAPI_CALL messageCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* pLayerPrefix,
		const char* pMsg,
		void* pUserData)
	{
		// Select prefix depending on flags passed to the callback
		// Note that multiple flags may be set for a single validation message
		std::string prefix("");

		// Error that may result in undefined behaviour
		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
			prefix += "ERROR:";
		};
		// Warnings may hint at unexpected / non-spec API usage
		if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
			prefix += "WARNING:";
		};
		// May indicate sub-optimal usage of the API
		if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
			prefix += "PERFORMANCE:";
		};
		// Informal messages that may become handy during debugging
		if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
			prefix += "INFO:";
		}
		// Diagnostic info from the Vulkan loader and layers
		// Usually not helpful in terms of API usage, but may help to debug layer and loader problems 
		if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
			prefix += "DEBUG:";
		}

		// Display message to default output (console/logcat)
		std::stringstream debugMessage;
		debugMessage << prefix << " [" << pLayerPrefix << "] Code " << msgCode << " : " << pMsg;

		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
			std::cerr << debugMessage.str() << "\n";
		}
		else {
			std::cout << debugMessage.str() << "\n";
		}

		fflush(stdout);

		// The return value of this callback controls wether the Vulkan call that caused
		// the validation message will be aborted or not
		// We return VK_FALSE as we DON'T want Vulkan calls that cause a validation message 
		// (and return a VkResult) to abort
		// If you instead want to have calls abort, pass in VK_TRUE and the function will 
		// return VK_ERROR_VALIDATION_FAILED_EXT 
		return VK_FALSE;
	}

	void setupDebugging(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportCallbackEXT callBack) {
		CreateDebugReportCallback = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
		DestroyDebugReportCallback = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
		dbgBreakCallback = reinterpret_cast<PFN_vkDebugReportMessageEXT>(vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT"));

		VkDebugReportCallbackCreateInfoEXT dbgCreateInfo = {};
		dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		dbgCreateInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)messageCallback;
		dbgCreateInfo.flags = flags;

		VkResult err = CreateDebugReportCallback(
			instance,
			&dbgCreateInfo,
			nullptr,
			(callBack != VK_NULL_HANDLE) ? &callBack : &msgCallback);
		assert(!err);
	}

	void freeDebugCallback(VkInstance instance) {
		if (msgCallback != VK_NULL_HANDLE) {
			DestroyDebugReportCallback(instance, msgCallback, nullptr);
		}
	}
}

// Setup and functions for the VK_EXT_debug_marker_extension
// Extension spec can be found at https://github.com/KhronosGroup/Vulkan-Docs/blob/1.0-VK_EXT_debug_marker/doc/specs/vulkan/appendices/VK_EXT_debug_marker.txt
// Note that the extension will only be present if run from an offline debugging application
// The actual check for extension presence and enabling it on the device is done in the example base class
// See VulkanRenderer::createInstance and VulkanRenderer::createDevice (base/vulkanexamplebase.cpp)
namespace debugmarker {
	// Set to true if function pointer for the debug marker are available
	extern bool active = false;

	PFN_vkDebugMarkerSetObjectTagEXT pfnDebugMarkerSetObjectTag = VK_NULL_HANDLE;
	PFN_vkDebugMarkerSetObjectNameEXT pfnDebugMarkerSetObjectName = VK_NULL_HANDLE;
	PFN_vkCmdDebugMarkerBeginEXT pfnCmdDebugMarkerBegin = VK_NULL_HANDLE;
	PFN_vkCmdDebugMarkerEndEXT pfnCmdDebugMarkerEnd = VK_NULL_HANDLE;
	PFN_vkCmdDebugMarkerInsertEXT pfnCmdDebugMarkerInsert = VK_NULL_HANDLE;

	void setup(VkDevice device) {
		pfnDebugMarkerSetObjectTag = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectTagEXT"));
		pfnDebugMarkerSetObjectName = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectNameEXT"));
		pfnCmdDebugMarkerBegin = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(vkGetDeviceProcAddr(device, "vkCmdDebugMarkerBeginEXT"));
		pfnCmdDebugMarkerEnd = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(vkGetDeviceProcAddr(device, "vkCmdDebugMarkerEndEXT"));
		pfnCmdDebugMarkerInsert = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(vkGetDeviceProcAddr(device, "vkCmdDebugMarkerInsertEXT"));

		// Set flag if at least one function pointer is present
		active = (pfnDebugMarkerSetObjectName != VK_NULL_HANDLE);
	}

	void setObjectName(VkDevice device, uint64_t object, VkDebugReportObjectTypeEXT objectType, const char* name) {
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (pfnDebugMarkerSetObjectName) {
			VkDebugMarkerObjectNameInfoEXT nameInfo = {};
			nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
			nameInfo.objectType = objectType;
			nameInfo.object = object;
			nameInfo.pObjectName = name;
			pfnDebugMarkerSetObjectName(device, &nameInfo);
		}
	}

	void setObjectTag(VkDevice device, uint64_t object, VkDebugReportObjectTypeEXT objectType, uint64_t name, size_t tagSize, const void* tag) {
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (pfnDebugMarkerSetObjectTag) {
			VkDebugMarkerObjectTagInfoEXT tagInfo = {};
			tagInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
			tagInfo.objectType = objectType;
			tagInfo.object = object;
			tagInfo.tagName = name;
			tagInfo.tagSize = tagSize;
			tagInfo.pTag = tag;
			pfnDebugMarkerSetObjectTag(device, &tagInfo);
		}
	}

	void beginRegion(VkCommandBuffer cmdbuffer, const char* pMarkerName, glm::vec4 color) {
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (pfnCmdDebugMarkerBegin) {
			VkDebugMarkerMarkerInfoEXT markerInfo = {};
			markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
			memcpy(markerInfo.color, &color[0], sizeof(float) * 4);
			markerInfo.pMarkerName = pMarkerName;
			pfnCmdDebugMarkerBegin(cmdbuffer, &markerInfo);
		}
	}

	void insert(VkCommandBuffer cmdbuffer, std::string markerName, glm::vec4 color) {
		// Check for valid function pointer (may not be present if not running in a debugging application)
		if (pfnCmdDebugMarkerInsert) {
			VkDebugMarkerMarkerInfoEXT markerInfo = {};
			markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
			memcpy(markerInfo.color, &color[0], sizeof(float) * 4);
			markerInfo.pMarkerName = markerName.c_str();
			pfnCmdDebugMarkerInsert(cmdbuffer, &markerInfo);
		}
	}

	void endRegion(VkCommandBuffer cmdBuffer) {
		// Check for valid function (may not be present if not runnin in a debugging application)
		if (pfnCmdDebugMarkerEnd) {
			pfnCmdDebugMarkerEnd(cmdBuffer);
		}
	}

	void setCommandBufferName(VkDevice device, VkCommandBuffer cmdBuffer, const char* name) {
		setObjectName(device, (uint64_t)cmdBuffer, VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT, name);
	}

	void setQueueName(VkDevice device, VkQueue queue, const char* name) {
		setObjectName(device, (uint64_t)queue, VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT, name);
	}

	void setImageName(VkDevice device, VkImage image, const char* name) {
		setObjectName(device, (uint64_t)image, VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT, name);
	}

	void setSamplerName(VkDevice device, VkSampler sampler, const char* name) {
		setObjectName(device, (uint64_t)sampler, VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT, name);
	}

	void setBufferName(VkDevice device, VkBuffer buffer, const char* name) {
		setObjectName(device, (uint64_t)buffer, VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT, name);
	}

	void setDeviceMemoryName(VkDevice device, VkDeviceMemory memory, const char* name) {
		setObjectName(device, (uint64_t)memory, VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, name);
	}

	void setShaderModuleName(VkDevice device, VkShaderModule shaderModule, const char* name) {
		setObjectName(device, (uint64_t)shaderModule, VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT, name);
	}

	void setPipelineName(VkDevice device, VkPipeline pipeline, const char* name) {
		setObjectName(device, (uint64_t)pipeline, VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT, name);
	}

	void setPipelineLayoutName(VkDevice device, VkPipelineLayout pipelineLayout, const char* name) {
		setObjectName(device, (uint64_t)pipelineLayout, VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT, name);
	}

	void setRenderPassName(VkDevice device, VkRenderPass renderPass, const char* name) {
		setObjectName(device, (uint64_t)renderPass, VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT, name);
	}

	void setFramebufferName(VkDevice device, VkFramebuffer framebuffer, const char* name) {
		setObjectName(device, (uint64_t)framebuffer, VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT, name);
	}

	void setDescriptorSetLayoutName(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const char* name) {
		setObjectName(device, (uint64_t)descriptorSetLayout, VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT, name);
	}

	void setDescriptorSetName(VkDevice device, VkDescriptorSet descriptorSet, const char* name) {
		setObjectName(device, (uint64_t)descriptorSet, VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT, name);
	}

	void setSemaphoreName(VkDevice device, VkSemaphore semaphore, const char* name) {
		setObjectName(device, (uint64_t)semaphore, VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT, name);
	}

	void setFenceName(VkDevice device, VkFence fence, const char* name) {
		setObjectName(device, (uint64_t)fence, VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT, name);
	}

	void setEventName(VkDevice device, VkEvent _event, const char* name) {
		setObjectName(device, (uint64_t)_event, VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT, name);
	}
};

namespace tools {
	template <class Container>
	void str_split(const std::string& str, Container& cont) {
		std::istringstream iss(str);
		std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(cont));
	}

	/*
	Sample Infile Contents
	0.0  0.0 0.0 0.0 1.0 1.0 -1.0 0.0
	1.0  4.0 0.0 0.0 1.0 1.0 -1.0 30.0
	2.0  8.0 0.0 0.0 1.0 1.0 -1.0 90.0
	3.0  12.0 12.0 12.0 1.0 1.0 -1.0 180.0
	4.0  12.0 18.0 18.0 1.0 1.0 -1.0 270.0
	5.0  18.0 18.0 18.0 0.0 1.0 0.0 90.0
	6.0  18.0 18.0 18.0 0.0 0.0 1.0 90.0
	7.0  25.0 12.0 12.0 1.0 0.0 0.0 0.0
	8.0  25.0 0.0 18.0 1.0 0.0 0.0 0.0
	9.0 25.0 1.0 18.0 1.0 0.0 0.0 0.0
	*/
	std::vector<KeyframeData> LoadInfile(std::string file_path, std::vector<KeyframeData> &keyframes) {
		std::ifstream file(file_path);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				// split the string up
				std::string s = line;
				
				std::vector<std::string> terms;
				str_split(s, terms);

				KeyframeData line_data;
				line_data.time	= std::stof(terms.at(0)); //time
				line_data.x		= std::stof(terms.at(1)); //x
				line_data.y		= std::stof(terms.at(2)); //y
				line_data.z		= std::stof(terms.at(3)); //z
				line_data.xa	= std::stof(terms.at(4)); //xa
				line_data.ya	= std::stof(terms.at(5)); //ya
				line_data.za	= std::stof(terms.at(6)); //za
				line_data.theta	= std::stof(terms.at(7)); //theta

				//lets build the matrix ahead of time then...
				line_data.trans = glm::translate(glm::mat4(1), glm::vec3(line_data.x, line_data.y, line_data.z));
				line_data.rot = glm::angleAxis(line_data.theta, glm::normalize(glm::vec3(line_data.xa, line_data.ya, line_data.za)));
				//line_data.rot = glm::rotate(glm::mat4(1), line_data.theta, glm::normalize(glm::vec3(line_data.xa, line_data.ya, line_data.za)) );
				//glm::rotate( glm::quat(), line_data.theta, glm::normalize(glm::vec3(line_data.xa, line_data.ya, line_data.za)) );
				line_data.matrix = glm::mat4(1.0);//line_data.trans*line_data.rot;

				keyframes.push_back(line_data);
			}
		}

		return keyframes;
	}

	int GetFirstKeyframeIndex(std::vector<KeyframeData>& keyframes, float t) {
		for (int i = 0; i < keyframes.size()-1; i++) {
			if (keyframes.at(i).time < t && t < keyframes.at(i+1).time) {
				return i;
			}
		}
		return keyframes.size()-1;
	}

	/** @brief Disable message boxes on fatal errors */
	extern bool errorModeSilent;

	/** @brief Returns the device type as a string */
	std::string physicalDeviceTypeString(VkPhysicalDeviceType type);

	// Selected a suitable supported depth format starting with 32 bit down to 16 bit
	// Returns false if none of the depth formats in the list is supported by the device
	VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat);

	// Put an image memory barrier for setting an image layout on the sub resource into the given command buffer
	void setImageLayout(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkImageSubresourceRange subresourceRange,
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
	// Uses a fixed sub resource layout with first mip level and layer
	void setImageLayout(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkImageAspectFlags aspectMask,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

	/** @brief Inser an image memory barrier into the command buffer */
	void insertImageMemoryBarrier(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkAccessFlags srcAccessMask,
		VkAccessFlags dstAccessMask,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkPipelineStageFlags srcStageMask,
		VkPipelineStageFlags dstStageMask,
		VkImageSubresourceRange subresourceRange);

	// Display error message and exit on fatal error
	void exitFatal(std::string message, int32_t exitCode);
	void exitFatal(std::string message, VkResult resultCode);

	// Load a SPIR-V shader (binary) 
	VkShaderModule loadShader(const char* fileName, VkDevice device);

	bool errorModeSilent = false;

	std::string errorString(VkResult errorCode) {
		switch (errorCode) {
		case VK_NOT_READY:
			return "NOT_READY";
		case VK_TIMEOUT:
			return "TIMEOUT";
		case VK_EVENT_SET:
			return "EVENT_SET";
		case VK_EVENT_RESET:
			return "EVENT_RESET";
		case VK_INCOMPLETE:
			return "INCOMPLETE";
		case VK_SUBOPTIMAL_KHR:
			return "SUBOPTIMAL_KHR";
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			return "ERROR_OUT_OF_HOST_MEMORY";
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			return "ERROR_OUT_OF_DEVICE_MEMORY";
		case VK_ERROR_INITIALIZATION_FAILED:
			return "ERROR_INITIALIZATION_FAILED";
		case VK_ERROR_DEVICE_LOST:
			return "ERROR_DEVICE_LOST";
		case VK_ERROR_MEMORY_MAP_FAILED:
			return "ERROR_MEMORY_MAP_FAILED";
		case VK_ERROR_LAYER_NOT_PRESENT:
			return "ERROR_LAYER_NOT_PRESENT";
		case VK_ERROR_EXTENSION_NOT_PRESENT:
			return "ERROR_EXTENSION_NOT_PRESENT";
		case VK_ERROR_FEATURE_NOT_PRESENT:
			return "ERROR_FEATURE_NOT_PRESENT";
		case VK_ERROR_INCOMPATIBLE_DRIVER:
			return "ERROR_INCOMPATIBLE_DRIVER";
		case VK_ERROR_TOO_MANY_OBJECTS:
			return "ERROR_TOO_MANY_OBJECTS";
		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			return "ERROR_FORMAT_NOT_SUPPORTED";
		case VK_ERROR_SURFACE_LOST_KHR:
			return "ERROR_SURFACE_LOST_KHR";
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			return "ERROR_NATIVE_WINDOW_IN_USE_KHR";
		case VK_ERROR_OUT_OF_DATE_KHR:
			return "ERROR_OUT_OF_DATE_KHR";
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			return "ERROR_INCOMPATIBLE_DISPLAY_KHR";
		case VK_ERROR_VALIDATION_FAILED_EXT:
			return "ERROR_VALIDATION_FAILED_EXT";
		case VK_ERROR_INVALID_SHADER_NV:
			return "ERROR_INVALID_SHADER_NV";
		default:
			return "UNKNOWN_ERROR";
		}
	}

	inline void VK_VERIFY_SUCCESS(VkResult res) {
		if (res != VK_SUCCESS) {
			std::cout << "Fatal : VkResult is \"" << tools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl;
			assert(res == VK_SUCCESS);
		}
	}

	std::string physicalDeviceTypeString(VkPhysicalDeviceType type) {
		switch (type) {
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:
			return "OTHER";
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			return "INTEGRATED_GPU";
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			return "DISCRETE_GPU";
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			return "VIRTUAL_GPU";
		default:
			return "UNKNOWN_DEVICE_TYPE";
		}
	}

	VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat) {
		// Since all depth formats may be optional, we need to find a suitable depth format to use
		// Start with the highest precision packed format
		std::vector<VkFormat> depthFormats = {
			VK_FORMAT_D32_SFLOAT_S8_UINT,
			VK_FORMAT_D32_SFLOAT,
			VK_FORMAT_D24_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM
		};

		for (auto& format : depthFormats) {
			VkFormatProperties formatProps;
			vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);
			// Format must support depth stencil attachment for optimal tiling
			if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
				*depthFormat = format;
				return true;
			}
		}

		return false;
	}

	// Create an image memory barrier for changing the layout of
	// an image and put it into an active command buffer
	// See chapter 11.4 "Image Layout" for details

	void setImageLayout(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkImageSubresourceRange subresourceRange,
		VkPipelineStageFlags srcStageMask,
		VkPipelineStageFlags dstStageMask)
	{
		// Create an image barrier object
		VkImageMemoryBarrier imageMemoryBarrier = initializers::imageMemoryBarrier();
		imageMemoryBarrier.oldLayout = oldImageLayout;
		imageMemoryBarrier.newLayout = newImageLayout;
		imageMemoryBarrier.image = image;
		imageMemoryBarrier.subresourceRange = subresourceRange;

		// Source layouts (old)
		// Source access mask controls actions that have to be finished on the old layout
		// before it will be transitioned to the new layout
		switch (oldImageLayout) {
		case VK_IMAGE_LAYOUT_UNDEFINED:
			// Image layout is undefined (or does not matter)
			// Only valid as initial layout
			// No flags required, listed only for completeness
			imageMemoryBarrier.srcAccessMask = 0;
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			// Image is preinitialized
			// Only valid as initial layout for linear images, preserves memory contents
			// Make sure host writes have been finished
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			// Image is a color attachment
			// Make sure any writes to the color buffer have been finished
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			// Image is a depth/stencil attachment
			// Make sure any writes to the depth/stencil buffer have been finished
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			// Image is a transfer source 
			// Make sure any reads from the image have been finished
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			// Image is a transfer destination
			// Make sure any writes to the image have been finished
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			// Image is read by a shader
			// Make sure any shader reads from the image have been finished
			imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
			break;
		default:
			// Other source layouts aren't handled (yet)
			break;
		}

		// Target layouts (new)
		// Destination access mask controls the dependency for the new image layout
		switch (newImageLayout) {
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			// Image will be used as a transfer destination
			// Make sure any writes to the image have been finished
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			// Image will be used as a transfer source
			// Make sure any reads from the image have been finished
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			// Image will be used as a color attachment
			// Make sure any writes to the color buffer have been finished
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			// Image layout will be used as a depth/stencil attachment
			// Make sure any writes to depth/stencil buffer have been finished
			imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			// Image will be read in a shader (sampler, input attachment)
			// Make sure any writes to the image have been finished
			if (imageMemoryBarrier.srcAccessMask == 0) {
				imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
			}
			imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			break;
		default:
			// Other source layouts aren't handled (yet)
			break;
		}

		// Put barrier inside setup command buffer
		vkCmdPipelineBarrier(
			cmdbuffer,
			srcStageMask,
			dstStageMask,
			0,
			0, nullptr,
			0, nullptr,
			1, &imageMemoryBarrier);
	}

	// Fixed sub resource on first mip level and layer
	void setImageLayout(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkImageAspectFlags aspectMask,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkPipelineStageFlags srcStageMask,
		VkPipelineStageFlags dstStageMask)
	{
		VkImageSubresourceRange subresourceRange = {};
		subresourceRange.aspectMask = aspectMask;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = 1;
		subresourceRange.layerCount = 1;
		setImageLayout(cmdbuffer, image, oldImageLayout, newImageLayout, subresourceRange, srcStageMask, dstStageMask);
	}

	void insertImageMemoryBarrier(
		VkCommandBuffer cmdbuffer,
		VkImage image,
		VkAccessFlags srcAccessMask,
		VkAccessFlags dstAccessMask,
		VkImageLayout oldImageLayout,
		VkImageLayout newImageLayout,
		VkPipelineStageFlags srcStageMask,
		VkPipelineStageFlags dstStageMask,
		VkImageSubresourceRange subresourceRange)
	{
		VkImageMemoryBarrier imageMemoryBarrier = initializers::imageMemoryBarrier();
		imageMemoryBarrier.srcAccessMask = srcAccessMask;
		imageMemoryBarrier.dstAccessMask = dstAccessMask;
		imageMemoryBarrier.oldLayout = oldImageLayout;
		imageMemoryBarrier.newLayout = newImageLayout;
		imageMemoryBarrier.image = image;
		imageMemoryBarrier.subresourceRange = subresourceRange;

		vkCmdPipelineBarrier(
			cmdbuffer,
			srcStageMask,
			dstStageMask,
			0,
			0, nullptr,
			0, nullptr,
			1, &imageMemoryBarrier);
	}

	void exitFatal(std::string message, int32_t exitCode) {
#if defined(_WIN32)
		if (!errorModeSilent) {
			MessageBox(NULL, message.c_str(), NULL, MB_OK | MB_ICONERROR);
		}
#endif
		std::cerr << message << "\n";
		exit(exitCode);
	}

	void exitFatal(std::string message, VkResult resultCode) {
		exitFatal(message, (int32_t)resultCode);
	}

	std::string readTextFile(const char* fileName) {
		std::string fileContent;
		std::ifstream fileStream(fileName, std::ios::in);
		if (!fileStream.is_open()) {
			printf("File %s not found\n", fileName);
			return "";
		}
		std::string line = "";
		while (!fileStream.eof()) {
			getline(fileStream, line);
			fileContent.append(line + "\n");
		}
		fileStream.close();
		return fileContent;
	}

	VkShaderModule loadShader(const char* fileName, VkDevice device) {
		std::ifstream is(fileName, std::ios::binary | std::ios::in | std::ios::ate);

		if (is.is_open()) {
			size_t size = is.tellg();
			is.seekg(0, std::ios::beg);
			char* shaderCode = new char[size];
			is.read(shaderCode, size);
			is.close();

			assert(size > 0);

			VkShaderModule shaderModule;
			VkShaderModuleCreateInfo moduleCreateInfo{};
			moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			moduleCreateInfo.codeSize = size;
			moduleCreateInfo.pCode = (uint32_t*)shaderCode;

			VK_VERIFY_SUCCESS(vkCreateShaderModule(device, &moduleCreateInfo, NULL, &shaderModule));

			delete[] shaderCode;

			return shaderModule;
		}
		else {
			std::cerr << "Error: Could not open shader file \"" << fileName << "\"" << std::endl;
			return VK_NULL_HANDLE;
		}
	}

	bool fileExists(const std::string& filename) {
		std::ifstream f(filename.c_str());
		return !f.fail();
	}
}


/**
* @brief Encapsulates access to a Vulkan buffer backed up by device memory
* @note To be filled by an external source like the VulkanDevice
*/
struct Buffer {
	VkDevice device;
	VkBuffer buffer = VK_NULL_HANDLE;
	VkDeviceMemory memory = VK_NULL_HANDLE;
	VkDescriptorBufferInfo descriptor;
	VkDeviceSize size = 0;
	VkDeviceSize alignment = 0;
	void* mapped = nullptr;

	/** @brief Usage flags to be filled by external source at buffer creation (to query at some later point) */
	VkBufferUsageFlags usageFlags;
	/** @brief Memory propertys flags to be filled by external source at buffer creation (to query at some later point) */
	VkMemoryPropertyFlags memoryPropertyFlags;

	/**
	* Map a memory range of this buffer. If successful, mapped points to the specified buffer range.
	*
	* @param size (Optional) Size of the memory range to map. Pass VK_WHOLE_SIZE to map the complete buffer range.
	* @param offset (Optional) Byte offset from beginning
	*
	* @return VkResult of the buffer mapping call
	*/
	VkResult map(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) {
		return vkMapMemory(device, memory, offset, size, 0, &mapped);
	}

	/**
	* Unmap a mapped memory range
	*
	* @note Does not return a result as vkUnmapMemory can't fail
	*/
	void unmap() {
		if (mapped) {
			vkUnmapMemory(device, memory);
			mapped = nullptr;
		}
	}

	/**
	* Attach the allocated memory block to the buffer
	*
	* @param offset (Optional) Byte offset (from the beginning) for the memory region to bind
	*
	* @return VkResult of the bindBufferMemory call
	*/
	VkResult bind(VkDeviceSize offset = 0) {
		return vkBindBufferMemory(device, buffer, memory, offset);
	}

	/**
	* Setup the default descriptor for this buffer
	*
	* @param size (Optional) Size of the memory range of the descriptor
	* @param offset (Optional) Byte offset from beginning
	*
	*/
	void setupDescriptor(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) {
		descriptor.offset = offset;
		descriptor.buffer = buffer;
		descriptor.range = size;
	}

	/**
	* Copies the specified data to the mapped buffer
	*
	* @param data Pointer to the data to copy
	* @param size Size of the data to copy in machine units
	*
	*/
	void copyTo(void* data, VkDeviceSize size) {
		assert(mapped);
		memcpy(mapped, data, size);
	}

	/**
	* Flush a memory range of the buffer to make it visible to the device
	*
	* @note Only required for non-coherent memory
	*
	* @param size (Optional) Size of the memory range to flush. Pass VK_WHOLE_SIZE to flush the complete buffer range.
	* @param offset (Optional) Byte offset from beginning
	*
	* @return VkResult of the flush call
	*/
	VkResult flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) {
		VkMappedMemoryRange mappedRange = {};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkFlushMappedMemoryRanges(device, 1, &mappedRange);
	}

	/**
	* Invalidate a memory range of the buffer to make it visible to the host
	*
	* @note Only required for non-coherent memory
	*
	* @param size (Optional) Size of the memory range to invalidate. Pass VK_WHOLE_SIZE to invalidate the complete buffer range.
	* @param offset (Optional) Byte offset from beginning
	*
	* @return VkResult of the invalidate call
	*/
	VkResult invalidate(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0) {
		VkMappedMemoryRange mappedRange = {};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = memory;
		mappedRange.offset = offset;
		mappedRange.size = size;
		return vkInvalidateMappedMemoryRanges(device, 1, &mappedRange);
	}

	/**
	* Release all Vulkan resources held by this buffer
	*/
	void destroy() {
		if (buffer) {
			vkDestroyBuffer(device, buffer, nullptr);
		}
		if (memory) {
			vkFreeMemory(device, memory, nullptr);
		}
	}
};

// make_unique is not available in C++11
// Taken from Herb Sutter's blog (https://herbsutter.com/gotw/_102/)
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Thread {
private:
	bool destroying = false;
	std::thread worker;
	std::queue<std::function<void()>> jobQueue;
	std::mutex queueMutex;
	std::condition_variable condition;

	// Loop through all remaining jobs
	void queueLoop() {
		while (true) {
			std::function<void()> job;
			{
				std::unique_lock<std::mutex> lock(queueMutex);
				condition.wait(lock, [this] { return !jobQueue.empty() || destroying; });

				if (destroying) break;

				job = jobQueue.front();
			}

			job();

			{
				std::lock_guard<std::mutex> lock(queueMutex);
				jobQueue.pop();
				condition.notify_one();
			}
		}
	}

public:
	Thread() {
		worker = std::thread(&Thread::queueLoop, this);
	}

	~Thread() {
		if (worker.joinable()) {
			wait();
			queueMutex.lock();
			destroying = true;
			condition.notify_one();
			queueMutex.unlock();
			worker.join();
		}
	}

	// Add a new job to the thread's queue
	void addJob(std::function<void()> function) {
		std::lock_guard<std::mutex> lock(queueMutex);
		jobQueue.push(std::move(function));
		condition.notify_one();
	}

	// Wait until all work items have been finished
	void wait() {
		std::unique_lock<std::mutex> lock(queueMutex);
		condition.wait(lock, [this]() { return jobQueue.empty(); });
	}
};

class ThreadPool {
public:
	std::vector<std::unique_ptr<Thread>> threads;

	// Sets the number of threads to be allocted in this pool
	void setThreadCount(uint32_t count) {
		threads.clear();
		for (uint32_t i = 0; i < count; i++) {
			threads.push_back(make_unique<Thread>());
		}
	}

	// Wait until all threads have finished their work items
	void wait() {
		for (auto& thread : threads) {
			thread->wait();
		}
	}
};

class Frustum {
public:
	enum side { LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3, BACK = 4, FRONT = 5 };
	std::array<glm::vec4, 6> planes;

	void update(glm::mat4 matrix) {
		planes[LEFT].x = matrix[0].w + matrix[0].x;
		planes[LEFT].y = matrix[1].w + matrix[1].x;
		planes[LEFT].z = matrix[2].w + matrix[2].x;
		planes[LEFT].w = matrix[3].w + matrix[3].x;

		planes[RIGHT].x = matrix[0].w - matrix[0].x;
		planes[RIGHT].y = matrix[1].w - matrix[1].x;
		planes[RIGHT].z = matrix[2].w - matrix[2].x;
		planes[RIGHT].w = matrix[3].w - matrix[3].x;

		planes[TOP].x = matrix[0].w - matrix[0].y;
		planes[TOP].y = matrix[1].w - matrix[1].y;
		planes[TOP].z = matrix[2].w - matrix[2].y;
		planes[TOP].w = matrix[3].w - matrix[3].y;

		planes[BOTTOM].x = matrix[0].w + matrix[0].y;
		planes[BOTTOM].y = matrix[1].w + matrix[1].y;
		planes[BOTTOM].z = matrix[2].w + matrix[2].y;
		planes[BOTTOM].w = matrix[3].w + matrix[3].y;

		planes[BACK].x = matrix[0].w + matrix[0].z;
		planes[BACK].y = matrix[1].w + matrix[1].z;
		planes[BACK].z = matrix[2].w + matrix[2].z;
		planes[BACK].w = matrix[3].w + matrix[3].z;

		planes[FRONT].x = matrix[0].w - matrix[0].z;
		planes[FRONT].y = matrix[1].w - matrix[1].z;
		planes[FRONT].z = matrix[2].w - matrix[2].z;
		planes[FRONT].w = matrix[3].w - matrix[3].z;

		for (auto i = 0; i < planes.size(); i++)
		{
			float length = sqrtf(planes[i].x * planes[i].x + planes[i].y * planes[i].y + planes[i].z * planes[i].z);
			planes[i] /= length;
		}
	}

	bool checkSphere(glm::vec3 pos, float radius)
	{
		for (auto i = 0; i < planes.size(); i++)
		{
			if ((planes[i].x * pos.x) + (planes[i].y * pos.y) + (planes[i].z * pos.z) + planes[i].w <= -radius)
			{
				return false;
			}
		}
		return true;
	}
};

struct VulkanDevice {
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceFeatures enabledFeatures;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	std::vector<VkQueueFamilyProperties> queueFamilyProperties;
	std::vector<std::string> supportedExtensions;

	VkCommandPool commandPool = VK_NULL_HANDLE;

	bool enableDebugMarkers = false;

	struct {
		uint32_t graphics;
		uint32_t compute;
		uint32_t transfer;
	} queueFamilyIndices;

	operator VkDevice() { return logicalDevice; };

	VulkanDevice(VkPhysicalDevice physicalDevice) {
		assert(physicalDevice);
		this->physicalDevice = physicalDevice;

		vkGetPhysicalDeviceProperties(physicalDevice, &properties);
		vkGetPhysicalDeviceFeatures(physicalDevice, &features);
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
		assert(queueFamilyCount > 0);
		queueFamilyProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

		// Get list of supported extensions
		uint32_t extCount = 0;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, nullptr);
		if (extCount > 0) {
			std::vector<VkExtensionProperties> extensions(extCount);
			if (vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extCount, &extensions.front()) == VK_SUCCESS) {
				for (auto ext : extensions) {
					supportedExtensions.push_back(ext.extensionName);
				}
			}
		}
	}

	~VulkanDevice() {
		if (commandPool) {
			vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
		}
		if (logicalDevice) {
			vkDestroyDevice(logicalDevice, nullptr);
		}
	}
	
	uint32_t getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32* memTypeFound = nullptr) {
		for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
			if ((typeBits & 1) == 1) {
				if ((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
					if (memTypeFound) {
						*memTypeFound = true;
					}
					return i;
				}
			}
			typeBits >>= 1;
		}

		if (memTypeFound) {
			*memTypeFound = false;
			return 0;
		} else {
			throw std::runtime_error("Could not find a matching memory type");
		}
	}

	uint32_t getQueueFamilyIndex(VkQueueFlagBits queueFlags) {
		if (queueFlags & VK_QUEUE_COMPUTE_BIT) {
			for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++) {
				if ((queueFamilyProperties[i].queueFlags & queueFlags) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0)) {
					return i;
				}
			}
		}

		if (queueFlags & VK_QUEUE_TRANSFER_BIT) {
			for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++) {
				if ((queueFamilyProperties[i].queueFlags & queueFlags) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) && ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0)) {
					return i;
				}
			}
		}

		for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++) {
			if (queueFamilyProperties[i].queueFlags & queueFlags) {
				return i;
			}
		}

		throw std::runtime_error("Could not find a matching queue family index");
	}

	VkResult createLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures,
		std::vector<const char*> enabledExtensions,
		void* pNextChain,
		bool useSwapChain = true,
		VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT) {
		
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

		
		const float defaultQueuePriority(0.0f);

		if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT) {
			queueFamilyIndices.graphics = getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queueFamilyIndices.graphics;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfos.push_back(queueInfo);
		} else {
			queueFamilyIndices.graphics = VK_NULL_HANDLE;
		}

		if (requestedQueueTypes & VK_QUEUE_COMPUTE_BIT) {
			queueFamilyIndices.compute = getQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
			if (queueFamilyIndices.compute != queueFamilyIndices.graphics) {
				VkDeviceQueueCreateInfo queueInfo{};
				queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueInfo.queueFamilyIndex = queueFamilyIndices.compute;
				queueInfo.queueCount = 1;
				queueInfo.pQueuePriorities = &defaultQueuePriority;
				queueCreateInfos.push_back(queueInfo);
			}
		} else {
			queueFamilyIndices.compute = queueFamilyIndices.graphics;
		}

		if (requestedQueueTypes & VK_QUEUE_TRANSFER_BIT) {
			queueFamilyIndices.transfer = getQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
			if ((queueFamilyIndices.transfer != queueFamilyIndices.graphics) && (queueFamilyIndices.transfer != queueFamilyIndices.compute)) {
				VkDeviceQueueCreateInfo queueInfo{};
				queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueInfo.queueFamilyIndex = queueFamilyIndices.transfer;
				queueInfo.queueCount = 1;
				queueInfo.pQueuePriorities = &defaultQueuePriority;
				queueCreateInfos.push_back(queueInfo);
			}
		} else {
			queueFamilyIndices.transfer = queueFamilyIndices.graphics;
		}

		// Create the logical device representation
		std::vector<const char*> deviceExtensions(enabledExtensions);
		if (useSwapChain) {
			deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

		if (pNextChain) {
			VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};
			physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
			physicalDeviceFeatures2.features = enabledFeatures;
			physicalDeviceFeatures2.pNext = pNextChain;
			deviceCreateInfo.pEnabledFeatures = nullptr;
			deviceCreateInfo.pNext = &physicalDeviceFeatures2;
		}

		if (extensionSupported(VK_EXT_DEBUG_MARKER_EXTENSION_NAME)) {
			deviceExtensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
			enableDebugMarkers = true;
		}

		if (deviceExtensions.size() > 0) {
			deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
			deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
		}

		VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &logicalDevice);

		if (result == VK_SUCCESS) {
			commandPool = createCommandPool(queueFamilyIndices.graphics);
		}

		this->enabledFeatures = enabledFeatures;

		return result;
	}

	VkResult createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, VkDeviceSize size, VkBuffer* buffer, VkDeviceMemory* memory, void* data = nullptr) {
		VkBufferCreateInfo bufferCreateInfo = initializers::bufferCreateInfo(usageFlags, size);
		bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		tools::VK_VERIFY_SUCCESS(vkCreateBuffer(logicalDevice, &bufferCreateInfo, nullptr, buffer));

		VkMemoryRequirements memReqs;
		VkMemoryAllocateInfo memAlloc = initializers::memoryAllocateInfo();
		vkGetBufferMemoryRequirements(logicalDevice, *buffer, &memReqs);
		memAlloc.allocationSize = memReqs.size;
		memAlloc.memoryTypeIndex = getMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);
		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(logicalDevice, &memAlloc, nullptr, memory));

		if (data != nullptr) {
			void* mapped;
			tools::VK_VERIFY_SUCCESS(vkMapMemory(logicalDevice, *memory, 0, size, 0, &mapped));
			memcpy(mapped, data, size);
			if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0) {
				VkMappedMemoryRange mappedRange = initializers::mappedMemoryRange();
				mappedRange.memory = *memory;
				mappedRange.offset = 0;
				mappedRange.size = size;
				vkFlushMappedMemoryRanges(logicalDevice, 1, &mappedRange);
			}
			vkUnmapMemory(logicalDevice, *memory);
		}

		tools::VK_VERIFY_SUCCESS(vkBindBufferMemory(logicalDevice, *buffer, *memory, 0));

		return VK_SUCCESS;
	}

	VkResult createBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags, Buffer* buffer, VkDeviceSize size, void* data = nullptr) {
		buffer->device = logicalDevice;

		VkBufferCreateInfo bufferCreateInfo = initializers::bufferCreateInfo(usageFlags, size);
		tools::VK_VERIFY_SUCCESS(vkCreateBuffer(logicalDevice, &bufferCreateInfo, nullptr, &buffer->buffer));

		VkMemoryRequirements memReqs;
		VkMemoryAllocateInfo memAlloc = initializers::memoryAllocateInfo();
		vkGetBufferMemoryRequirements(logicalDevice, buffer->buffer, &memReqs);
		memAlloc.allocationSize = memReqs.size;
		memAlloc.memoryTypeIndex = getMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);
		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(logicalDevice, &memAlloc, nullptr, &buffer->memory));

		buffer->alignment = memReqs.alignment;
		buffer->size = memAlloc.allocationSize;
		buffer->usageFlags = usageFlags;
		buffer->memoryPropertyFlags = memoryPropertyFlags;

		if (data) {
			tools::VK_VERIFY_SUCCESS(buffer->map());
			memcpy(buffer->mapped, data, size);
			if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0) buffer->flush();

			buffer->unmap();
		}

		buffer->setupDescriptor();

		return buffer->bind();
	}

	void copyBuffer(Buffer* src, Buffer* dst, VkQueue queue, VkBufferCopy* copyRegion = nullptr) {
		assert(dst->size <= src->size);
		assert(src->buffer);
		VkCommandBuffer copyCmd = createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
		VkBufferCopy bufferCopy{};
		if (copyRegion == nullptr) {
			bufferCopy.size = src->size;
		} else {
			bufferCopy = *copyRegion;
		}

		vkCmdCopyBuffer(copyCmd, src->buffer, dst->buffer, 1, &bufferCopy);

		flushCommandBuffer(copyCmd, queue);
	}

	VkCommandPool createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT) {
		VkCommandPoolCreateInfo cmdPoolInfo = {};
		cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
		cmdPoolInfo.flags = createFlags;
		VkCommandPool cmdPool;
		tools::VK_VERIFY_SUCCESS(vkCreateCommandPool(logicalDevice, &cmdPoolInfo, nullptr, &cmdPool));
		return cmdPool;
	}

	VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, bool begin = false) {
		VkCommandBufferAllocateInfo cmdBufAllocateInfo = initializers::commandBufferAllocateInfo(commandPool, level, 1);

		VkCommandBuffer cmdBuffer;
		tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(logicalDevice, &cmdBufAllocateInfo, &cmdBuffer));

		if (begin) {
			VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();
			tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(cmdBuffer, &cmdBufInfo));
		}

		return cmdBuffer;
	}

	void flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, bool free = true) {
		if (commandBuffer == VK_NULL_HANDLE) {
			return;
		}

		tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(commandBuffer));

		VkSubmitInfo submitInfo = initializers::submitInfo();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		VkFenceCreateInfo fenceInfo = initializers::fenceCreateInfo(VK_FLAGS_NONE);
		VkFence fence;
		tools::VK_VERIFY_SUCCESS(vkCreateFence(logicalDevice, &fenceInfo, nullptr, &fence));

		tools::VK_VERIFY_SUCCESS(vkQueueSubmit(queue, 1, &submitInfo, fence));
		tools::VK_VERIFY_SUCCESS(vkWaitForFences(logicalDevice, 1, &fence, VK_TRUE, DEFAULT_FENCE_TIMEOUT));

		vkDestroyFence(logicalDevice, fence, nullptr);

		if (free) {
			vkFreeCommandBuffers(logicalDevice, commandPool, 1, &commandBuffer);
		}
	}

	bool extensionSupported(std::string extension) {
		return (std::find(supportedExtensions.begin(), supportedExtensions.end(), extension) != supportedExtensions.end());
	}
};

class Texture {
public:
	VulkanDevice* device;
	VkImage image;
	VkImageLayout imageLayout;
	VkDeviceMemory deviceMemory;
	VkImageView view;
	uint32_t width, height;
	uint32_t mipLevels;
	uint32_t layerCount;
	VkDescriptorImageInfo descriptor;

	VkSampler sampler;

	void updateDescriptor() {
		descriptor.sampler = sampler;
		descriptor.imageView = view;
		descriptor.imageLayout = imageLayout;
	}

	void destroy() {
		vkDestroyImageView(device->logicalDevice, view, nullptr);
		vkDestroyImage(device->logicalDevice, image, nullptr);
		if (sampler) {
			vkDestroySampler(device->logicalDevice, sampler, nullptr);
		}
		vkFreeMemory(device->logicalDevice, deviceMemory, nullptr);
	}
};

class Texture2D : public Texture {
public:
	void loadFromFile(
		std::string filename,
		VkFormat format,
		VulkanDevice* device,
		VkQueue copyQueue,
		VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_SAMPLED_BIT,
		VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		bool forceLinear = false)
	{

		if (!tools::fileExists(filename)) {
			tools::exitFatal("Could not load texture from " + filename + "\n\nThe file may be part of the additional asset pack.\n\nRun \"download_assets.py\" in the repository root to download the latest version.", -1);
		}
		gli::texture2d tex2D(gli::load(filename.c_str()));
		assert(!tex2D.empty());

		this->device = device;
		width = static_cast<uint32_t>(tex2D[0].extent().x);
		height = static_cast<uint32_t>(tex2D[0].extent().y);
		mipLevels = static_cast<uint32_t>(tex2D.levels());

		VkFormatProperties formatProperties;
		vkGetPhysicalDeviceFormatProperties(device->physicalDevice, format, &formatProperties);

		VkBool32 useStaging = !forceLinear;

		VkMemoryAllocateInfo memAllocInfo = initializers::memoryAllocateInfo();
		VkMemoryRequirements memReqs;

		VkCommandBuffer copyCmd = device->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

		if (useStaging) {
			VkBuffer stagingBuffer;
			VkDeviceMemory stagingMemory;

			VkBufferCreateInfo bufferCreateInfo = initializers::bufferCreateInfo();
			bufferCreateInfo.size = tex2D.size();
			bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			tools::VK_VERIFY_SUCCESS(vkCreateBuffer(device->logicalDevice, &bufferCreateInfo, nullptr, &stagingBuffer));

			vkGetBufferMemoryRequirements(device->logicalDevice, stagingBuffer, &memReqs);

			memAllocInfo.allocationSize = memReqs.size;
			memAllocInfo.memoryTypeIndex = device->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device->logicalDevice, &memAllocInfo, nullptr, &stagingMemory));
			tools::VK_VERIFY_SUCCESS(vkBindBufferMemory(device->logicalDevice, stagingBuffer, stagingMemory, 0));

			uint8_t* data;
			tools::VK_VERIFY_SUCCESS(vkMapMemory(device->logicalDevice, stagingMemory, 0, memReqs.size, 0, (void**)& data));
			memcpy(data, tex2D.data(), tex2D.size());
			vkUnmapMemory(device->logicalDevice, stagingMemory);

			std::vector<VkBufferImageCopy> bufferCopyRegions;
			uint32_t offset = 0;

			for (uint32_t i = 0; i < mipLevels; i++) {
				VkBufferImageCopy bufferCopyRegion = {};
				bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				bufferCopyRegion.imageSubresource.mipLevel = i;
				bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
				bufferCopyRegion.imageSubresource.layerCount = 1;
				bufferCopyRegion.imageExtent.width = static_cast<uint32_t>(tex2D[i].extent().x);
				bufferCopyRegion.imageExtent.height = static_cast<uint32_t>(tex2D[i].extent().y);
				bufferCopyRegion.imageExtent.depth = 1;
				bufferCopyRegion.bufferOffset = offset;

				bufferCopyRegions.push_back(bufferCopyRegion);

				offset += static_cast<uint32_t>(tex2D[i].size());
			}

			VkImageCreateInfo imageCreateInfo = initializers::imageCreateInfo();
			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
			imageCreateInfo.format = format;
			imageCreateInfo.mipLevels = mipLevels;
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageCreateInfo.extent = { width, height, 1 };
			imageCreateInfo.usage = imageUsageFlags;
			if (!(imageCreateInfo.usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT)) {
				imageCreateInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			}
			tools::VK_VERIFY_SUCCESS(vkCreateImage(device->logicalDevice, &imageCreateInfo, nullptr, &image));

			vkGetImageMemoryRequirements(device->logicalDevice, image, &memReqs);

			memAllocInfo.allocationSize = memReqs.size;

			memAllocInfo.memoryTypeIndex = device->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device->logicalDevice, &memAllocInfo, nullptr, &deviceMemory));
			tools::VK_VERIFY_SUCCESS(vkBindImageMemory(device->logicalDevice, image, deviceMemory, 0));

			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = mipLevels;
			subresourceRange.layerCount = 1;

			tools::setImageLayout(
				copyCmd,
				image,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				subresourceRange);

			vkCmdCopyBufferToImage(
				copyCmd,
				stagingBuffer,
				image,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				static_cast<uint32_t>(bufferCopyRegions.size()),
				bufferCopyRegions.data()
			);

			this->imageLayout = imageLayout;
			tools::setImageLayout(
				copyCmd,
				image,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				imageLayout,
				subresourceRange);

			device->flushCommandBuffer(copyCmd, copyQueue);

			vkFreeMemory(device->logicalDevice, stagingMemory, nullptr);
			vkDestroyBuffer(device->logicalDevice, stagingBuffer, nullptr);
		} else {
			assert(formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT);

			VkImage mappableImage;
			VkDeviceMemory mappableMemory;

			VkImageCreateInfo imageCreateInfo = initializers::imageCreateInfo();
			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
			imageCreateInfo.format = format;
			imageCreateInfo.extent = { width, height, 1 };
			imageCreateInfo.mipLevels = 1;
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.tiling = VK_IMAGE_TILING_LINEAR;
			imageCreateInfo.usage = imageUsageFlags;
			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

			tools::VK_VERIFY_SUCCESS(vkCreateImage(device->logicalDevice, &imageCreateInfo, nullptr, &mappableImage));

			vkGetImageMemoryRequirements(device->logicalDevice, mappableImage, &memReqs);
			memAllocInfo.allocationSize = memReqs.size;

			memAllocInfo.memoryTypeIndex = device->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device->logicalDevice, &memAllocInfo, nullptr, &mappableMemory));

			tools::VK_VERIFY_SUCCESS(vkBindImageMemory(device->logicalDevice, mappableImage, mappableMemory, 0));

			VkImageSubresource subRes = {};
			subRes.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subRes.mipLevel = 0;

			VkSubresourceLayout subResLayout;
			void* data;

			vkGetImageSubresourceLayout(device->logicalDevice, mappableImage, &subRes, &subResLayout);

			tools::VK_VERIFY_SUCCESS(vkMapMemory(device->logicalDevice, mappableMemory, 0, memReqs.size, 0, &data));

			memcpy(data, tex2D[subRes.mipLevel].data(), tex2D[subRes.mipLevel].size());

			vkUnmapMemory(device->logicalDevice, mappableMemory);

			image = mappableImage;
			deviceMemory = mappableMemory;
			this->imageLayout = imageLayout;

			tools::setImageLayout(copyCmd, image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED, imageLayout);

			device->flushCommandBuffer(copyCmd, copyQueue);
		}

		VkSamplerCreateInfo samplerCreateInfo = {};
		samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.mipLodBias = 0.0f;
		samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
		samplerCreateInfo.minLod = 0.0f;
		samplerCreateInfo.maxLod = (useStaging) ? (float)mipLevels : 0.0f;
		samplerCreateInfo.maxAnisotropy = device->enabledFeatures.samplerAnisotropy ? device->properties.limits.maxSamplerAnisotropy : 1.0f;
		samplerCreateInfo.anisotropyEnable = device->enabledFeatures.samplerAnisotropy;
		samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		tools::VK_VERIFY_SUCCESS(vkCreateSampler(device->logicalDevice, &samplerCreateInfo, nullptr, &sampler));

		VkImageViewCreateInfo viewCreateInfo = {};
		viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewCreateInfo.format = format;
		viewCreateInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		viewCreateInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		viewCreateInfo.subresourceRange.levelCount = (useStaging) ? mipLevels : 1;
		viewCreateInfo.image = image;
		tools::VK_VERIFY_SUCCESS(vkCreateImageView(device->logicalDevice, &viewCreateInfo, nullptr, &view));

		updateDescriptor();
	}

	void fromBuffer(
		void* buffer,
		VkDeviceSize bufferSize,
		VkFormat format,
		uint32_t texWidth,
		uint32_t texHeight,
		VulkanDevice* device,
		VkQueue copyQueue,
		VkFilter filter = VK_FILTER_LINEAR,
		VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_SAMPLED_BIT,
		VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
	{
		assert(buffer);

		this->device = device;
		width = texWidth;
		height = texHeight;
		mipLevels = 1;

		VkMemoryAllocateInfo memAllocInfo = initializers::memoryAllocateInfo();
		VkMemoryRequirements memReqs;

		VkCommandBuffer copyCmd = device->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMemory;

		VkBufferCreateInfo bufferCreateInfo = initializers::bufferCreateInfo();
		bufferCreateInfo.size = bufferSize;
		bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		tools::VK_VERIFY_SUCCESS(vkCreateBuffer(device->logicalDevice, &bufferCreateInfo, nullptr, &stagingBuffer));

		vkGetBufferMemoryRequirements(device->logicalDevice, stagingBuffer, &memReqs);

		memAllocInfo.allocationSize = memReqs.size;
		memAllocInfo.memoryTypeIndex = device->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device->logicalDevice, &memAllocInfo, nullptr, &stagingMemory));
		tools::VK_VERIFY_SUCCESS(vkBindBufferMemory(device->logicalDevice, stagingBuffer, stagingMemory, 0));

		uint8_t* data;
		tools::VK_VERIFY_SUCCESS(vkMapMemory(device->logicalDevice, stagingMemory, 0, memReqs.size, 0, (void**)& data));
		memcpy(data, buffer, bufferSize);
		vkUnmapMemory(device->logicalDevice, stagingMemory);

		VkBufferImageCopy bufferCopyRegion = {};
		bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		bufferCopyRegion.imageSubresource.mipLevel = 0;
		bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
		bufferCopyRegion.imageSubresource.layerCount = 1;
		bufferCopyRegion.imageExtent.width = width;
		bufferCopyRegion.imageExtent.height = height;
		bufferCopyRegion.imageExtent.depth = 1;
		bufferCopyRegion.bufferOffset = 0;

		VkImageCreateInfo imageCreateInfo = initializers::imageCreateInfo();
		imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
		imageCreateInfo.format = format;
		imageCreateInfo.mipLevels = mipLevels;
		imageCreateInfo.arrayLayers = 1;
		imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageCreateInfo.extent = { width, height, 1 };
		imageCreateInfo.usage = imageUsageFlags;
		if (!(imageCreateInfo.usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT)) {
			imageCreateInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		}
		tools::VK_VERIFY_SUCCESS(vkCreateImage(device->logicalDevice, &imageCreateInfo, nullptr, &image));

		vkGetImageMemoryRequirements(device->logicalDevice, image, &memReqs);

		memAllocInfo.allocationSize = memReqs.size;

		memAllocInfo.memoryTypeIndex = device->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device->logicalDevice, &memAllocInfo, nullptr, &deviceMemory));
		tools::VK_VERIFY_SUCCESS(vkBindImageMemory(device->logicalDevice, image, deviceMemory, 0));

		VkImageSubresourceRange subresourceRange = {};
		subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = mipLevels;
		subresourceRange.layerCount = 1;

		tools::setImageLayout(
			copyCmd,
			image,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			subresourceRange);

		vkCmdCopyBufferToImage(
			copyCmd,
			stagingBuffer,
			image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&bufferCopyRegion
		);

		this->imageLayout = imageLayout;
		tools::setImageLayout(
			copyCmd,
			image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			imageLayout,
			subresourceRange);

		device->flushCommandBuffer(copyCmd, copyQueue);

		vkFreeMemory(device->logicalDevice, stagingMemory, nullptr);
		vkDestroyBuffer(device->logicalDevice, stagingBuffer, nullptr);

		VkSamplerCreateInfo samplerCreateInfo = {};
		samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerCreateInfo.magFilter = filter;
		samplerCreateInfo.minFilter = filter;
		samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.mipLodBias = 0.0f;
		samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
		samplerCreateInfo.minLod = 0.0f;
		samplerCreateInfo.maxLod = 0.0f;
		samplerCreateInfo.maxAnisotropy = 1.0f;
		tools::VK_VERIFY_SUCCESS(vkCreateSampler(device->logicalDevice, &samplerCreateInfo, nullptr, &sampler));

		VkImageViewCreateInfo viewCreateInfo = {};
		viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewCreateInfo.pNext = NULL;
		viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewCreateInfo.format = format;
		viewCreateInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		viewCreateInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		viewCreateInfo.subresourceRange.levelCount = 1;
		viewCreateInfo.image = image;
		tools::VK_VERIFY_SUCCESS(vkCreateImageView(device->logicalDevice, &viewCreateInfo, nullptr, &view));

		updateDescriptor();
	}
};

typedef struct _SwapChainBuffers {
	VkImage image;
	VkImageView view;
} SwapChainBuffer;

class VulkanSwapChain {
private:
	VkInstance instance;
	VkDevice device;
	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;
	// Function pointers
	PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR;
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR;
	PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
	PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
	PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
	PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
	PFN_vkQueuePresentKHR fpQueuePresentKHR;
public:
	VkFormat colorFormat;
	VkColorSpaceKHR colorSpace;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;
	uint32_t imageCount;
	std::vector<VkImage> images;
	std::vector<SwapChainBuffer> buffers;
	uint32_t queueNodeIndex = UINT32_MAX;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
	void initSurface(void* platformHandle, void* platformWindow)
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	void initSurface(void* view)
#endif
	{
		VkResult err = VK_SUCCESS;

		// Create the os-specific surface
#if defined(VK_USE_PLATFORM_WIN32_KHR)
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hinstance = (HINSTANCE)platformHandle;
		surfaceCreateInfo.hwnd = (HWND)platformWindow;
		err = vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
		VkMacOSSurfaceCreateInfoMVK surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
		surfaceCreateInfo.pNext = NULL;
		surfaceCreateInfo.flags = 0;
		surfaceCreateInfo.pView = view;
		err = vkCreateMacOSSurfaceMVK(instance, &surfaceCreateInfo, NULL, &surface);
#endif

		if (err != VK_SUCCESS) {
			tools::exitFatal("Could not create surface!", err);
		}

		uint32_t queueCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, NULL);
		assert(queueCount >= 1);

		std::vector<VkQueueFamilyProperties> queueProps(queueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueProps.data());

		std::vector<VkBool32> supportsPresent(queueCount);
		for (uint32_t i = 0; i < queueCount; i++) {
			fpGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &supportsPresent[i]);
		}

		uint32_t graphicsQueueNodeIndex = UINT32_MAX;
		uint32_t presentQueueNodeIndex = UINT32_MAX;
		for (uint32_t i = 0; i < queueCount; i++) {
			if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
				if (graphicsQueueNodeIndex == UINT32_MAX) {
					graphicsQueueNodeIndex = i;
				}

				if (supportsPresent[i] == VK_TRUE) {
					graphicsQueueNodeIndex = i;
					presentQueueNodeIndex = i;
					break;
				}
			}
		}
		if (presentQueueNodeIndex == UINT32_MAX) {
			for (uint32_t i = 0; i < queueCount; ++i) {
				if (supportsPresent[i] == VK_TRUE) {
					presentQueueNodeIndex = i;
					break;
				}
			}
		}

		if (graphicsQueueNodeIndex == UINT32_MAX || presentQueueNodeIndex == UINT32_MAX) {
			tools::exitFatal("Could not find a graphics and/or presenting queue!", -1);
		}

		if (graphicsQueueNodeIndex != presentQueueNodeIndex) {
			tools::exitFatal("Separate graphics and presenting queues are not supported yet!", -1);
		}

		queueNodeIndex = graphicsQueueNodeIndex;

		uint32_t formatCount;
		tools::VK_VERIFY_SUCCESS(fpGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, NULL));
		assert(formatCount > 0);

		std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
		tools::VK_VERIFY_SUCCESS(fpGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, surfaceFormats.data()));

		if ((formatCount == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)) {
			colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
			colorSpace = surfaceFormats[0].colorSpace;
		} else {
			bool found_B8G8R8A8_UNORM = false;
			for (auto&& surfaceFormat : surfaceFormats) {
				if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) {
					colorFormat = surfaceFormat.format;
					colorSpace = surfaceFormat.colorSpace;
					found_B8G8R8A8_UNORM = true;
					break;
				}
			}

			if (!found_B8G8R8A8_UNORM) {
				colorFormat = surfaceFormats[0].format;
				colorSpace = surfaceFormats[0].colorSpace;
			}
		}
	}

	void connect(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device) {
		this->instance = instance;
		this->physicalDevice = physicalDevice;
		this->device = device;
		GET_INSTANCE_PROC_ADDR(instance, GetPhysicalDeviceSurfaceSupportKHR);
		GET_INSTANCE_PROC_ADDR(instance, GetPhysicalDeviceSurfaceCapabilitiesKHR);
		GET_INSTANCE_PROC_ADDR(instance, GetPhysicalDeviceSurfaceFormatsKHR);
		GET_INSTANCE_PROC_ADDR(instance, GetPhysicalDeviceSurfacePresentModesKHR);
		GET_DEVICE_PROC_ADDR(device, CreateSwapchainKHR);
		GET_DEVICE_PROC_ADDR(device, DestroySwapchainKHR);
		GET_DEVICE_PROC_ADDR(device, GetSwapchainImagesKHR);
		GET_DEVICE_PROC_ADDR(device, AcquireNextImageKHR);
		GET_DEVICE_PROC_ADDR(device, QueuePresentKHR);
	}

	void create(uint32_t* width, uint32_t* height, bool vsync = false) {
		VkSwapchainKHR oldSwapchain = swapChain;

		VkSurfaceCapabilitiesKHR surfCaps;
		tools::VK_VERIFY_SUCCESS(fpGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfCaps));

		uint32_t presentModeCount;
		tools::VK_VERIFY_SUCCESS(fpGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, NULL));
		assert(presentModeCount > 0);

		std::vector<VkPresentModeKHR> presentModes(presentModeCount);
		tools::VK_VERIFY_SUCCESS(fpGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data()));

		VkExtent2D swapchainExtent = {};
		if (surfCaps.currentExtent.width == (uint32_t)-1) {
			swapchainExtent.width = *width;
			swapchainExtent.height = *height;
		} else {
			swapchainExtent = surfCaps.currentExtent;
			*width = surfCaps.currentExtent.width;
			*height = surfCaps.currentExtent.height;
		}



		VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

		if (!vsync) {
			for (size_t i = 0; i < presentModeCount; i++) {
				if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
					swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
					break;
				}
				if ((swapchainPresentMode != VK_PRESENT_MODE_MAILBOX_KHR) && (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR)) {
					swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
				}
			}
		}

		uint32_t desiredNumberOfSwapchainImages = surfCaps.minImageCount + 1;
		if ((surfCaps.maxImageCount > 0) && (desiredNumberOfSwapchainImages > surfCaps.maxImageCount)) {
			desiredNumberOfSwapchainImages = surfCaps.maxImageCount;
		}

		VkSurfaceTransformFlagsKHR preTransform;
		if (surfCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
			preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		} else {
			preTransform = surfCaps.currentTransform;
		}

		VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		std::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
		};
		for (auto& compositeAlphaFlag : compositeAlphaFlags) {
			if (surfCaps.supportedCompositeAlpha & compositeAlphaFlag) {
				compositeAlpha = compositeAlphaFlag;
				break;
			};
		}

		VkSwapchainCreateInfoKHR swapchainCI = {};
		swapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCI.pNext = NULL;
		swapchainCI.surface = surface;
		swapchainCI.minImageCount = desiredNumberOfSwapchainImages;
		swapchainCI.imageFormat = colorFormat;
		swapchainCI.imageColorSpace = colorSpace;
		swapchainCI.imageExtent = { swapchainExtent.width, swapchainExtent.height };
		swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCI.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
		swapchainCI.imageArrayLayers = 1;
		swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCI.queueFamilyIndexCount = 0;
		swapchainCI.pQueueFamilyIndices = NULL;
		swapchainCI.presentMode = swapchainPresentMode;
		swapchainCI.oldSwapchain = oldSwapchain;
		swapchainCI.clipped = VK_TRUE;
		swapchainCI.compositeAlpha = compositeAlpha;

		if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
			swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		}

		if (surfCaps.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
			swapchainCI.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		}

		tools::VK_VERIFY_SUCCESS(fpCreateSwapchainKHR(device, &swapchainCI, nullptr, &swapChain));

		if (oldSwapchain != VK_NULL_HANDLE) {
			for (uint32_t i = 0; i < imageCount; i++) {
				vkDestroyImageView(device, buffers[i].view, nullptr);
			}
			fpDestroySwapchainKHR(device, oldSwapchain, nullptr);
		}
		tools::VK_VERIFY_SUCCESS(fpGetSwapchainImagesKHR(device, swapChain, &imageCount, NULL));

		// Get the swap chain images
		images.resize(imageCount);
		tools::VK_VERIFY_SUCCESS(fpGetSwapchainImagesKHR(device, swapChain, &imageCount, images.data()));

		// Get the swap chain buffers containing the image and imageview
		buffers.resize(imageCount);
		for (uint32_t i = 0; i < imageCount; i++)
		{
			VkImageViewCreateInfo colorAttachmentView = {};
			colorAttachmentView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			colorAttachmentView.pNext = NULL;
			colorAttachmentView.format = colorFormat;
			colorAttachmentView.components = {
				VK_COMPONENT_SWIZZLE_R,
				VK_COMPONENT_SWIZZLE_G,
				VK_COMPONENT_SWIZZLE_B,
				VK_COMPONENT_SWIZZLE_A
			};
			colorAttachmentView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			colorAttachmentView.subresourceRange.baseMipLevel = 0;
			colorAttachmentView.subresourceRange.levelCount = 1;
			colorAttachmentView.subresourceRange.baseArrayLayer = 0;
			colorAttachmentView.subresourceRange.layerCount = 1;
			colorAttachmentView.viewType = VK_IMAGE_VIEW_TYPE_2D;
			colorAttachmentView.flags = 0;

			buffers[i].image = images[i];

			colorAttachmentView.image = buffers[i].image;

			tools::VK_VERIFY_SUCCESS(vkCreateImageView(device, &colorAttachmentView, nullptr, &buffers[i].view));
		}
	}

	/**
	* Acquires the next image in the swap chain
	*
	* @param presentCompleteSemaphore (Optional) Semaphore that is signaled when the image is ready for use
	* @param imageIndex Pointer to the image index that will be increased if the next image could be acquired
	*
	* @note The function will always wait until the next image has been acquired by setting timeout to UINT64_MAX
	*
	* @return VkResult of the image acquisition
	*/
	VkResult acquireNextImage(VkSemaphore presentCompleteSemaphore, uint32_t* imageIndex)
	{
		// By setting timeout to UINT64_MAX we will always wait until the next image has been acquired or an actual error is thrown
		// With that we don't have to handle VK_NOT_READY
		return fpAcquireNextImageKHR(device, swapChain, UINT64_MAX, presentCompleteSemaphore, (VkFence)nullptr, imageIndex);
	}

	/**
	* Queue an image for presentation
	*
	* @param queue Presentation queue for presenting the image
	* @param imageIndex Index of the swapchain image to queue for presentation
	* @param waitSemaphore (Optional) Semaphore that is waited on before the image is presented (only used if != VK_NULL_HANDLE)
	*
	* @return VkResult of the queue presentation
	*/
	VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE)
	{
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = NULL;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapChain;
		presentInfo.pImageIndices = &imageIndex;
		// Check if a wait semaphore has been specified to wait for before presenting the image
		if (waitSemaphore != VK_NULL_HANDLE)
		{
			presentInfo.pWaitSemaphores = &waitSemaphore;
			presentInfo.waitSemaphoreCount = 1;
		}
		return fpQueuePresentKHR(queue, &presentInfo);
	}


	/**
	* Destroy and free Vulkan resources used for the swapchain
	*/
	void cleanup()
	{
		if (swapChain != VK_NULL_HANDLE)
		{
			for (uint32_t i = 0; i < imageCount; i++)
			{
				vkDestroyImageView(device, buffers[i].view, nullptr);
			}
		}
		if (surface != VK_NULL_HANDLE)
		{
			fpDestroySwapchainKHR(device, swapChain, nullptr);
			vkDestroySurfaceKHR(instance, surface, nullptr);
		}
		surface = VK_NULL_HANDLE;
		swapChain = VK_NULL_HANDLE;
	}
};

/** @brief Stores vertex layout components for model loading and Vulkan vertex input and atribute bindings  */
struct VertexLayout {
public:
	/** @brief Components used to generate vertices from */
	std::vector<Component> components;

	VertexLayout(std::vector<Component> components) {
		this->components = std::move(components);
	}

	uint32_t stride() {
		uint32_t res = 0;
		for (auto& component : components) {
			switch (component) {
			case VERTEX_COMPONENT_UV:
				res += 2 * sizeof(float);
				break;
			case VERTEX_COMPONENT_DUMMY_FLOAT:
				res += sizeof(float);
				break;
			case VERTEX_COMPONENT_DUMMY_VEC4:
				res += 4 * sizeof(float);
				break;
			default:
				// All components except the ones listed above are made up of 3 floats
				res += 3 * sizeof(float);
			}
		}
		return res;
	}
};

/** @brief Used to parametrize model loading */
struct ModelCreateInfo {
	glm::vec3 center;
	glm::vec3 scale;
	glm::vec2 uvscale;
	VkMemoryPropertyFlags memoryPropertyFlags = 0;

	ModelCreateInfo() : center(glm::vec3(0.0f)), scale(glm::vec3(1.0f)), uvscale(glm::vec2(1.0f)) {};

	ModelCreateInfo(glm::vec3 scale, glm::vec2 uvscale, glm::vec3 center) {
		this->center = center;
		this->scale = scale;
		this->uvscale = uvscale;
	}

	ModelCreateInfo(float scale, float uvscale, float center) {
		this->center = glm::vec3(center);
		this->scale = glm::vec3(scale);
		this->uvscale = glm::vec2(uvscale);
	}

};

enum AnimationType {
	ANI_STATIC,
	ANI_KEYFRAMES,
	ANI_BILLIARDS,
	ANI_MOCAP,
	ANI_CUSTOM,

	ANI_TYPE_NUM
};

struct Model {
	VkDevice device = nullptr;
	Buffer vertices;
	Buffer indices;
	uint32_t indexCount = 0;
	uint32_t vertexCount = 0;
	bool enabled = true;
	std::mutex _lock;

	// animation attributes
	AnimationType aniType = ANI_STATIC;
	//Physics Animations
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 translation_vector = glm::vec3(0, 0, 0);
	glm::quat rotation = glm::quat();
	glm::vec3 rotation_axis = glm::vec3(0,0,0);
	glm::vec3 scaling = glm::vec3(1.0, 1.0, 1.0);
	float rotation_speed = 0.0f;
	float scale = 1.0f;
	float rot_angle = 0.0f;

	float collision_radius = 1.0f;
	bool collisions_enabled = true;
	bool moving = false;
	bool movement_pinned = true;
	float mass = 10.0f;

	/** @brief Stores vertex and index base and counts for each part of a model */
	struct ModelPart {
		uint32_t vertexBase;
		uint32_t vertexCount;
		uint32_t indexBase;
		uint32_t indexCount;

		float collision_radius = 1.0f;
	};
	std::vector<ModelPart> parts;

	static const int defaultFlags = aiProcess_FlipWindingOrder | aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals;

	struct Dimension {
		glm::vec3 min = glm::vec3(FLT_MAX);
		glm::vec3 max = glm::vec3(-FLT_MAX);
		glm::vec3 size;
	} dim;

	Model() {}
	Model(const Model& m) {
		device = m.device;
		vertices = m.vertices;
		indices = m.indices;
		indexCount = m.indexCount;
		vertexCount = m.vertexCount;
		enabled = m.enabled;

		// animation attributes
		aniType = m.aniType;

		position = m.position;
		translation_vector = m.translation_vector;
		rotation = m.rotation;
		rotation_axis = m.rotation_axis;
		rotation_speed = m.rotation_speed;
		scale = m.scale;
		scaling = m.scaling;
		rot_angle = m.rot_angle;

		collision_radius = m.collision_radius;
		collisions_enabled = m.collisions_enabled;
		moving = m.moving;
		movement_pinned = m.movement_pinned;
		mass = m.mass;

		parts = m.parts;
	}

	void BilliardMovements(float interval_length, std::vector<Model>& interactibles) {
		if (!moving || !collisions_enabled) {
			// just in case
			translation_vector = glm::vec3(0.0f, 0.0f, 0.0f);
			return;
		}

		const float rolling_friction = 0.5f; //for slowing down the translation_speed
		const float ELASTICITY = 1.0f;

		float distance = interval_length * glm::length(translation_vector);
		glm::vec3 target_position = distance * translation_vector + position;

		// for each Model in the interactibles vector
		bool intersects = false;
		for (int i = 0; i < interactibles.size(); i++) {
			Model& m = interactibles.at(i);
			if ((this == &m) || !m.collisions_enabled || m.aniType != ANI_BILLIARDS) {
				//skip self, collisions disabled, or if it's not a billiards ball
				continue;
			}

			//does it collide?
			double radiusSum = collision_radius + m.collision_radius;
			glm::vec3 collisionNormal = position - m.position;
			bool intersects = (glm::dot(collisionNormal, collisionNormal) <= radiusSum * radiusSum) ? true : false;

			//if so update then break out
			if (intersects) {
				float radiusSum = collision_radius + m.collision_radius;
				glm::vec3 collisionNormal = position - m.position;

				float distance = length(collisionNormal);
				float penetration = radiusSum - distance;

				glm::vec3 relativeVelocity = m.translation_vector - translation_vector;
				
				float vDOTn;
				float numerator;
				float denominator;
				float impulse;

				collisionNormal = normalize(collisionNormal);

				position = position + 0.5f * penetration * collisionNormal;
				m.position = m.position - 0.5f * penetration * collisionNormal;
				vDOTn = dot(relativeVelocity, collisionNormal);

				if (vDOTn < 0.0) {
					return;
				}

				numerator = -(1.0 + ELASTICITY) * vDOTn;
				denominator = (1.0 / m.mass + 1.0 / mass);
				impulse = numerator / denominator;

				m.translation_vector = m.translation_vector + impulse / m.mass * collisionNormal;
				if (glm::length(m.translation_vector) > 0.01f) {
					m.moving = true;
				}
				translation_vector = translation_vector - impulse / mass * collisionNormal;

				break;
			}
		}
		

		// now check the walls
		if (target_position.x < 0 && translation_vector.x < 0) {
			translation_vector.x *= -1;
		}
		if (20 < target_position.x && 1.0 < translation_vector.x) {
			translation_vector.x *= -1;
		}
		if (target_position.y < 0 && translation_vector.y < 0) {
			translation_vector.y *= -1;
		}
		if (20 < target_position.y && 1.0 < translation_vector.y) {
			translation_vector.y *= -1;
		}
		translation_vector.z = 0;
		
		//update velocity with the time interval's friction component
		//stop the ball if it "flips" direction
		float translation_coeff = (glm::length(translation_vector) - interval_length*rolling_friction);
		if (translation_coeff < 0.001) {
			moving = false;
			translation_vector *= 0;
		} else {
			translation_vector = translation_coeff * glm::normalize(translation_vector);
		}

		position = distance * translation_vector + position;
		position.z = 0; // we -should- check gravity through this process but fuck it, set to 0 to prevent floating point drift
	}

	/** @brief Release all Vulkan resources of this model */
	void destroy() {
		assert(device);
		// TODO Add empty buffer check
		vkDestroyBuffer(device, vertices.buffer, nullptr);
		vkFreeMemory(device, vertices.memory, nullptr);

		if (indices.buffer != VK_NULL_HANDLE) {
			vkDestroyBuffer(device, indices.buffer, nullptr);
			vkFreeMemory(device, indices.memory, nullptr);
		}
	}

	/**
	* Loads a 3D model from a file into Vulkan buffers
	*
	* @param device Pointer to the Vulkan device used to generated the vertex and index buffers on
	* @param filename File to load (must be a model format supported by ASSIMP)
	* @param layout Vertex layout components (position, normals, tangents, etc.)
	* @param createInfo MeshCreateInfo structure for load time settings like scale, center, etc.
	* @param copyQueue Queue used for the memory staging copy commands (must support transfer)
	*/
	bool loadFromFile(const std::string& filename, VertexLayout layout, ModelCreateInfo* createInfo, VulkanDevice* device, VkQueue copyQueue) {
		this->device = device->logicalDevice;

		Assimp::Importer Importer;
		const aiScene* pScene;

		// Load file
		pScene = Importer.ReadFile(filename.c_str(), defaultFlags);
		if (!pScene) {
			std::string error = Importer.GetErrorString();
			tools::exitFatal(error + "\n\nThe file may be part of the additional asset pack.\n\nRun \"download_assets.py\" in the repository root to download the latest version.", -1);
		}

		if (pScene) {
			parts.clear();
			parts.resize(pScene->mNumMeshes);

			glm::vec3 scale(1.0f);
			glm::vec2 uvscale(1.0f);
			glm::vec3 center(0.0f);
			if (createInfo) {
				scale = createInfo->scale;
				uvscale = createInfo->uvscale;
				center = createInfo->center;
			}

			std::vector<float> vertexBuffer;
			std::vector<uint32_t> indexBuffer;

			vertexCount = 0;
			indexCount = 0;

			// Load meshes
			for (unsigned int i = 0; i < pScene->mNumMeshes; i++) {
				const aiMesh* paiMesh = pScene->mMeshes[i];

				parts[i] = {};
				parts[i].vertexBase = vertexCount;
				parts[i].indexBase = indexCount;

				vertexCount += pScene->mMeshes[i]->mNumVertices;

				aiColor3D pColor(0.f, 0.f, 0.f);
				pScene->mMaterials[paiMesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, pColor);

				const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

				for (unsigned int j = 0; j < paiMesh->mNumVertices; j++) {
					const aiVector3D* pPos = &(paiMesh->mVertices[j]);
					const aiVector3D* pNormal = &(paiMesh->mNormals[j]);
					const aiVector3D* pTexCoord = (paiMesh->HasTextureCoords(0)) ? &(paiMesh->mTextureCoords[0][j]) : &Zero3D;
					const aiVector3D* pTangent = (paiMesh->HasTangentsAndBitangents()) ? &(paiMesh->mTangents[j]) : &Zero3D;
					const aiVector3D* pBiTangent = (paiMesh->HasTangentsAndBitangents()) ? &(paiMesh->mBitangents[j]) : &Zero3D;

					for (auto& component : layout.components) {
						switch (component) {
						case VERTEX_COMPONENT_POSITION:
							vertexBuffer.push_back(pPos->x * scale.x + center.x);
							vertexBuffer.push_back(-pPos->y * scale.y + center.y);
							vertexBuffer.push_back(pPos->z * scale.z + center.z);
							break;
						case VERTEX_COMPONENT_NORMAL:
							vertexBuffer.push_back(pNormal->x);
							vertexBuffer.push_back(-pNormal->y);
							vertexBuffer.push_back(pNormal->z);
							break;
						case VERTEX_COMPONENT_UV:
							vertexBuffer.push_back(pTexCoord->x * uvscale.s);
							vertexBuffer.push_back(pTexCoord->y * uvscale.t);
							break;
						case VERTEX_COMPONENT_COLOR:
							vertexBuffer.push_back(pColor.r);
							vertexBuffer.push_back(pColor.g);
							vertexBuffer.push_back(pColor.b);
							break;
						case VERTEX_COMPONENT_TANGENT:
							vertexBuffer.push_back(pTangent->x);
							vertexBuffer.push_back(pTangent->y);
							vertexBuffer.push_back(pTangent->z);
							break;
						case VERTEX_COMPONENT_BITANGENT:
							vertexBuffer.push_back(pBiTangent->x);
							vertexBuffer.push_back(pBiTangent->y);
							vertexBuffer.push_back(pBiTangent->z);
							break;
							// Dummy components for padding
						case VERTEX_COMPONENT_DUMMY_FLOAT:
							vertexBuffer.push_back(0.0f);
							break;
						case VERTEX_COMPONENT_DUMMY_VEC4:
							vertexBuffer.push_back(0.0f);
							vertexBuffer.push_back(0.0f);
							vertexBuffer.push_back(0.0f);
							vertexBuffer.push_back(0.0f);
							break;
						};
					}

					dim.max.x = fmax(pPos->x, dim.max.x);
					dim.max.y = fmax(pPos->y, dim.max.y);
					dim.max.z = fmax(pPos->z, dim.max.z);

					dim.min.x = fmin(pPos->x, dim.min.x);
					dim.min.y = fmin(pPos->y, dim.min.y);
					dim.min.z = fmin(pPos->z, dim.min.z);
				}

				dim.size = dim.max - dim.min;

				parts[i].vertexCount = paiMesh->mNumVertices;

				uint32_t indexBase = static_cast<uint32_t>(indexBuffer.size());
				for (unsigned int j = 0; j < paiMesh->mNumFaces; j++) {
					const aiFace& Face = paiMesh->mFaces[j];
					if (Face.mNumIndices != 3)
						continue;
					indexBuffer.push_back(indexBase + Face.mIndices[0]);
					indexBuffer.push_back(indexBase + Face.mIndices[1]);
					indexBuffer.push_back(indexBase + Face.mIndices[2]);
					parts[i].indexCount += 3;
					indexCount += 3;
				}
			}


			uint32_t vBufferSize = static_cast<uint32_t>(vertexBuffer.size()) * sizeof(float);
			uint32_t iBufferSize = static_cast<uint32_t>(indexBuffer.size()) * sizeof(uint32_t);

			// Use staging buffer to move vertex and index buffer to device local memory
			// Create staging buffers
			Buffer vertexStaging, indexStaging;

			// Vertex buffer
			tools::VK_VERIFY_SUCCESS(device->createBuffer(
				VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				&vertexStaging,
				vBufferSize,
				vertexBuffer.data()));

			// Index buffer
			tools::VK_VERIFY_SUCCESS(device->createBuffer(
				VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				&indexStaging,
				iBufferSize,
				indexBuffer.data()));

			// Create device local target buffers
			// Vertex buffer
			tools::VK_VERIFY_SUCCESS(device->createBuffer(
				VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | createInfo->memoryPropertyFlags,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				&vertices,
				vBufferSize));

			// Index buffer
			tools::VK_VERIFY_SUCCESS(device->createBuffer(
				VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | createInfo->memoryPropertyFlags,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				&indices,
				iBufferSize));

			// Copy from staging buffers
			VkCommandBuffer copyCmd = device->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

			VkBufferCopy copyRegion{};

			copyRegion.size = vertices.size;
			vkCmdCopyBuffer(copyCmd, vertexStaging.buffer, vertices.buffer, 1, &copyRegion);

			copyRegion.size = indices.size;
			vkCmdCopyBuffer(copyCmd, indexStaging.buffer, indices.buffer, 1, &copyRegion);

			device->flushCommandBuffer(copyCmd, copyQueue);

			// Destroy staging resources
			vkDestroyBuffer(device->logicalDevice, vertexStaging.buffer, nullptr);
			vkFreeMemory(device->logicalDevice, vertexStaging.memory, nullptr);
			vkDestroyBuffer(device->logicalDevice, indexStaging.buffer, nullptr);
			vkFreeMemory(device->logicalDevice, indexStaging.memory, nullptr);

			return true;
		} else {
			printf("Error parsing '%s': '%s'\n", filename.c_str(), Importer.GetErrorString());
			return false;
		}
	};

	/**
	* Loads a 3D model from a file into Vulkan buffers
	*
	* @param device Pointer to the Vulkan device used to generated the vertex and index buffers on
	* @param filename File to load (must be a model format supported by ASSIMP)
	* @param layout Vertex layout components (position, normals, tangents, etc.)
	* @param scale Load time scene scale
	* @param copyQueue Queue used for the memory staging copy commands (must support transfer)
	*/
	bool loadFromFile(const std::string& filename, VertexLayout layout, float scale, VulkanDevice* device, VkQueue copyQueue) {
		ModelCreateInfo modelCreateInfo(scale, 1.0f, 0.0f);
		return loadFromFile(filename, layout, &modelCreateInfo, device, copyQueue);
	}
};

class UIOverlay {
public:
	VulkanDevice* device;
	VkQueue queue;

	VkSampleCountFlagBits rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	uint32_t subpass = 0;

	Buffer vertexBuffer;
	Buffer indexBuffer;
	int32_t vertexCount = 0;
	int32_t indexCount = 0;

	std::vector<VkPipelineShaderStageCreateInfo> shaders;

	VkDescriptorPool descriptorPool;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSet descriptorSet;
	VkPipelineLayout pipelineLayout;
	VkPipeline pipeline;

	VkDeviceMemory fontMemory = VK_NULL_HANDLE;
	VkImage fontImage = VK_NULL_HANDLE;
	VkImageView fontView = VK_NULL_HANDLE;
	VkSampler sampler;

	struct PushConstBlock {
		glm::vec2 scale;
		glm::vec2 translate;
	} pushConstBlock;

	bool visible = true;
	bool updated = false;
	float scale = 1.0f;

	UIOverlay();
	~UIOverlay();

	void preparePipeline(const VkPipelineCache pipelineCache, const VkRenderPass renderPass);
	void prepareResources();

	bool update();
	void draw(const VkCommandBuffer commandBuffer);
	void resize(uint32_t width, uint32_t height);

	void freeResources();

	bool header(const char* caption);
	bool checkBox(const char* caption, bool* value);
	bool checkBox(const char* caption, int32_t* value);
	bool inputFloat(const char* caption, float* value, float step, uint32_t precision);
	bool sliderFloat(const char* caption, float* value, float min, float max);
	bool sliderInt(const char* caption, int32_t* value, int32_t min, int32_t max);
	bool comboBox(const char* caption, int32_t* itemindex, std::vector<std::string> items);
	bool button(const char* caption);
	void text(const char* formatstr, ...);
};

UIOverlay::UIOverlay() {
	// Init ImGui
	ImGui::CreateContext();
	// Color scheme
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.0f, 0.0f, 0.0f, 0.1f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.8f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.1f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.2f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.0f, 0.0f, 0.0f, 0.4f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.0f, 0.0f, 0.6f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.0f, 0.0f, 0.8f);
	// Dimensions
	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = scale;
}

UIOverlay::~UIOverlay() { }

void UIOverlay::prepareResources() {
	ImGuiIO& io = ImGui::GetIO();

	unsigned char* fontData;
	int texWidth, texHeight;
	io.Fonts->AddFontFromFileTTF("./../data/Roboto-Medium.ttf", 16.0f);
	io.Fonts->GetTexDataAsRGBA32(&fontData, &texWidth, &texHeight);
	VkDeviceSize uploadSize = texWidth * texHeight * 4 * sizeof(char);

	VkImageCreateInfo imageInfo = initializers::imageCreateInfo();
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	imageInfo.extent.width = texWidth;
	imageInfo.extent.height = texHeight;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	tools::VK_VERIFY_SUCCESS(vkCreateImage(device->logicalDevice, &imageInfo, nullptr, &fontImage));
	VkMemoryRequirements memReqs;
	vkGetImageMemoryRequirements(device->logicalDevice, fontImage, &memReqs);
	VkMemoryAllocateInfo memAllocInfo = initializers::memoryAllocateInfo();
	memAllocInfo.allocationSize = memReqs.size;
	memAllocInfo.memoryTypeIndex = device->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device->logicalDevice, &memAllocInfo, nullptr, &fontMemory));
	tools::VK_VERIFY_SUCCESS(vkBindImageMemory(device->logicalDevice, fontImage, fontMemory, 0));

	// Image view
	VkImageViewCreateInfo viewInfo = initializers::imageViewCreateInfo();
	viewInfo.image = fontImage;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.layerCount = 1;
	tools::VK_VERIFY_SUCCESS(vkCreateImageView(device->logicalDevice, &viewInfo, nullptr, &fontView));

	// Staging buffers for font data upload
	Buffer stagingBuffer;

	tools::VK_VERIFY_SUCCESS(device->createBuffer(
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&stagingBuffer,
		uploadSize));

	stagingBuffer.map();
	memcpy(stagingBuffer.mapped, fontData, uploadSize);
	stagingBuffer.unmap();

	// Copy buffer data to font image
	VkCommandBuffer copyCmd = device->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

	// Prepare for transfer
	tools::setImageLayout(
		copyCmd,
		fontImage,
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_PIPELINE_STAGE_HOST_BIT,
		VK_PIPELINE_STAGE_TRANSFER_BIT);

	// Copy
	VkBufferImageCopy bufferCopyRegion = {};
	bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	bufferCopyRegion.imageSubresource.layerCount = 1;
	bufferCopyRegion.imageExtent.width = texWidth;
	bufferCopyRegion.imageExtent.height = texHeight;
	bufferCopyRegion.imageExtent.depth = 1;

	vkCmdCopyBufferToImage(
		copyCmd,
		stagingBuffer.buffer,
		fontImage,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		1,
		&bufferCopyRegion
	);

	// Prepare for shader read
	tools::setImageLayout(
		copyCmd,
		fontImage,
		VK_IMAGE_ASPECT_COLOR_BIT,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		VK_PIPELINE_STAGE_TRANSFER_BIT,
		VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

	device->flushCommandBuffer(copyCmd, queue, true);

	stagingBuffer.destroy();

	// Font texture Sampler
	VkSamplerCreateInfo samplerInfo = initializers::samplerCreateInfo();
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	tools::VK_VERIFY_SUCCESS(vkCreateSampler(device->logicalDevice, &samplerInfo, nullptr, &sampler));

	// Descriptor pool
	std::vector<VkDescriptorPoolSize> poolSizes = {
		initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1)
	};
	VkDescriptorPoolCreateInfo descriptorPoolInfo = initializers::descriptorPoolCreateInfo(poolSizes, 2);
	tools::VK_VERIFY_SUCCESS(vkCreateDescriptorPool(device->logicalDevice, &descriptorPoolInfo, nullptr, &descriptorPool));

	// Descriptor set layout
	std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
		initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 0),
	};
	VkDescriptorSetLayoutCreateInfo descriptorLayout = initializers::descriptorSetLayoutCreateInfo(setLayoutBindings);
	tools::VK_VERIFY_SUCCESS(vkCreateDescriptorSetLayout(device->logicalDevice, &descriptorLayout, nullptr, &descriptorSetLayout));

	// Descriptor set
	VkDescriptorSetAllocateInfo allocInfo = initializers::descriptorSetAllocateInfo(descriptorPool, &descriptorSetLayout, 1);
	tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device->logicalDevice, &allocInfo, &descriptorSet));
	VkDescriptorImageInfo fontDescriptor = initializers::descriptorImageInfo(
		sampler,
		fontView,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	);
	std::vector<VkWriteDescriptorSet> writeDescriptorSets = {
		initializers::writeDescriptorSet(descriptorSet, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0, &fontDescriptor)
	};
	vkUpdateDescriptorSets(device->logicalDevice, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);
}

/** Prepare a separate pipeline for the UI overlay rendering decoupled from the main application */
void UIOverlay::preparePipeline(const VkPipelineCache pipelineCache, const VkRenderPass renderPass) {
	// Pipeline layout
	// Push constants for UI rendering parameters
	VkPushConstantRange pushConstantRange = initializers::pushConstantRange(VK_SHADER_STAGE_VERTEX_BIT, sizeof(PushConstBlock), 0);
	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = initializers::pipelineLayoutCreateInfo(&descriptorSetLayout, 1);
	pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
	pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;
	tools::VK_VERIFY_SUCCESS(vkCreatePipelineLayout(device->logicalDevice, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

	// Setup graphics pipeline for UI rendering
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyState =
		initializers::pipelineInputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, VK_FALSE);

	VkPipelineRasterizationStateCreateInfo rasterizationState =
		initializers::pipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_COUNTER_CLOCKWISE);

	// Enable blending
	VkPipelineColorBlendAttachmentState blendAttachmentState{};
	blendAttachmentState.blendEnable = VK_TRUE;
	blendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	blendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	blendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	blendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
	blendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	blendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	blendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlendState =
		initializers::pipelineColorBlendStateCreateInfo(1, &blendAttachmentState);

	VkPipelineDepthStencilStateCreateInfo depthStencilState =
		initializers::pipelineDepthStencilStateCreateInfo(VK_FALSE, VK_FALSE, VK_COMPARE_OP_ALWAYS);

	VkPipelineViewportStateCreateInfo viewportState =
		initializers::pipelineViewportStateCreateInfo(1, 1, 0);

	VkPipelineMultisampleStateCreateInfo multisampleState =
		initializers::pipelineMultisampleStateCreateInfo(rasterizationSamples);

	std::vector<VkDynamicState> dynamicStateEnables = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo dynamicState =
		initializers::pipelineDynamicStateCreateInfo(dynamicStateEnables);

	VkGraphicsPipelineCreateInfo pipelineCreateInfo = initializers::pipelineCreateInfo(pipelineLayout, renderPass);

	pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
	pipelineCreateInfo.pRasterizationState = &rasterizationState;
	pipelineCreateInfo.pColorBlendState = &colorBlendState;
	pipelineCreateInfo.pMultisampleState = &multisampleState;
	pipelineCreateInfo.pViewportState = &viewportState;
	pipelineCreateInfo.pDepthStencilState = &depthStencilState;
	pipelineCreateInfo.pDynamicState = &dynamicState;
	pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaders.size());
	pipelineCreateInfo.pStages = shaders.data();
	pipelineCreateInfo.subpass = subpass;

	// Vertex bindings an attributes based on ImGui vertex definition
	std::vector<VkVertexInputBindingDescription> vertexInputBindings = {
		initializers::vertexInputBindingDescription(0, sizeof(ImDrawVert), VK_VERTEX_INPUT_RATE_VERTEX),
	};
	std::vector<VkVertexInputAttributeDescription> vertexInputAttributes = {
		initializers::vertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(ImDrawVert, pos)),	// Location 0: Position
		initializers::vertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(ImDrawVert, uv)),	// Location 1: UV
		initializers::vertexInputAttributeDescription(0, 2, VK_FORMAT_R8G8B8A8_UNORM, offsetof(ImDrawVert, col)),	// Location 0: Color
	};
	VkPipelineVertexInputStateCreateInfo vertexInputState = initializers::pipelineVertexInputStateCreateInfo();
	vertexInputState.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindings.size());
	vertexInputState.pVertexBindingDescriptions = vertexInputBindings.data();
	vertexInputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributes.size());
	vertexInputState.pVertexAttributeDescriptions = vertexInputAttributes.data();

	pipelineCreateInfo.pVertexInputState = &vertexInputState;

	tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device->logicalDevice, pipelineCache, 1, &pipelineCreateInfo, nullptr, &pipeline));
}

/** Update vertex and index buffer containing the imGui elements when required */
bool UIOverlay::update() {
	ImDrawData* imDrawData = ImGui::GetDrawData();
	bool updateCmdBuffers = false;

	if (!imDrawData) { return false; };

	// Note: Alignment is done inside buffer creation
	VkDeviceSize vertexBufferSize = imDrawData->TotalVtxCount * sizeof(ImDrawVert);
	VkDeviceSize indexBufferSize = imDrawData->TotalIdxCount * sizeof(ImDrawIdx);

	// Update buffers only if vertex or index count has been changed compared to current buffer size
	if ((vertexBufferSize == 0) || (indexBufferSize == 0)) {
		return false;
	}

	// Vertex buffer
	if ((vertexBuffer.buffer == VK_NULL_HANDLE) || (vertexCount != imDrawData->TotalVtxCount)) {
		vertexBuffer.unmap();
		vertexBuffer.destroy();
		tools::VK_VERIFY_SUCCESS(device->createBuffer(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &vertexBuffer, vertexBufferSize));
		vertexCount = imDrawData->TotalVtxCount;
		vertexBuffer.unmap();
		vertexBuffer.map();
		updateCmdBuffers = true;
	}

	// Index buffer
	VkDeviceSize indexSize = imDrawData->TotalIdxCount * sizeof(ImDrawIdx);
	if ((indexBuffer.buffer == VK_NULL_HANDLE) || (indexCount < imDrawData->TotalIdxCount)) {
		indexBuffer.unmap();
		indexBuffer.destroy();
		tools::VK_VERIFY_SUCCESS(device->createBuffer(VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &indexBuffer, indexBufferSize));
		indexCount = imDrawData->TotalIdxCount;
		indexBuffer.map();
		updateCmdBuffers = true;
	}

	// Upload data
	ImDrawVert* vtxDst = (ImDrawVert*)vertexBuffer.mapped;
	ImDrawIdx* idxDst = (ImDrawIdx*)indexBuffer.mapped;

	for (int n = 0; n < imDrawData->CmdListsCount; n++) {
		const ImDrawList* cmd_list = imDrawData->CmdLists[n];
		memcpy(vtxDst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
		memcpy(idxDst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
		vtxDst += cmd_list->VtxBuffer.Size;
		idxDst += cmd_list->IdxBuffer.Size;
	}

	// Flush to make writes visible to GPU
	vertexBuffer.flush();
	indexBuffer.flush();

	return updateCmdBuffers;
}

void UIOverlay::draw(const VkCommandBuffer commandBuffer) {
	ImDrawData* imDrawData = ImGui::GetDrawData();
	int32_t vertexOffset = 0;
	int32_t indexOffset = 0;

	if ((!imDrawData) || (imDrawData->CmdListsCount == 0)) {
		return;
	}

	ImGuiIO& io = ImGui::GetIO();

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, NULL);

	pushConstBlock.scale = glm::vec2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
	pushConstBlock.translate = glm::vec2(-1.0f);
	vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(PushConstBlock), &pushConstBlock);

	VkDeviceSize offsets[1] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer.buffer, offsets);
	vkCmdBindIndexBuffer(commandBuffer, indexBuffer.buffer, 0, VK_INDEX_TYPE_UINT16);

	for (int32_t i = 0; i < imDrawData->CmdListsCount; i++) {
		const ImDrawList* cmd_list = imDrawData->CmdLists[i];
		for (int32_t j = 0; j < cmd_list->CmdBuffer.Size; j++) {
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[j];
			VkRect2D scissorRect;
			scissorRect.offset.x = std::max((int32_t)(pcmd->ClipRect.x), 0);
			scissorRect.offset.y = std::max((int32_t)(pcmd->ClipRect.y), 0);
			scissorRect.extent.width = (uint32_t)(pcmd->ClipRect.z - pcmd->ClipRect.x);
			scissorRect.extent.height = (uint32_t)(pcmd->ClipRect.w - pcmd->ClipRect.y);
			vkCmdSetScissor(commandBuffer, 0, 1, &scissorRect);
			vkCmdDrawIndexed(commandBuffer, pcmd->ElemCount, 1, indexOffset, vertexOffset, 0);
			indexOffset += pcmd->ElemCount;
		}
		vertexOffset += cmd_list->VtxBuffer.Size;
	}
}

void UIOverlay::resize(uint32_t width, uint32_t height) {
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)(width), (float)(height));
}

void UIOverlay::freeResources() {
	ImGui::DestroyContext();
	vertexBuffer.destroy();
	indexBuffer.destroy();
	vkDestroyImageView(device->logicalDevice, fontView, nullptr);
	vkDestroyImage(device->logicalDevice, fontImage, nullptr);
	vkFreeMemory(device->logicalDevice, fontMemory, nullptr);
	vkDestroySampler(device->logicalDevice, sampler, nullptr);
	vkDestroyDescriptorSetLayout(device->logicalDevice, descriptorSetLayout, nullptr);
	vkDestroyDescriptorPool(device->logicalDevice, descriptorPool, nullptr);
	vkDestroyPipelineLayout(device->logicalDevice, pipelineLayout, nullptr);
	vkDestroyPipeline(device->logicalDevice, pipeline, nullptr);
}

bool UIOverlay::header(const char* caption) {
	return ImGui::CollapsingHeader(caption, ImGuiTreeNodeFlags_DefaultOpen);
}

bool UIOverlay::checkBox(const char* caption, bool* value) {
	bool res = ImGui::Checkbox(caption, value);
	if (res) { updated = true; };
	return res;
}

bool UIOverlay::checkBox(const char* caption, int32_t* value) {
	bool val = (*value == 1);
	bool res = ImGui::Checkbox(caption, &val);
	*value = val;
	if (res) { updated = true; };
	return res;
}

bool UIOverlay::inputFloat(const char* caption, float* value, float step, uint32_t precision) {
	bool res = ImGui::InputFloat(caption, value, step, step * 10.0f, precision);
	if (res) { updated = true; };
	return res;
}

bool UIOverlay::sliderFloat(const char* caption, float* value, float min, float max) {
	bool res = ImGui::SliderFloat(caption, value, min, max);
	if (res) { updated = true; };
	return res;
}

bool UIOverlay::sliderInt(const char* caption, int32_t* value, int32_t min, int32_t max) {
	bool res = ImGui::SliderInt(caption, value, min, max);
	if (res) { updated = true; };
	return res;
}

bool UIOverlay::comboBox(const char* caption, int32_t* itemindex, std::vector<std::string> items) {
	if (items.empty()) {
		return false;
	}
	std::vector<const char*> charitems;
	charitems.reserve(items.size());
	for (size_t i = 0; i < items.size(); i++) {
		charitems.push_back(items[i].c_str());
	}
	uint32_t itemCount = static_cast<uint32_t>(charitems.size());
	bool res = ImGui::Combo(caption, itemindex, &charitems[0], itemCount, itemCount);
	if (res) { updated = true; };
	return res;
}

bool UIOverlay::button(const char* caption) {
	bool res = ImGui::Button(caption, ImVec2(0, 0));
	if (res) { updated = true; };
	return res;
}

void UIOverlay::text(const char* formatstr, ...) {
	va_list args;
	va_start(args, formatstr);
	ImGui::TextV(formatstr, args);
	va_end(args);
}

class Benchmark {
private:
	FILE* stream;
	VkPhysicalDeviceProperties deviceProps;
public:
	bool active = false;
	bool outputFrameTimes = false;
	uint32_t warmup = 1;
	uint32_t duration = 10;
	std::vector<double> frameTimes;
	std::string filename = "";

	double runtime = 0.0;
	uint32_t frameCount = 0;

	void run(std::function<void()> renderFunc, VkPhysicalDeviceProperties deviceProps) {
		active = true;
		this->deviceProps = deviceProps;
#if defined(_WIN32)
		AttachConsole(ATTACH_PARENT_PROCESS);
		freopen_s(&stream, "CONOUT$", "w+", stdout);
		freopen_s(&stream, "CONOUT$", "w+", stderr);
#endif
		std::cout << std::fixed << std::setprecision(3);

		// Warm up phase to get more stable frame rates
		{
			double tMeasured = 0.0;
			while (tMeasured < (warmup * 1000)) {
				auto tStart = std::chrono::high_resolution_clock::now();
				renderFunc();
				auto tDiff = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - tStart).count();
				tMeasured += tDiff;
			};
		}

		// Benchmark phase
		{
			while (runtime < (duration * 1000.0)) {
				auto tStart = std::chrono::high_resolution_clock::now();
				renderFunc();
				auto tDiff = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - tStart).count();
				runtime += tDiff;
				frameTimes.push_back(tDiff);
				frameCount++;
			};
			std::cout << "Benchmark finished" << std::endl;
			std::cout << "device : " << deviceProps.deviceName << " (driver version: " << deviceProps.driverVersion << ")" << std::endl;
			std::cout << "runtime: " << (runtime / 1000.0) << std::endl;
			std::cout << "frames : " << frameCount << std::endl;
			std::cout << "fps    : " << frameCount / (runtime / 1000.0) << std::endl;
		}
	}

	void saveResults() {
		std::ofstream result(filename, std::ios::out);
		if (result.is_open()) {
			result << std::fixed << std::setprecision(4);

			result << "device,driverversion,duration (ms),frames,fps" << std::endl;
			result << deviceProps.deviceName << "," << deviceProps.driverVersion << "," << runtime << "," << frameCount << "," << frameCount / (runtime / 1000.0) << std::endl;

			if (outputFrameTimes) {
				result << std::endl << "frame,ms" << std::endl;
				for (size_t i = 0; i < frameTimes.size(); i++) {
					result << i << "," << frameTimes[i] << std::endl;
				}
				double tMin = *std::min_element(frameTimes.begin(), frameTimes.end());
				double tMax = *std::max_element(frameTimes.begin(), frameTimes.end());
				double tAvg = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / (double)frameTimes.size();
				std::cout << "best   : " << (1000.0 / tMin) << " fps (" << tMin << " ms)" << std::endl;
				std::cout << "worst  : " << (1000.0 / tMax) << " fps (" << tMax << " ms)" << std::endl;
				std::cout << "avg    : " << (1000.0 / tAvg) << " fps (" << tAvg << " ms)" << std::endl;
				std::cout << std::endl;
			}

			result.flush();
#if defined(_WIN32)
			FreeConsole();
#endif
		}
	}
};








/**

VULKAN RENDERER SEGMENT

**/


class VulkanRenderer : public Renderer {
private:
	std::string getWindowTitle();
	bool viewUpdated = false;
	uint32_t destWidth;
	uint32_t destHeight;
	bool resizing = false;
	void windowResize();
	void handleMouseMove(int32_t x, int32_t y);
protected:
	uint32_t frameCounter = 0; // the frames generated over 1 second intervals, reset every second
	uint32_t frameCount = 0; // useful for benchmarking the number of frames generated
	uint32_t lastFPS = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTimestamp;
	std::chrono::time_point<std::chrono::steady_clock> resetTime = std::chrono::high_resolution_clock::now();
	std::vector<KeyframeData> keyframes;
	float frameTime; // the time in seconds between the last frame and the current one
	float animation_alpha; //used for keyframe blending

	bool paused = false;
	// loops between 0 and 1.
	float timer = 0.0f;
	// a modifier for the timer above
	float timerSpeed = 1.0f; // 1.0f means real time, 0.5 means half as fast, etc
	double frameTimer = 1.0f; // time since last frame was generated, same as frameTime

	// Cloth Stuff
	uint32_t sceneSetup = 0;
	uint32_t readSet = 0;
	uint32_t indexCount;
	bool simulateWind = false;

	Texture2D textureCloth;
	Model modelSphere;

	// Structs useful for containing cloth simulation resources, and the buffer object associated
	struct {
		VkDescriptorSetLayout descriptorSetLayout;
		VkDescriptorSet descriptorSet;
		VkPipelineLayout pipelineLayout;
		struct Pipelines {
			VkPipeline cloth;
			VkPipeline sphere;
		} pipelines;
		Buffer indices;
		Buffer uniformBuffer;
		struct graphicsUBO {
			glm::mat4 projection;
			glm::mat4 view;
			glm::vec4 lightPos = glm::vec4(-1.0f, 2.0f, -1.0f, 1.0f);
		} ubo;
	} graphics;
	struct {
		struct StorageBuffers {
			Buffer input;
			Buffer output;
		} storageBuffers;
		Buffer uniformBuffer;
		VkQueue queue;
		VkCommandPool commandPool;
		std::array<VkCommandBuffer, 2> commandBuffers;
		VkFence fence;
		VkDescriptorSetLayout descriptorSetLayout;
		std::array<VkDescriptorSet, 2> descriptorSets;
		VkPipelineLayout pipelineLayout;
		VkPipeline pipeline;
		struct computeUBO {
			float deltaT = 0.0f;
			float particleMass = 0.1f;
			float springStiffness = 2000.0f;
			float damping = 0.25f;
			float restDistH;
			float restDistV;
			float restDistD;
			float sphereRadius = 0.5f;
			glm::vec4 spherePos = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			glm::vec4 gravity = glm::vec4(0.0f, 9.8f, 0.0f, 0.0f);
			glm::ivec2 particleCount;
		} ubo;
	} compute;

	//Particle for the cloth simulation.
	struct Particle {
		glm::vec4 pos;
		glm::vec4 vel;
		glm::vec4 uv;
		glm::vec4 normal;
		float pinned;
		glm::vec3 _pad0;
	};

	struct Cloth {
		glm::uvec2 gridsize = glm::uvec2(60, 60); // 60 by 60 vertices in the cloth
		glm::vec2 size = glm::vec2(2.5f, 2.5f); // actual size in world space
	} cloth;

	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	VkPhysicalDeviceMemoryProperties deviceMemoryProperties;

	VkPhysicalDeviceFeatures enabledFeatures{};
	std::vector<const char*> enabledDeviceExtensions;
	std::vector<const char*> enabledInstanceExtensions;

	void* deviceCreatepNextChain = nullptr;
	VkDevice device;
	VkQueue queue;
	VkFormat depthFormat;
	VkCommandPool cmdPool;
	VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	VkSubmitInfo submitInfo;
	std::vector<VkCommandBuffer> drawCmdBuffers;
	VkRenderPass renderPass;
	std::vector<VkFramebuffer>frameBuffers;
	uint32_t currentBuffer = 0;
	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
	std::vector<VkShaderModule> shaderModules;
	VkPipelineCache pipelineCache;
	
	VulkanSwapChain swapChain;
	struct {
		VkSemaphore presentComplete;
		VkSemaphore renderComplete;
	} semaphores;
	std::vector<VkFence> waitFences;

	// For the Billiards Animation
	void UpdateModelsList();
public:
	static std::vector<const char*> args;

	bool prepared = false;
	uint32_t width = 1280;
	uint32_t height = 720;

	UIOverlay overlay;

	const std::string getAssetPath();

	Benchmark benchmark;

	VulkanDevice* vulkanDevice;

	VertexLayout vertexLayout = VertexLayout({
		VERTEX_COMPONENT_POSITION,
		VERTEX_COMPONENT_NORMAL,
		VERTEX_COMPONENT_COLOR,
		});

	struct {
		Model ufo;
		Model skysphere;
	} models;
	std::vector<Model> models_list;

	struct {
		glm::mat4 projection;
		glm::mat4 view;
	} matrices;

	struct {
		VkPipeline phong;
		VkPipeline starsphere;
	} pipelines;

	VkPipelineLayout pipelineLayout;

	VkCommandBuffer primaryCommandBuffer;

	// Secondary scene command buffers used to store backgdrop and user interface
	struct SecondaryCommandBuffers {
		VkCommandBuffer background;
		VkCommandBuffer ui;
	} secondaryCommandBuffers;

	struct ThreadPushConstantBlock {
		glm::mat4 mvp;
		glm::vec3 color;
	};

	struct ObjectData {
		glm::mat4 model;
		glm::vec3 pos;
		glm::vec3 rotation;
		float rotationDir;
		float rotationSpeed;
		float scale;
		float deltaT;
		float stateT = 0;
		bool visible = true;
	};

	// Threading data
	struct ThreadData {
		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffer;
		std::vector<ThreadPushConstantBlock> pushConstBlock;
		std::vector<ObjectData> objectData;
	};
	std::vector<ThreadData> threadData;
	ThreadPool threadPool;
	uint32_t numObjectsPerThread;
	uint32_t numThreads;

	VkFence renderFence = {};

	Frustum frustum;
	float objectSphereDim;

	std::default_random_engine rndEngine;

	struct Settings {
		bool validation = false;
		bool fullscreen = false;
		bool vsync = false;
		bool overlay = false;
	} settings;

	VkClearColorValue defaultClearColor = { { 0.025f, 0.025f, 0.025f, 1.0f } };
	bool displaySkybox = true;

	Camera camera;
	// current "camera zoom"
	float zoom = 0;

	glm::vec3 rotation = glm::vec3();
	glm::vec3 cameraPos = glm::vec3();
	glm::vec2 mousePos;
	// mouse rotation speed
	float rotationSpeed = 1.0f;
	float zoomSpeed = 1.0f;

	std::string title = "Polyform Engine";
	std::string name = "PolyformEngine";
	uint32_t apiVersion = VK_API_VERSION_1_0;

	struct {
		VkImage image;
		VkDeviceMemory mem;
		VkImageView view;
	} depthStencil;

	struct {
		glm::vec2 axisLeft = glm::vec2(0.0f);
		glm::vec2 axisRight = glm::vec2(0.0f);
	} gamePadState;

	struct {
		bool left = false;
		bool right = false;
		bool middle = false;
	} mouseButtons;

	VulkanRenderer(bool enableValidation = false);
	virtual ~VulkanRenderer();

	// OS specific 
#if defined(_WIN32)
	HWND window;
	HINSTANCE windowInstance; 
	void setupConsole(std::string title);
	void setupDPIAwareness();
	HWND setupWindow(HINSTANCE hinstance, WNDPROC wndproc);
	void handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	void* setupWindow(void* view);
	void* view;
#endif


	// Does the hard work of creating the Vulkan instance.
	bool initVulkan(); 
	virtual VkResult createInstance(bool enableValidation);

	virtual void render() = 0;
	virtual void viewChanged();

	// Hardware
	virtual void keyPressed(uint32_t);
	virtual void mouseMoved(double x, double y, bool& handled);
	virtual void windowResized();

	void createSynchronizationPrimitives();

	void createCommandPool();

	virtual void setupDepthStencil();
	virtual void setupFrameBuffer();
	virtual void setupRenderPass();

	virtual void getEnabledFeatures();

	// Swap Chain
	void initSwapchain();
	void setupSwapChain();

	// Command Buffer
	virtual void buildCommandBuffers();
	virtual void buildComputeCommandBuffer();
	bool checkCommandBuffers();
	void createCommandBuffers();
	void destroyCommandBuffers();
	VkCommandBuffer createCommandBuffer(VkCommandBufferLevel level, bool begin);
	void flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, bool free);

	void createPipelineCache();

	virtual void prepare();

	VkPipelineShaderStageCreateInfo loadShader(std::string fileName, VkShaderStageFlagBits stage);

	void renderLoop();

	void renderFrame();

	void updateOverlay();
	void drawUI(const VkCommandBuffer commandBuffer);

	// Prepare the frame for workload submission
	void prepareFrame();
	void submitFrame();

	virtual void OnUpdateUIOverlay(UIOverlay* overlay);

	float rnd(float range) {
		std::uniform_real_distribution<float> rndDist(0.0f, range);
		return rndDist(rndEngine);
	}

	float rnd(float start, float end) {
		std::uniform_real_distribution<float> rndDist(start, end);
		return rndDist(rndEngine);
	}
};

std::vector<const char*> VulkanRenderer::args;

VkResult VulkanRenderer::createInstance(bool enableValidation) {
	this->settings.validation = enableValidation;

	// Validation can also be forced via a define
#if defined(_VALIDATION)
	this->settings.validation = true;
#endif	

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = name.c_str();
	appInfo.pEngineName = name.c_str();
	appInfo.apiVersion = apiVersion;

	std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };

	// Enable surface extensions depending on os
#if defined(_WIN32)
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	instanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#endif

	if (enabledInstanceExtensions.size() > 0) {
		for (auto enabledExtension : enabledInstanceExtensions) {
			instanceExtensions.push_back(enabledExtension);
		}
	}

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pNext = NULL;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	if (instanceExtensions.size() > 0)
	{
		if (settings.validation)
		{
			instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}
		instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	}
	if (settings.validation)
	{
		instanceCreateInfo.enabledLayerCount = debug::validationLayerCount;
		instanceCreateInfo.ppEnabledLayerNames = debug::validationLayerNames;
	}
	return vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
}

std::string VulkanRenderer::getWindowTitle()
{
	std::string device(deviceProperties.deviceName);
	std::string windowTitle;
	windowTitle = title + " - " + device;
	if (!settings.overlay) {
		windowTitle += " - " + std::to_string(frameCounter) + " fps";
	}
	return windowTitle;
}

#if !defined(VK_USE_PLATFORM_MACOS_MVK)
const std::string VulkanRenderer::getAssetPath() {
	return "C:/Users/Colin/Desktop/Rendering/VKRT/env/";
}
#endif

bool VulkanRenderer::checkCommandBuffers() {
	for (VkCommandBuffer& cmdBuffer : drawCmdBuffers) {
		if (cmdBuffer == VK_NULL_HANDLE) {
			return false;
		}
	}
	return true;
}

void VulkanRenderer::createCommandBuffers() {
	// Create one command buffer for each swap chain image and reuse for rendering
	drawCmdBuffers.resize(swapChain.imageCount);

	VkCommandBufferAllocateInfo cmdBufAllocateInfo =
		initializers::commandBufferAllocateInfo(
			cmdPool,
			VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			static_cast<uint32_t>(drawCmdBuffers.size()));

	tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, drawCmdBuffers.data()));
}

void VulkanRenderer::destroyCommandBuffers() {
	vkFreeCommandBuffers(device, cmdPool, static_cast<uint32_t>(drawCmdBuffers.size()), drawCmdBuffers.data());
}

VkCommandBuffer VulkanRenderer::createCommandBuffer(VkCommandBufferLevel level, bool begin) {
	VkCommandBuffer cmdBuffer;

	VkCommandBufferAllocateInfo cmdBufAllocateInfo =
		initializers::commandBufferAllocateInfo(
			cmdPool,
			level,
			1);

	tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &cmdBuffer));

	// If requested, also start the new command buffer
	if (begin)
	{
		VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();
		tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(cmdBuffer, &cmdBufInfo));
	}

	return cmdBuffer;
}

void VulkanRenderer::flushCommandBuffer(VkCommandBuffer commandBuffer, VkQueue queue, bool free) {
	if (commandBuffer == VK_NULL_HANDLE) {
		return;
	}

	tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(commandBuffer));

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	tools::VK_VERIFY_SUCCESS(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));
	tools::VK_VERIFY_SUCCESS(vkQueueWaitIdle(queue));

	if (free) {
		vkFreeCommandBuffers(device, cmdPool, 1, &commandBuffer);
	}
}

void VulkanRenderer::createPipelineCache() {
	VkPipelineCacheCreateInfo pipelineCacheCreateInfo = {};
	pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
	tools::VK_VERIFY_SUCCESS(vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &pipelineCache));
}

void VulkanRenderer::prepare() {
	if (vulkanDevice->enableDebugMarkers) {
		debugmarker::setup(device);
	}
	initSwapchain();
	createCommandPool();
	setupSwapChain();
	createCommandBuffers();
	createSynchronizationPrimitives();
	setupDepthStencil();
	setupRenderPass();
	createPipelineCache();
	setupFrameBuffer();
	settings.overlay = settings.overlay && (!benchmark.active);
	if (settings.overlay) {
		overlay.device = vulkanDevice;
		overlay.queue = queue;
		overlay.shaders = {
			loadShader(getAssetPath() + "shaders/UI/uioverlay.vert.spv", VK_SHADER_STAGE_VERTEX_BIT),
			loadShader(getAssetPath() + "shaders/UI/uioverlay.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT)
		};
		overlay.prepareResources();
		overlay.preparePipeline(pipelineCache, renderPass);
	}
}

VkPipelineShaderStageCreateInfo VulkanRenderer::loadShader(std::string fileName, VkShaderStageFlagBits stage) {
	VkPipelineShaderStageCreateInfo shaderStage = {};
	shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStage.stage = stage;
	shaderStage.module = tools::loadShader(fileName.c_str(), device);
	shaderStage.pName = "main";
	assert(shaderStage.module != VK_NULL_HANDLE);
	shaderModules.push_back(shaderStage.module);
	return shaderStage;
}

void VulkanRenderer::renderFrame() {
	if (viewUpdated) {
		viewUpdated = false;
		viewChanged();
	}

	auto tEnd = std::chrono::high_resolution_clock::now();
	auto tDiff = std::chrono::duration<double, std::milli>(tEnd - lastTimestamp).count();
	frameTimer = tDiff / 1000.0f;
	frameTime = frameTimer;
	
	render();

	frameCounter++;
	camera.update(frameTimer);
	if (camera.moving()) {
		viewUpdated = true;
	}
	// Convert to clamped timer value
	if (!paused) {
		timer += timerSpeed * frameTimer;
		if (timer > 1.0) {
			timer -= 1.0f;
		}
	}

	float fpsTimer = std::chrono::duration<double, std::milli>(tEnd - lastTimestamp).count();
	if (fpsTimer > 1000.0f) {
		lastFPS = static_cast<uint32_t>((float)frameCounter * (1000.0f / fpsTimer));
#if defined(_WIN32)
		if (!settings.overlay) {
			std::string windowTitle = getWindowTitle();
			SetWindowText(window, windowTitle.c_str());
		}
#endif
		frameCounter = 0;
		lastTimestamp = tEnd; // THIS CAUSES STUTTERS?!?!
	}

	lastTimestamp = tEnd;

	updateOverlay();
}

void VulkanRenderer::UpdateModelsList() {
	bool any_moving = false;

	for (int i = 0; i < models_list.size(); i++) {
		if (models_list.at(i).moving && models_list.at(i).aniType == ANI_BILLIARDS) {
			any_moving = true;
		}
	}

	if (!any_moving && models_list.size() > 0) {
		//assume the cueball is first
		models_list.at(0).moving = true;
		models_list.at(0).translation_vector = 3.1f * glm::normalize(models_list.at(1).position - models_list.at(0).position + glm::vec3(0.1f, 0.2f, 0.0f));
	}

	//check walls?
	for (int i = 0; i < models_list.size(); i++) {
		if (models_list.at(i).aniType != ANI_BILLIARDS) {
			continue;
		}

		if (models_list.at(i).position.x < 0) {
			models_list.at(i).position.x = 0;
			models_list.at(i).translation_vector.x = 0.6f * abs(models_list.at(i).translation_vector.x);
		} else if (20 < models_list.at(i).position.x) {
			models_list.at(i).position.x = 20;
			models_list.at(i).translation_vector.x = -0.6f * abs(models_list.at(i).translation_vector.x);
		}

		if (models_list.at(i).position.y < 0) {
			models_list.at(i).position.y = 0;
			models_list.at(i).translation_vector.y = 0.6f * abs(models_list.at(i).translation_vector.y);
		} else if (20 < models_list.at(i).position.y) {
			models_list.at(i).position.y = 20;
			models_list.at(i).translation_vector.y = -0.6f * abs(models_list.at(i).translation_vector.y);
		}

		models_list.at(i).position.z = 0;
		models_list.at(i).translation_vector.z = 0.0f;
	}

	for (int i = 0; i < models_list.size(); i++) {
		if (models_list.at(i).aniType == ANI_BILLIARDS) {
			models_list.at(i).BilliardMovements(frameTime, models_list);
		}
	}
}

void VulkanRenderer::renderLoop() {
	if (benchmark.active) {
		benchmark.run([=] { render(); }, vulkanDevice->properties);
		vkDeviceWaitIdle(device);
		if (benchmark.filename != "") {
			benchmark.saveResults();
		}
		return;
	}

	destWidth = width;
	destHeight = height;
	lastTimestamp = std::chrono::high_resolution_clock::now();
//#if defined(_WIN32)
	MSG msg;
	bool quitMessageReceived = false;
	while (!quitMessageReceived) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) {
				quitMessageReceived = true;
				break;
			}
		}

		// per frame animations
		UpdateModelsList();

		if (!IsIconic(window)) {
			renderFrame();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
//#endif
	// Flush device to make sure all resources can be freed
	if (device != VK_NULL_HANDLE) {
		vkDeviceWaitIdle(device);
	}
}

void VulkanRenderer::updateOverlay() {
	if (!settings.overlay) return;

	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)width, (float)height);
	io.DeltaTime = frameTimer;

	io.MousePos = ImVec2(mousePos.x, mousePos.y);
	io.MouseDown[0] = mouseButtons.left;
	io.MouseDown[1] = mouseButtons.right;

	ImGui::NewFrame();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Rendering Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	//ImGui::TextUnformatted(title.c_str());
	//ImGui::TextUnformatted(deviceProperties.deviceName);
	//ImGui::Text("Alpha: %f", animation_alpha);
	//ImGui::Text("%.2f ms/frame (%.1d fps)", (1000.0f / lastFPS), lastFPS);
	ImGui::Text("%.2f ms frameTime", frameTime);

	ImGui::PushItemWidth(110.0f * overlay.scale);
	OnUpdateUIOverlay(&overlay);
	ImGui::PopItemWidth();

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::Render();

	if (overlay.update() || overlay.updated) {
		buildCommandBuffers();
		overlay.updated = false;
	}
}

void VulkanRenderer::drawUI(const VkCommandBuffer commandBuffer) {
	if (settings.overlay) {
		const VkViewport viewport = initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
		const VkRect2D scissor = initializers::rect2D(width, height, 0, 0);
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		overlay.draw(commandBuffer);
	}
}

void VulkanRenderer::prepareFrame() {
	// Acquire the next image from the swap chain
	VkResult err = swapChain.acquireNextImage(semaphores.presentComplete, &currentBuffer);
	// Recreate the swapchain if it's no longer compatible with the surface (OUT_OF_DATE) or no longer optimal for presentation (SUBOPTIMAL)
	if ((err == VK_ERROR_OUT_OF_DATE_KHR) || (err == VK_SUBOPTIMAL_KHR)) {
		windowResize();
	}
	else {
		tools::VK_VERIFY_SUCCESS(err);
	}
}

void VulkanRenderer::submitFrame() {
	VkResult queueRes = swapChain.queuePresent(queue, currentBuffer, semaphores.renderComplete);
	if (!((queueRes == VK_SUCCESS) || (queueRes == VK_SUBOPTIMAL_KHR))) {
		if (queueRes == VK_ERROR_OUT_OF_DATE_KHR) {
			// Swap chain is no longer compatible with the surface and needs to be recreated
			windowResize();
			return;
		}
		else {
			tools::VK_VERIFY_SUCCESS(queueRes);
		}
	}
	tools::VK_VERIFY_SUCCESS(vkQueueWaitIdle(queue));
}

VulkanRenderer::VulkanRenderer(bool enableValidation) {
	// Check for a valid asset path
	struct stat info;
	if (stat(getAssetPath().c_str(), &info) != 0) {
#if defined(_WIN32)
		std::string msg = "Could not locate asset path in \"" + getAssetPath() + "\" !";
		MessageBox(NULL, msg.c_str(), "Fatal error", MB_OK | MB_ICONERROR);
#else
		std::cerr << "Error: Could not find asset path in " << getAssetPath() << std::endl;
#endif
		exit(-1);
	}

	settings.validation = enableValidation;

	char* numConvPtr;

	// Parse command line arguments
	for (size_t i = 0; i < args.size(); i++) {
		if (args[i] == std::string("-validation")) {
			settings.validation = true;
		}
		if (args[i] == std::string("-vsync")) {
			settings.vsync = true;
		}
		if ((args[i] == std::string("-f")) || (args[i] == std::string("--fullscreen"))) {
			settings.fullscreen = true;
		}
		if ((args[i] == std::string("-w")) || (args[i] == std::string("-width"))) {
			uint32_t w = strtol(args[i + 1], &numConvPtr, 10);
			if (numConvPtr != args[i + 1]) { width = w; };
		}
		if ((args[i] == std::string("-h")) || (args[i] == std::string("-height"))) {
			uint32_t h = strtol(args[i + 1], &numConvPtr, 10);
			if (numConvPtr != args[i + 1]) { height = h; };
		}
		// Benchmark
		if ((args[i] == std::string("-b")) || (args[i] == std::string("--benchmark"))) {
			benchmark.active = true;
			tools::errorModeSilent = true;
		}
		// Warmup time (in seconds)
		if ((args[i] == std::string("-bw")) || (args[i] == std::string("--benchwarmup"))) {
			if (args.size() > i + 1) {
				uint32_t num = strtol(args[i + 1], &numConvPtr, 10);
				if (numConvPtr != args[i + 1]) {
					benchmark.warmup = num;
				}
				else {
					std::cerr << "Warmup time for benchmark mode must be specified as a number!" << std::endl;
				}
			}
		}
		// Benchmark runtime (in seconds)
		if ((args[i] == std::string("-br")) || (args[i] == std::string("--benchruntime"))) {
			if (args.size() > i + 1) {
				uint32_t num = strtol(args[i + 1], &numConvPtr, 10);
				if (numConvPtr != args[i + 1]) {
					benchmark.duration = num;
				}
				else {
					std::cerr << "Benchmark run duration must be specified as a number!" << std::endl;
				}
			}
		}
		// Bench result save filename (overrides default)
		if ((args[i] == std::string("-bf")) || (args[i] == std::string("--benchfilename"))) {
			if (args.size() > i + 1) {
				if (args[i + 1][0] == '-') {
					std::cerr << "Filename for benchmark results must not start with a hyphen!" << std::endl;
				}
				else {
					benchmark.filename = args[i + 1];
				}
			}
		}
		// Output frame times to benchmark result file
		if ((args[i] == std::string("-bt")) || (args[i] == std::string("--benchframetimes"))) {
			benchmark.outputFrameTimes = true;
		}
	}

#if defined(_WIN32)
	// Enable console if validation is active
	// Debug message callback will output to it
	if (this->settings.validation)
	{
		setupConsole("Vulkan validation output");
	}
	setupDPIAwareness();
#endif
}

VulkanRenderer::~VulkanRenderer() {
	// Clean up Vulkan resources
	swapChain.cleanup();
	if (descriptorPool != VK_NULL_HANDLE) {
		vkDestroyDescriptorPool(device, descriptorPool, nullptr);
	}
	destroyCommandBuffers();
	vkDestroyRenderPass(device, renderPass, nullptr);
	for (uint32_t i = 0; i < frameBuffers.size(); i++) {
		vkDestroyFramebuffer(device, frameBuffers[i], nullptr);
	}

	for (auto& shaderModule : shaderModules) {
		vkDestroyShaderModule(device, shaderModule, nullptr);
	}
	vkDestroyImageView(device, depthStencil.view, nullptr);
	vkDestroyImage(device, depthStencil.image, nullptr);
	vkFreeMemory(device, depthStencil.mem, nullptr);

	vkDestroyPipelineCache(device, pipelineCache, nullptr);

	vkDestroyCommandPool(device, cmdPool, nullptr);

	vkDestroySemaphore(device, semaphores.presentComplete, nullptr);
	vkDestroySemaphore(device, semaphores.renderComplete, nullptr);
	for (auto& fence : waitFences) {
		vkDestroyFence(device, fence, nullptr);
	}

	if (settings.overlay) {
		overlay.freeResources();
	}

	delete vulkanDevice;

	if (settings.validation) {
		debug::freeDebugCallback(instance);
	}

	vkDestroyInstance(instance, nullptr);
}

bool VulkanRenderer::initVulkan() {
	VkResult err;

	// Vulkan instance
	err = createInstance(settings.validation);
	if (err) {
		tools::exitFatal("Could not create Vulkan instance : \n" + tools::errorString(err), err);
		return false;
	}

	// If requested, we enable the default validation layers for debugging
	if (settings.validation) {
		// The report flags determine what type of messages for the layers will be displayed
		// For validating (debugging) an appplication the error and warning bits should suffice
		VkDebugReportFlagsEXT debugReportFlags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		// Additional flags include performance info, loader and layer debug messages, etc.
		debug::setupDebugging(instance, debugReportFlags, VK_NULL_HANDLE);
	}

	// Physical device
	uint32_t gpuCount = 0;
	// Get number of available physical devices
	tools::VK_VERIFY_SUCCESS(vkEnumeratePhysicalDevices(instance, &gpuCount, nullptr));
	assert(gpuCount > 0);
	// Enumerate devices
	std::vector<VkPhysicalDevice> physicalDevices(gpuCount);
	err = vkEnumeratePhysicalDevices(instance, &gpuCount, physicalDevices.data());
	if (err) {
		tools::exitFatal("Could not enumerate physical devices : \n" + tools::errorString(err), err);
		return false;
	}

	// GPU selection

	// Select physical device to be used for the Vulkan example
	// Defaults to the first device unless specified by command line
	uint32_t selectedDevice = 0;

	// GPU selection via command line argument
	for (size_t i = 0; i < args.size(); i++) {
		// Select GPU
		if ((args[i] == std::string("-g")) || (args[i] == std::string("-gpu"))) {
			char* endptr;
			uint32_t index = strtol(args[i + 1], &endptr, 10);
			if (endptr != args[i + 1]) {
				if (index > gpuCount - 1) {
					std::cerr << "Selected device index " << index << " is out of range, reverting to device 0 (use -listgpus to show available Vulkan devices)" << std::endl;
				}
				else {
					std::cout << "Selected Vulkan device " << index << std::endl;
					selectedDevice = index;
				}
			};
			break;
		}
		// List available GPUs
		if (args[i] == std::string("-listgpus")) {
			uint32_t gpuCount = 0;
			tools::VK_VERIFY_SUCCESS(vkEnumeratePhysicalDevices(instance, &gpuCount, nullptr));
			if (gpuCount == 0) {
				std::cerr << "No Vulkan devices found!" << std::endl;
			}
			else {
				// Enumerate devices
				std::cout << "Available Vulkan devices" << std::endl;
				std::vector<VkPhysicalDevice> devices(gpuCount);
				tools::VK_VERIFY_SUCCESS(vkEnumeratePhysicalDevices(instance, &gpuCount, devices.data()));
				for (uint32_t i = 0; i < gpuCount; i++) {
					VkPhysicalDeviceProperties deviceProperties;
					vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
					std::cout << "Device [" << i << "] : " << deviceProperties.deviceName << std::endl;
					std::cout << " Type: " << tools::physicalDeviceTypeString(deviceProperties.deviceType) << std::endl;
					std::cout << " API: " << (deviceProperties.apiVersion >> 22) << "." << ((deviceProperties.apiVersion >> 12) & 0x3ff) << "." << (deviceProperties.apiVersion & 0xfff) << std::endl;
				}
			}
		}
	}

	physicalDevice = physicalDevices[selectedDevice];

	// Store properties (including limits), features and memory properties of the phyiscal device (so that examples can check against them)
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &deviceMemoryProperties);

	// Derived examples can override this to set actual features (based on above readings) to enable for logical device creation
	getEnabledFeatures();

	// Vulkan device creation
	// This is handled by a separate class that gets a logical device representation
	// and encapsulates functions related to a device
	vulkanDevice = new VulkanDevice(physicalDevice);
	VkResult res = vulkanDevice->createLogicalDevice(enabledFeatures, enabledDeviceExtensions, deviceCreatepNextChain);
	if (res != VK_SUCCESS) {
		tools::exitFatal("Could not create Vulkan device: \n" + tools::errorString(res), res);
		return false;
	}
	device = vulkanDevice->logicalDevice;

	// Get a graphics queue from the device
	vkGetDeviceQueue(device, vulkanDevice->queueFamilyIndices.graphics, 0, &queue);

	// Find a suitable depth format
	VkBool32 validDepthFormat = tools::getSupportedDepthFormat(physicalDevice, &depthFormat);
	assert(validDepthFormat);

	swapChain.connect(instance, physicalDevice, device);

	// Create synchronization objects
	VkSemaphoreCreateInfo semaphoreCreateInfo = initializers::semaphoreCreateInfo();
	// Create a semaphore used to synchronize image presentation
	// Ensures that the image is displayed before we start submitting new commands to the queu
	tools::VK_VERIFY_SUCCESS(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &semaphores.presentComplete));
	// Create a semaphore used to synchronize command submission
	// Ensures that the image is not presented until all commands have been sumbitted and executed
	tools::VK_VERIFY_SUCCESS(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &semaphores.renderComplete));

	// Set up submit info structure
	// Semaphores will stay the same during application lifetime
	// Command buffer submission info is set by each example
	submitInfo = initializers::submitInfo();
	submitInfo.pWaitDstStageMask = &submitPipelineStages;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &semaphores.presentComplete;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &semaphores.renderComplete;

	return true;
}

#if defined(_WIN32)
// Win32 : Sets up a console window and redirects standard output to it
void VulkanRenderer::setupConsole(std::string title) {
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w+", stdout);
	freopen_s(&stream, "CONOUT$", "w+", stderr);
	SetConsoleTitle(TEXT(title.c_str()));
}

void VulkanRenderer::setupDPIAwareness() {
	typedef HRESULT* (__stdcall * SetProcessDpiAwarenessFunc)(PROCESS_DPI_AWARENESS);

	HMODULE shCore = LoadLibraryA("Shcore.dll");
	if (shCore) {
		SetProcessDpiAwarenessFunc setProcessDpiAwareness = (SetProcessDpiAwarenessFunc)GetProcAddress(shCore, "SetProcessDpiAwareness");

		if (setProcessDpiAwareness != nullptr) {
			setProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		}

		FreeLibrary(shCore);
	}
}

HWND VulkanRenderer::setupWindow(HINSTANCE hinstance, WNDPROC wndproc) {
	this->windowInstance = hinstance;

	WNDCLASSEX wndClass;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = wndproc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hinstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = name.c_str();
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wndClass)) {
		std::cout << "Could not register window class!\n";
		fflush(stdout);
		exit(1);
	}

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (settings.fullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = screenWidth;
		dmScreenSettings.dmPelsHeight = screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if ((width != (uint32_t)screenWidth) && (height != (uint32_t)screenHeight)) {
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
				if (MessageBox(NULL, "Fullscreen Mode not supported!\n Switch to window mode?", "Error", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
					settings.fullscreen = false;
				}
				else {
					return nullptr;
				}
			}
		}

	}

	DWORD dwExStyle;
	DWORD dwStyle;

	if (settings.fullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	}
	else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	}

	RECT windowRect;
	windowRect.left = 0L;
	windowRect.top = 0L;
	windowRect.right = settings.fullscreen ? (long)screenWidth : (long)width;
	windowRect.bottom = settings.fullscreen ? (long)screenHeight : (long)height;

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	std::string windowTitle = getWindowTitle();
	window = CreateWindowEx(0,
		name.c_str(),
		windowTitle.c_str(),
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hinstance,
		NULL);

	if (!settings.fullscreen) {
		// Center on screen
		uint32_t x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
		uint32_t y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
		SetWindowPos(window, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	if (!window) {
		printf("Could not create window!\n");
		fflush(stdout);
		return nullptr;
		exit(1);
	}

	ShowWindow(window, SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);

	return window;
}

void VulkanRenderer::handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	float wheelDelta;
	switch (uMsg) {
	case WM_CLOSE:
		prepared = false;
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		ValidateRect(window, NULL);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case KEY_P:
			paused = !paused;
			break;
		case KEY_F1:
			if (settings.overlay) {
				overlay.visible = !overlay.visible;
			}
			break;
		case KEY_ESCAPE:
			PostQuitMessage(0);
			break;
		case KEY_R:
			resetTime = std::chrono::high_resolution_clock::now();
			frameCount = 0;
			break;
		}

		if (camera.firstperson) {
			switch (wParam) {
			case KEY_W:
				camera.keys.up = true;
				break;
			case KEY_S:
				camera.keys.down = true;
				break;
			case KEY_A:
				camera.keys.left = true;
				break;
			case KEY_D:
				camera.keys.right = true;
				break;
			}
		}

		keyPressed((uint32_t)wParam);
		break;
	case WM_KEYUP:
		if (camera.firstperson) {
			switch (wParam)
			{
			case KEY_W:
				camera.keys.up = false;
				break;
			case KEY_S:
				camera.keys.down = false;
				break;
			case KEY_A:
				camera.keys.left = false;
				break;
			case KEY_D:
				camera.keys.right = false;
				break;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		mousePos = glm::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
		mouseButtons.left = true;
		break;
	case WM_RBUTTONDOWN:
		mousePos = glm::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
		mouseButtons.right = true;
		break;
	case WM_MBUTTONDOWN:
		mousePos = glm::vec2((float)LOWORD(lParam), (float)HIWORD(lParam));
		mouseButtons.middle = true;
		break;
	case WM_LBUTTONUP:
		mouseButtons.left = false;
		break;
	case WM_RBUTTONUP:
		mouseButtons.right = false;
		break;
	case WM_MBUTTONUP:
		mouseButtons.middle = false;
		break;
	case WM_MOUSEWHEEL:
		wheelDelta = (float)GET_WHEEL_DELTA_WPARAM(wParam);
		zoom += wheelDelta * 0.005f * zoomSpeed;
		camera.translate(glm::vec3(0.0f, 0.0f, wheelDelta * 0.005f * zoomSpeed));
		viewUpdated = true;
		break;
	case WM_MOUSEMOVE:
		handleMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_SIZE:
		if ((prepared) && (wParam != SIZE_MINIMIZED)) {
			if ((resizing) || ((wParam == SIZE_MAXIMIZED) || (wParam == SIZE_RESTORED))) {
				destWidth = LOWORD(lParam);
				destHeight = HIWORD(lParam);
				windowResize();
			}
		}
		break;
	case WM_ENTERSIZEMOVE:
		resizing = true;
		break;
	case WM_EXITSIZEMOVE:
		resizing = false;
		break;
	}
}
#elif defined(VK_USE_PLATFORM_MACOS_MVK))
void* VulkanRenderer::setupWindow(void* view) {
	this->view = view;
	return view;
}
#endif

void VulkanRenderer::viewChanged() {}

void VulkanRenderer::keyPressed(uint32_t) {}

void VulkanRenderer::mouseMoved(double x, double y, bool& handled) {}

void VulkanRenderer::buildCommandBuffers() {}

void VulkanRenderer::createSynchronizationPrimitives() {
	// Wait fences to sync command buffer access
	VkFenceCreateInfo fenceCreateInfo = initializers::fenceCreateInfo(VK_FENCE_CREATE_SIGNALED_BIT);
	waitFences.resize(drawCmdBuffers.size());
	for (auto& fence : waitFences) {
		tools::VK_VERIFY_SUCCESS(vkCreateFence(device, &fenceCreateInfo, nullptr, &fence));
	}
}

void VulkanRenderer::createCommandPool() {
	VkCommandPoolCreateInfo cmdPoolInfo = {};
	cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolInfo.queueFamilyIndex = swapChain.queueNodeIndex;
	cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	tools::VK_VERIFY_SUCCESS(vkCreateCommandPool(device, &cmdPoolInfo, nullptr, &cmdPool));
}

void VulkanRenderer::setupDepthStencil() {
	VkImageCreateInfo imageCI{};
	imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCI.imageType = VK_IMAGE_TYPE_2D;
	imageCI.format = depthFormat;
	imageCI.extent = { width, height, 1 };
	imageCI.mipLevels = 1;
	imageCI.arrayLayers = 1;
	imageCI.samples = VK_SAMPLE_COUNT_1_BIT;
	imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageCI.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

	tools::VK_VERIFY_SUCCESS(vkCreateImage(device, &imageCI, nullptr, &depthStencil.image));
	VkMemoryRequirements memReqs{};
	vkGetImageMemoryRequirements(device, depthStencil.image, &memReqs);

	VkMemoryAllocateInfo memAllloc{};
	memAllloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAllloc.allocationSize = memReqs.size;
	memAllloc.memoryTypeIndex = vulkanDevice->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device, &memAllloc, nullptr, &depthStencil.mem));
	tools::VK_VERIFY_SUCCESS(vkBindImageMemory(device, depthStencil.image, depthStencil.mem, 0));

	VkImageViewCreateInfo imageViewCI{};
	imageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCI.image = depthStencil.image;
	imageViewCI.format = depthFormat;
	imageViewCI.subresourceRange.baseMipLevel = 0;
	imageViewCI.subresourceRange.levelCount = 1;
	imageViewCI.subresourceRange.baseArrayLayer = 0;
	imageViewCI.subresourceRange.layerCount = 1;
	imageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	// Stencil aspect should only be set on depth + stencil formats (VK_FORMAT_D16_UNORM_S8_UINT..VK_FORMAT_D32_SFLOAT_S8_UINT
	if (depthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
		imageViewCI.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}
	tools::VK_VERIFY_SUCCESS(vkCreateImageView(device, &imageViewCI, nullptr, &depthStencil.view));
}

void VulkanRenderer::setupFrameBuffer() {
	VkImageView attachments[2];

	// Depth/Stencil attachment is the same for all frame buffers
	attachments[1] = depthStencil.view;

	VkFramebufferCreateInfo frameBufferCreateInfo = {};
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	frameBufferCreateInfo.pNext = NULL;
	frameBufferCreateInfo.renderPass = renderPass;
	frameBufferCreateInfo.attachmentCount = 2;
	frameBufferCreateInfo.pAttachments = attachments;
	frameBufferCreateInfo.width = width;
	frameBufferCreateInfo.height = height;
	frameBufferCreateInfo.layers = 1;

	// Create frame buffers for every swap chain image
	frameBuffers.resize(swapChain.imageCount);
	for (uint32_t i = 0; i < frameBuffers.size(); i++) {
		attachments[0] = swapChain.buffers[i].view;
		tools::VK_VERIFY_SUCCESS(vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, &frameBuffers[i]));
	}
}

void VulkanRenderer::setupRenderPass() {
	std::array<VkAttachmentDescription, 2> attachments = {};
	// Color attachment
	attachments[0].format = swapChain.colorFormat;
	attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	// Depth attachment
	attachments[1].format = depthFormat;
	attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference colorReference = {};
	colorReference.attachment = 0;
	colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthReference = {};
	depthReference.attachment = 1;
	depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpassDescription = {};
	subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpassDescription.colorAttachmentCount = 1;
	subpassDescription.pColorAttachments = &colorReference;
	subpassDescription.pDepthStencilAttachment = &depthReference;
	subpassDescription.inputAttachmentCount = 0;
	subpassDescription.pInputAttachments = nullptr;
	subpassDescription.preserveAttachmentCount = 0;
	subpassDescription.pPreserveAttachments = nullptr;
	subpassDescription.pResolveAttachments = nullptr;

	// Subpass dependencies for layout transitions
	std::array<VkSubpassDependency, 2> dependencies;

	dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
	dependencies[0].dstSubpass = 0;
	dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	dependencies[1].srcSubpass = 0;
	dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
	dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
	dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

	VkRenderPassCreateInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	renderPassInfo.pAttachments = attachments.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpassDescription;
	renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
	renderPassInfo.pDependencies = dependencies.data();

	tools::VK_VERIFY_SUCCESS(vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass));
}

void VulkanRenderer::getEnabledFeatures() {
	// Can be overriden in derived class
	if (deviceFeatures.samplerAnisotropy) {
		enabledFeatures.samplerAnisotropy = VK_TRUE;
	}
}

void VulkanRenderer::windowResize() {
	if (!prepared) { return; }
	prepared = false;

	// Ensure all operations on the device have been finished before destroying resources
	vkDeviceWaitIdle(device);

	// Recreate swap chain
	width = destWidth;
	height = destHeight;
	setupSwapChain();

	// Recreate the frame buffers
	vkDestroyImageView(device, depthStencil.view, nullptr);
	vkDestroyImage(device, depthStencil.image, nullptr);
	vkFreeMemory(device, depthStencil.mem, nullptr);
	setupDepthStencil();
	for (uint32_t i = 0; i < frameBuffers.size(); i++) {
		vkDestroyFramebuffer(device, frameBuffers[i], nullptr);
	}
	setupFrameBuffer();

	if ((width > 0.0f) && (height > 0.0f)) {
		if (settings.overlay) {
			overlay.resize(width, height);
		}
	}

	// Command buffers need to be recreated as they may store
	// references to the recreated frame buffer
	destroyCommandBuffers();
	createCommandBuffers();
	buildCommandBuffers();

	vkDeviceWaitIdle(device);

	if ((width > 0.0f) && (height > 0.0f)) {
		camera.updateAspectRatio((float)width / (float)height);
	}

	// Notify derived class
	windowResized();
	viewChanged();

	prepared = true;
}

void VulkanRenderer::buildComputeCommandBuffer() {}

void VulkanRenderer::handleMouseMove(int32_t x, int32_t y) {
	int32_t dx = (int32_t)mousePos.x - x;
	int32_t dy = (int32_t)mousePos.y - y;

	bool handled = false;

	if (settings.overlay) {
		ImGuiIO& io = ImGui::GetIO();
		handled = io.WantCaptureMouse;
	}
	mouseMoved((float)x, (float)y, handled);

	if (handled) {
		mousePos = glm::vec2((float)x, (float)y);
		return;
	}

	if (mouseButtons.left) {
		rotation.x += dy * 1.25f * rotationSpeed;
		rotation.y -= dx * 1.25f * rotationSpeed;
		camera.rotate(glm::vec3(dy * camera.rotationSpeed, -dx * camera.rotationSpeed, 0.0f));
		viewUpdated = true;
	}
	if (mouseButtons.right) {
		zoom += dy * .005f * zoomSpeed;
		camera.translate(glm::vec3(-0.0f, 0.0f, dy * .005f * zoomSpeed));
		viewUpdated = true;
	}
	if (mouseButtons.middle) {
		cameraPos.x -= dx * 0.01f;
		cameraPos.y -= dy * 0.01f;
		camera.translate(glm::vec3(-dx * 0.01f, -dy * 0.01f, 0.0f));
		viewUpdated = true;
	}
	mousePos = glm::vec2((float)x, (float)y);
}

void VulkanRenderer::windowResized() {
	// Can be overriden in derived class
}

void VulkanRenderer::initSwapchain() {
#if defined(_WIN32)
	swapChain.initSurface(windowInstance, window);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	swapChain.initSurface(view);
#endif
}

void VulkanRenderer::setupSwapChain() {
	swapChain.create(&width, &height, settings.vsync);
}

void VulkanRenderer::OnUpdateUIOverlay(UIOverlay* overlay) {}







/**

VULKAN RASTERIZER SEGMENT

**/

class VulkanRasterizer : public VulkanRenderer {
public:
	// Constructor / Deconstructor
	VulkanRasterizer() : VulkanRenderer(ENABLE_VALIDATION) {
		zoom = -32.5f;
		zoomSpeed = 2.5f;
		rotationSpeed = 0.5f;
		rotation = { 0.0f, 37.5f, 0.0f };
		camera.type = Camera::CameraType::firstperson;
		camera.setPerspective(60.0f, (float)width / (float)height, 0.1f, 2048.0f); // default 512
		camera.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
		camera.setTranslation(glm::vec3(0.0f, 5.0f, -8.0f));
		title = "Billiards Simulation";
		settings.overlay = true;
		// Get number of max. concurrent threads
		//numThreads = std::thread::hardware_concurrency();
		numThreads = 7; //1 usually?
		assert(numThreads > 0);
		std::cout << "numThreads = " << numThreads << std::endl;
		threadPool.setThreadCount(numThreads);
		numObjectsPerThread = 1;
		rndEngine.seed(benchmark.active ? 0 : (unsigned)time(nullptr));
	}

	~VulkanRasterizer() {
		// Clean up used Vulkan resources 
		// Note : Inherited destructor cleans up resources stored in base class
		vkDestroyPipeline(device, pipelines.phong, nullptr);
		vkDestroyPipeline(device, pipelines.starsphere, nullptr);
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

		//models.ufo.destroy();
		models.skysphere.destroy();
		for (int i = 0; i < models_list.size(); i++) {
			models_list.at(i).destroy();
		}

		for (auto& thread : threadData) {
			vkFreeCommandBuffers(device, thread.commandPool, thread.commandBuffer.size(), thread.commandBuffer.data());
			vkDestroyCommandPool(device, thread.commandPool, nullptr);
		}

		vkDestroyFence(device, renderFence, nullptr);
	}

	void setupDescriptorPool() {
		std::vector<VkDescriptorPoolSize> poolSizes = {
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 3),
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4),
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 2)
		};

		VkDescriptorPoolCreateInfo descriptorPoolInfo =
			initializers::descriptorPoolCreateInfo(poolSizes, 3);

		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorPool(device, &descriptorPoolInfo, nullptr, &descriptorPool));
	}

	// Create all threads and initialize shader push constants
	void prepareMultiThreadedRenderer() {
		// Since this demo updates the command buffers on each frame
		// we don't use the per-framebuffer command buffers from the
		// base class, and create a single primary command buffer instead
		VkCommandBufferAllocateInfo cmdBufAllocateInfo =
			initializers::commandBufferAllocateInfo(
				cmdPool,
				VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				1);
		tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &primaryCommandBuffer));

		// Create additional secondary CBs for background and ui
		cmdBufAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &secondaryCommandBuffers.background));
		tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &secondaryCommandBuffers.ui));

		threadData.resize(numThreads);

		float maxX = std::floor(std::sqrt(numThreads * numObjectsPerThread));
		uint32_t posX = 0;
		uint32_t posZ = 0;

		for (uint32_t i = 0; i < numThreads; i++) {
			ThreadData* thread = &threadData[i];

			// Create one command pool for each thread
			VkCommandPoolCreateInfo cmdPoolInfo = initializers::commandPoolCreateInfo();
			cmdPoolInfo.queueFamilyIndex = swapChain.queueNodeIndex;
			cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
			tools::VK_VERIFY_SUCCESS(vkCreateCommandPool(device, &cmdPoolInfo, nullptr, &thread->commandPool));

			// One secondary command buffer per object that is updated by this thread
			thread->commandBuffer.resize(numObjectsPerThread);
			// Generate secondary command buffers for each thread
			VkCommandBufferAllocateInfo secondaryCmdBufAllocateInfo =
				initializers::commandBufferAllocateInfo(
					thread->commandPool,
					VK_COMMAND_BUFFER_LEVEL_SECONDARY,
					thread->commandBuffer.size());
			tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &secondaryCmdBufAllocateInfo, thread->commandBuffer.data()));

			thread->pushConstBlock.resize(numObjectsPerThread);
			thread->objectData.resize(numObjectsPerThread);

			for (uint32_t j = 0; j < numObjectsPerThread; j++) {
				//float theta = 2.0f * float(M_PI) * rnd(1.0f);
				//float phi = acos(1.0f - 2.0f * rnd(1.0f));
				thread->objectData[j].pos = glm::vec3(0, 0, 0);// glm::vec3(sin(phi) * cos(theta), 0.0f, cos(phi)) * 35.0f;

				thread->objectData[j].rotation = glm::vec3(0, 0, 0);// glm::vec3(0.0f, rnd(360.0f), 0.0f);
				thread->objectData[j].deltaT = 1.0;// rnd(1.0f);
				thread->objectData[j].rotationDir = 1.0f;// (rnd(100.0f) < 50.0f) ? 1.0f : -1.0f;
				thread->objectData[j].rotationSpeed = 1.0;// (2.0f + rnd(4.0f))* thread->objectData[j].rotationDir;
				thread->objectData[j].scale = 1.0;// 0.75f + rnd(0.5f);

				thread->pushConstBlock[j].color = glm::vec3(rnd(1.0f), rnd(1.0f), rnd(1.0f));
			}
		}

	}

	// Builds the secondary command buffer for each thread
	void threadRenderCode(uint32_t threadIndex, uint32_t cmdBufferIndex, VkCommandBufferInheritanceInfo inheritanceInfo) {
		ThreadData* thread = &threadData[threadIndex];
		ObjectData* objectData = &thread->objectData[cmdBufferIndex];
		Model& m = models_list.at(threadIndex); //at() returns a reference!

		// Check visibility against view frustum
		bool visible = frustum.checkSphere(m.position, objectSphereDim * 0.5f);
		if (!visible) {
			return;
		}

		VkCommandBufferBeginInfo commandBufferBeginInfo = initializers::commandBufferBeginInfo();
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
		commandBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;

		VkCommandBuffer cmdBuffer = thread->commandBuffer[cmdBufferIndex];

		tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(cmdBuffer, &commandBufferBeginInfo));

		VkViewport viewport = initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
		vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);

		VkRect2D scissor = initializers::rect2D(width, height, 0, 0);
		vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);

		vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.phong);

		// update based on animation type
		float rotat = 0;
		switch (m.aniType) {
		case ANI_STATIC:
			glm::mat4 id_mat(1.0f);
			glm::vec3 scaling(1.0, 0.5, 0.5); //right-left, back-front, up-down
			rotat = glm::radians(-90.0f);
			glm::vec3 rot_axis = glm::vec3(1, 0, 0);
			glm::vec3 pos(10,1,10); //right-left, back-front, up-down
			thread->pushConstBlock[cmdBufferIndex].mvp = matrices.projection * matrices.view * glm::translate(glm::scale(glm::rotate(id_mat, m.rot_angle, m.rotation_axis), m.scaling), m.position);//objectData->model;
			break;
		
		case ANI_MOCAP:
			break;

		case ANI_BILLIARDS:
			//ANI_BILLIARDS models get updated in UpdateModelsList(), here we just package it into a glm::mat4
			glm::mat4 modelTransform = glm::translate(glm::mat4(1.0), m.position) * glm::scale(glm::mat4(1.0f), glm::vec3(m.scale, m.scale, m.scale)) * glm::mat4_cast(m.rotation);
			thread->pushConstBlock[cmdBufferIndex].mvp = matrices.projection * matrices.view * modelTransform;
			break;
		
		case ANI_KEYFRAMES:
			std::chrono::milliseconds time_since_reset = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - resetTime);
			float reset_time_in_seconds = time_since_reset.count() / 1000.0;
			if (keyframes.size() == 0) {
				tools::LoadInfile("keyframe-input.txt", keyframes);
			}
			int kf_idx = tools::GetFirstKeyframeIndex(keyframes, reset_time_in_seconds);
			if (kf_idx == keyframes.size() - 1) {
				glm::quat obj_rotation = keyframes.at(kf_idx).rot;
				obj_rotation = glm::normalize(obj_rotation);
				objectData->model = keyframes.at(kf_idx).trans * glm::mat4_cast(obj_rotation);
			} else {
				float time1 = keyframes.at(kf_idx).time;
				float time2 = keyframes.at(kf_idx + 1).time;
				animation_alpha = (reset_time_in_seconds - time1) / (time2 - time1);

				//glm::quat obj_rotation = glm::lerp(keyframes.at(kf_idx).rot, keyframes.at(kf_idx + 1).rot, animation_alpha);
				glm::quat obj_rotation = glm::slerp(keyframes.at(kf_idx).rot, keyframes.at(kf_idx + 1).rot, animation_alpha);
				obj_rotation = glm::normalize(obj_rotation);
				glm::mat4 obj_trans = glm::interpolate(keyframes.at(kf_idx).trans, keyframes.at(kf_idx + 1).trans, animation_alpha);
				objectData->model = obj_trans * glm::mat4_cast(obj_rotation);
			}

			thread->pushConstBlock[cmdBufferIndex].mvp = matrices.projection * matrices.view * objectData->model;
			break;
		}

		// Update shader push constant block
		// Contains model view matrix
		vkCmdPushConstants(
			cmdBuffer,
			pipelineLayout,
			VK_SHADER_STAGE_VERTEX_BIT,
			0,
			sizeof(ThreadPushConstantBlock),
			&thread->pushConstBlock[cmdBufferIndex]);

		VkDeviceSize offsets[1] = { 0 };
		vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &models_list.at(threadIndex).vertices.buffer, offsets);
		vkCmdBindIndexBuffer(cmdBuffer, models_list.at(threadIndex).indices.buffer, 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(cmdBuffer, models_list.at(threadIndex).indexCount, 1, 0, 0, 0);

		tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(cmdBuffer));
	}

	void updateSecondaryCommandBuffers(VkCommandBufferInheritanceInfo inheritanceInfo) {
		// Secondary command buffer for the sky sphere
		VkCommandBufferBeginInfo commandBufferBeginInfo = initializers::commandBufferBeginInfo();
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
		commandBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;

		VkViewport viewport = initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
		VkRect2D scissor = initializers::rect2D(width, height, 0, 0);

		/*
			Background
		*/

		tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(secondaryCommandBuffers.background, &commandBufferBeginInfo));

		vkCmdSetViewport(secondaryCommandBuffers.background, 0, 1, &viewport);
		vkCmdSetScissor(secondaryCommandBuffers.background, 0, 1, &scissor);

		vkCmdBindPipeline(secondaryCommandBuffers.background, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.starsphere);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::rotate(view, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 mvp = matrices.projection * view;

		vkCmdPushConstants(
			secondaryCommandBuffers.background,
			pipelineLayout,
			VK_SHADER_STAGE_VERTEX_BIT,
			0,
			sizeof(mvp),
			&mvp);

		VkDeviceSize offsets[1] = { 0 };
		vkCmdBindVertexBuffers(secondaryCommandBuffers.background, 0, 1, &models.skysphere.vertices.buffer, offsets);
		vkCmdBindIndexBuffer(secondaryCommandBuffers.background, models.skysphere.indices.buffer, 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(secondaryCommandBuffers.background, models.skysphere.indexCount, 1, 0, 0, 0);

		tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(secondaryCommandBuffers.background));

		/*
			User interface

			With VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS, the primary command buffer's content has to be defined
			by secondary command buffers, which also applies to the UI overlay command buffer
		*/

		tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(secondaryCommandBuffers.ui, &commandBufferBeginInfo));

		vkCmdSetViewport(secondaryCommandBuffers.ui, 0, 1, &viewport);
		vkCmdSetScissor(secondaryCommandBuffers.ui, 0, 1, &scissor);

		vkCmdBindPipeline(secondaryCommandBuffers.ui, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.starsphere);

		if (settings.overlay) {
			drawUI(secondaryCommandBuffers.ui);
		}

		tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(secondaryCommandBuffers.ui));
	}

	// Updates the secondary command buffers using a thread pool 
	// and puts them into the primary command buffer that's 
	// lat submitted to the queue for rendering
	void updateCommandBuffers(VkFramebuffer frameBuffer) {
		// Contains the list of secondary command buffers to be submitted
		std::vector<VkCommandBuffer> commandBuffers;

		VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();

		VkClearValue clearValues[2];
		clearValues[0].color = defaultClearColor;
		clearValues[1].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderPassBeginInfo = initializers::renderPassBeginInfo();
		renderPassBeginInfo.renderPass = renderPass;
		renderPassBeginInfo.renderArea.offset.x = 0;
		renderPassBeginInfo.renderArea.offset.y = 0;
		renderPassBeginInfo.renderArea.extent.width = width;
		renderPassBeginInfo.renderArea.extent.height = height;
		renderPassBeginInfo.clearValueCount = 2;
		renderPassBeginInfo.pClearValues = clearValues;
		renderPassBeginInfo.framebuffer = frameBuffer;

		// Set target frame buffer

		tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(primaryCommandBuffer, &cmdBufInfo));

		// The primary command buffer does not contain any rendering commands
		// These are stored (and retrieved) from the secondary command buffers
		vkCmdBeginRenderPass(primaryCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);

		// Inheritance info for the secondary command buffers
		VkCommandBufferInheritanceInfo inheritanceInfo = initializers::commandBufferInheritanceInfo();
		inheritanceInfo.renderPass = renderPass;
		// Secondary command buffer also use the currently active framebuffer
		inheritanceInfo.framebuffer = frameBuffer;

		// Update secondary sene command buffers
		updateSecondaryCommandBuffers(inheritanceInfo);

		if (displaySkybox) {
			commandBuffers.push_back(secondaryCommandBuffers.background);
		}

		// Add a job to the thread's queue for each object to be rendered
		for (uint32_t t = 0; t < numThreads; t++) {
			for (uint32_t i = 0; i < numObjectsPerThread; i++) {
				threadPool.threads[t]->addJob([=] { threadRenderCode(t, i, inheritanceInfo); });
			}
		}

		threadPool.wait();

		// Only submit if object is within the current view frustum
		for (uint32_t t = 0; t < numThreads; t++) {
			for (uint32_t i = 0; i < numObjectsPerThread; i++) {
				if (threadData[t].objectData[i].visible) {
					commandBuffers.push_back(threadData[t].commandBuffer[i]);
				}
			}
		}

		// Render ui last
		if (overlay.visible) {
			commandBuffers.push_back(secondaryCommandBuffers.ui);
		}

		// Execute render commands from the secondary command buffer
		vkCmdExecuteCommands(primaryCommandBuffer, commandBuffers.size(), commandBuffers.data());

		vkCmdEndRenderPass(primaryCommandBuffer);

		tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(primaryCommandBuffer));
	}

	void loadAssets() {
		//models.ufo.loadFromFile(getAssetPath() + "models/retroufo_red_lowpoly.dae", vertexLayout, 0.12f, vulkanDevice, queue);
		//models.ufo.loadFromFile(getAssetPath() + "models/teapot.dae", vertexLayout, 0.25f, vulkanDevice, queue);
		//models.ufo.loadFromFile(getAssetPath() + "models/cube.dae", vertexLayout, 2.0f, vulkanDevice, queue);
		models.skysphere.loadFromFile(getAssetPath() + "models/sphere.obj", vertexLayout, 1.0f, vulkanDevice, queue);
		//objectSphereDim = std::max(std::max(models.ufo.dim.size.x, models.ufo.dim.size.y), models.ufo.dim.size.z);

		/// BILIARDS SETUP
		glm::vec3 positions[] = {
			glm::vec3( 2.0f, 5.0f, 0.0f), // cueball
			glm::vec3( 8.0f, 5.0f, 0.0f), //rest are green
			glm::vec3(12.0f, 7.0f, 0.0f),
			glm::vec3(15.0f, 4.5f, 0.0f)
		};

		Model cueball;
		cueball.loadFromFile(getAssetPath() + "models/sphere.obj", vertexLayout, 0.03f, vulkanDevice, queue);
		cueball.aniType = ANI_BILLIARDS;
		cueball.position = positions[0];
		models_list.push_back(cueball);

		for (int i = 1; i < 4; i++) {
			Model m;
			m.loadFromFile(getAssetPath() + "models/sphere.3ds", vertexLayout, 0.03f, vulkanDevice, queue);
			m.aniType = ANI_BILLIARDS;
			m.position = positions[i];
			models_list.push_back(m);
		}

		Model board;
		board.loadFromFile(getAssetPath() + "models/plane.obj", vertexLayout, 1.0f, vulkanDevice, queue);
		board.aniType = ANI_STATIC;
		//right-left, back-front, up-down
		board.position = glm::vec3(10, 1, 10);
		board.scaling = glm::vec3(1.0, 0.5, 1.0);
		board.rot_angle = glm::radians(-90.0f);
		board.rotation_axis = glm::vec3(1, 0, 0);
		models_list.push_back(board);

		Model boardtop;
		boardtop.loadFromFile(getAssetPath() + "models/plane.obj", vertexLayout, 1.0f, vulkanDevice, queue);
		boardtop.aniType = ANI_STATIC;
		boardtop.position = glm::vec3(10, 0, 8);
		boardtop.scaling = glm::vec3(1.0,1.0,0.1);
		boardtop.rotation_axis = glm::vec3(1, 0, 0);
		boardtop.rot_angle = glm::radians(180.0f);
		models_list.push_back(boardtop);

		Model boardright;
		boardright.loadFromFile(getAssetPath() + "models/plane.obj", vertexLayout, 1.0f, vulkanDevice, queue);
		boardright.aniType = ANI_STATIC;
		boardright.position = glm::vec3(0, 0, 0);
		//models_list.push_back(boardright);

		Model boardleft;
		boardleft.loadFromFile(getAssetPath() + "models/plane.obj", vertexLayout, 1.0f, vulkanDevice, queue);
		boardleft.aniType = ANI_STATIC;
		boardleft.position = glm::vec3(10, 0, -10);
		boardleft.scaling = glm::vec3(1.0, 1.0, 0.1);
		boardleft.rotation_axis = glm::vec3(0, 0, 1);
		boardleft.rot_angle = glm::radians(90.0f);
		models_list.push_back(boardleft);

		Model boardbottom;
		boardbottom.loadFromFile(getAssetPath() + "models/plane.obj", vertexLayout, 1.0f, vulkanDevice, queue);
		boardbottom.aniType = ANI_STATIC;
		boardbottom.position = glm::vec3(0, 0, 0);
		//models_list.push_back(boardbottom);

		objectSphereDim = 1.0f;
		numThreads = models_list.size();

		/// BVH SETUP
		/*
		Model sphere;
		sphere.aniType = ANI_STATIC;
		sphere.loadFromFile(getAssetPath() + "models/sphere.obj", vertexLayout, 0.03f, vulkanDevice, queue);
		std::string mocap_path = getAssetPath() + "bvh/wave.bvh";
		sphere.mocaps.Load(mocap_path.c_str());
		models_list.push_back(sphere);

		Model cyl;
		cyl.loadFromFile(getAssetPath() + "models/cylinder.obj", vertexLayout, 0.03f, vulkanDevice, queue);
		models_list.push_back(cyl);
		
		objectSphereDim = 1.0f;
		numThreads = 1;
		*/
		

		displaySkybox = false;
	}

	void setupPipelineLayout() {
		VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo =
			initializers::pipelineLayoutCreateInfo(nullptr, 0);

		// Push constants for model matrices
		VkPushConstantRange pushConstantRange =
			initializers::pushConstantRange(
				VK_SHADER_STAGE_VERTEX_BIT,
				sizeof(ThreadPushConstantBlock),
				0);

		// Push constant ranges are part of the pipeline layout
		pPipelineLayoutCreateInfo.pushConstantRangeCount = 1;
		pPipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;

		tools::VK_VERIFY_SUCCESS(vkCreatePipelineLayout(device, &pPipelineLayoutCreateInfo, nullptr, &pipelineLayout));
	}

	void preparePipelines() {
		/**/
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState =
			initializers::pipelineInputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, 0, VK_FALSE);

		VkPipelineRasterizationStateCreateInfo rasterizationState =
			initializers::pipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL, VK_CULL_MODE_BACK_BIT, VK_FRONT_FACE_CLOCKWISE, 0);

		VkPipelineColorBlendAttachmentState blendAttachmentState =
			initializers::pipelineColorBlendAttachmentState(0xf, VK_FALSE);

		VkPipelineColorBlendStateCreateInfo colorBlendState =
			initializers::pipelineColorBlendStateCreateInfo(1, &blendAttachmentState);

		VkPipelineDepthStencilStateCreateInfo depthStencilState =
			initializers::pipelineDepthStencilStateCreateInfo(VK_TRUE, VK_TRUE, VK_COMPARE_OP_LESS_OR_EQUAL);

		VkPipelineViewportStateCreateInfo viewportState =
			initializers::pipelineViewportStateCreateInfo(1, 1, 0);

		VkPipelineMultisampleStateCreateInfo multisampleState =
			initializers::pipelineMultisampleStateCreateInfo(VK_SAMPLE_COUNT_1_BIT, 0);

		std::vector<VkDynamicState> dynamicStateEnables = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamicState =
			initializers::pipelineDynamicStateCreateInfo(dynamicStateEnables.data(), dynamicStateEnables.size(), 0);

		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

		VkGraphicsPipelineCreateInfo pipelineCI = initializers::pipelineCreateInfo(pipelineLayout, renderPass, 0);
		pipelineCI.pInputAssemblyState = &inputAssemblyState;
		pipelineCI.pRasterizationState = &rasterizationState;
		pipelineCI.pColorBlendState = &colorBlendState;
		pipelineCI.pMultisampleState = &multisampleState;
		pipelineCI.pViewportState = &viewportState;
		pipelineCI.pDepthStencilState = &depthStencilState;
		pipelineCI.pDynamicState = &dynamicState;
		pipelineCI.stageCount = shaderStages.size();
		pipelineCI.pStages = shaderStages.data();

		// Vertex bindings and attributes
		const std::vector<VkVertexInputBindingDescription> vertexInputBindings = {
			initializers::vertexInputBindingDescription(0, vertexLayout.stride(), VK_VERTEX_INPUT_RATE_VERTEX),
		};

		const std::vector<VkVertexInputAttributeDescription> vertexInputAttributes = {
			initializers::vertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0),					// Location 0: Position			
			initializers::vertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 3),	// Location 1: Normal
			initializers::vertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 6),	// Location 2: Color
		};
		VkPipelineVertexInputStateCreateInfo vertexInputStateCI = initializers::pipelineVertexInputStateCreateInfo();
		vertexInputStateCI.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindings.size());
		vertexInputStateCI.pVertexBindingDescriptions = vertexInputBindings.data();
		vertexInputStateCI.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributes.size());
		vertexInputStateCI.pVertexAttributeDescriptions = vertexInputAttributes.data();

		pipelineCI.pVertexInputState = &vertexInputStateCI;

		// Object rendering pipeline
		shaderStages[0] = loadShader(getAssetPath() + "shaders/raster/phong.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
		shaderStages[1] = loadShader(getAssetPath() + "shaders/raster/phong.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
		tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCI, nullptr, &pipelines.phong));

		// Star sphere rendering pipeline
		rasterizationState.cullMode = VK_CULL_MODE_FRONT_BIT;
		depthStencilState.depthWriteEnable = VK_FALSE;
		shaderStages[0] = loadShader(getAssetPath() + "shaders/raster/starsphere.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
		shaderStages[1] = loadShader(getAssetPath() + "shaders/raster/starsphere.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
		tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCI, nullptr, &pipelines.starsphere));
	}

	void updateMatrices() {
		matrices.projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 256.0f);
		matrices.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zoom));
		matrices.view = glm::rotate(matrices.view, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrices.view = glm::rotate(matrices.view, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrices.view = glm::rotate(matrices.view, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		frustum.update(matrices.projection * matrices.view);
	}

	void draw() {
		// Wait for fence to signal that all command buffers are ready
		VkResult fenceRes;
		do {
			fenceRes = vkWaitForFences(device, 1, &renderFence, VK_TRUE, 100000000);
		} while (fenceRes == VK_TIMEOUT);
		tools::VK_VERIFY_SUCCESS(fenceRes);
		vkResetFences(device, 1, &renderFence);

		VulkanRenderer::prepareFrame();

		updateCommandBuffers(frameBuffers[currentBuffer]);

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &primaryCommandBuffer;

		tools::VK_VERIFY_SUCCESS(vkQueueSubmit(queue, 1, &submitInfo, renderFence));

		VulkanRenderer::submitFrame();
	}

	void prepare() {
		VulkanRenderer::prepare();
		// Create a fence for synchronization
		VkFenceCreateInfo fenceCreateInfo = initializers::fenceCreateInfo(VK_FENCE_CREATE_SIGNALED_BIT);
		vkCreateFence(device, &fenceCreateInfo, nullptr, &renderFence);
		loadAssets();
		setupPipelineLayout();
		preparePipelines();
		prepareMultiThreadedRenderer();
		updateMatrices();
		prepared = true;
	}

	virtual void render() {
		if (!prepared)
			return;
		draw();
	}

	virtual void viewChanged() {
		updateMatrices();
	}

	virtual void OnUpdateUIOverlay(UIOverlay* overlay) {
		if (overlay->header("Statistics")) {
			overlay->text("Active threads: %d", numThreads);
		}
		if (overlay->header("Settings")) {
			overlay->checkBox("Skybox", &displaySkybox);
		}
	}
};










/**

VULKAN RAY TRACER SEGMENT

**/


struct AccelerationStructure {
	VkDeviceMemory memory;
	VkAccelerationStructureNV accelerationStructure;
	uint64_t handle;
};

// Ray tracing geometry instance
struct GeometryInstance {
	glm::mat3x4 transform;
	uint32_t instanceId : 24;
	uint32_t mask : 8;
	uint32_t instanceOffset : 24;
	uint32_t flags : 8;
	uint64_t accelerationStructureHandle;
};

// Indices for the different ray tracing groups used in this example
#define INDEX_RAYGEN 0
#define INDEX_MISS 1
//#define INDEX_CLOSEST_HIT 2
//#define NUM_SHADER_GROUPS 3
#define INDEX_SHADOW_MISS 2
#define INDEX_CLOSEST_HIT 3
#define INDEX_SHADOW_HIT 4
#define NUM_SHADER_GROUPS 5
/* Shadows Support
*/

typedef struct VkRayTracingShaderGroupCreateInfoNV {
	VkStructureType                  sType;
	const void* pNext;
	VkRayTracingShaderGroupTypeNV    type;
	uint32_t                         generalShader;
	uint32_t                         closestHitShader;
	uint32_t                         anyHitShader;
	uint32_t                         intersectionShader;
} VkRayTracingShaderGroupCreateInfoNV;

typedef struct VkRayTracingPipelineCreateInfoNV {
	VkStructureType                               sType;
	const void* pNext;
	VkPipelineCreateFlags                         flags;
	uint32_t                                      stageCount;
	const VkPipelineShaderStageCreateInfo* pStages;
	uint32_t                                      groupCount;
	const VkRayTracingShaderGroupCreateInfoNV* pGroups;
	uint32_t                                      maxRecursionDepth;
	VkPipelineLayout                              layout;
	VkPipeline                                    basePipelineHandle;
	int32_t                                       basePipelineIndex;
} VkRayTracingPipelineCreateInfoNV;

typedef struct VkGeometryTrianglesNV {
	VkStructureType    sType;
	const void* pNext;
	VkBuffer           vertexData;
	VkDeviceSize       vertexOffset;
	uint32_t           vertexCount;
	VkDeviceSize       vertexStride;
	VkFormat           vertexFormat;
	VkBuffer           indexData;
	VkDeviceSize       indexOffset;
	uint32_t           indexCount;
	VkIndexType        indexType;
	VkBuffer           transformData;
	VkDeviceSize       transformOffset;
} VkGeometryTrianglesNV;

typedef struct VkGeometryAABBNV {
	VkStructureType    sType;
	const void* pNext;
	VkBuffer           aabbData;
	uint32_t           numAABBs;
	uint32_t           stride;
	VkDeviceSize       offset;
} VkGeometryAABBNV;

typedef struct VkGeometryDataNV {
	VkGeometryTrianglesNV    triangles;
	VkGeometryAABBNV         aabbs;
} VkGeometryDataNV;

typedef struct VkGeometryNV {
	VkStructureType      sType;
	const void* pNext;
	VkGeometryTypeNV     geometryType;
	VkGeometryDataNV     geometry;
	VkGeometryFlagsNV    flags;
} VkGeometryNV;

typedef struct VkAccelerationStructureInfoNV {
	VkStructureType                        sType;
	const void* pNext;
	VkAccelerationStructureTypeNV          type;
	VkBuildAccelerationStructureFlagsNV    flags;
	uint32_t                               instanceCount;
	uint32_t                               geometryCount;
	const VkGeometryNV* pGeometries;
} VkAccelerationStructureInfoNV;

typedef struct VkAccelerationStructureCreateInfoNV {
	VkStructureType                  sType;
	const void* pNext;
	VkDeviceSize                     compactedSize;
	VkAccelerationStructureInfoNV    info;
} VkAccelerationStructureCreateInfoNV;

typedef struct VkBindAccelerationStructureMemoryInfoNV {
	VkStructureType              sType;
	const void* pNext;
	VkAccelerationStructureNV    accelerationStructure;
	VkDeviceMemory               memory;
	VkDeviceSize                 memoryOffset;
	uint32_t                     deviceIndexCount;
	const uint32_t* pDeviceIndices;
} VkBindAccelerationStructureMemoryInfoNV;

typedef struct VkWriteDescriptorSetAccelerationStructureNV {
	VkStructureType                     sType;
	const void* pNext;
	uint32_t                            accelerationStructureCount;
	const VkAccelerationStructureNV* pAccelerationStructures;
} VkWriteDescriptorSetAccelerationStructureNV;

typedef struct VkAccelerationStructureMemoryRequirementsInfoNV {
	VkStructureType                                    sType;
	const void* pNext;
	VkAccelerationStructureMemoryRequirementsTypeNV    type;
	VkAccelerationStructureNV                          accelerationStructure;
} VkAccelerationStructureMemoryRequirementsInfoNV;

typedef struct VkPhysicalDeviceRayTracingPropertiesNV {
	VkStructureType    sType;
	void* pNext;
	uint32_t           shaderGroupHandleSize;
	uint32_t           maxRecursionDepth;
	uint32_t           maxShaderGroupStride;
	uint32_t           shaderGroupBaseAlignment;
	uint64_t           maxGeometryCount;
	uint64_t           maxInstanceCount;
	uint64_t           maxTriangleCount;
	uint32_t           maxDescriptorSetAccelerationStructures;
} VkPhysicalDeviceRayTracingPropertiesNV;

typedef VkResult(VKAPI_PTR* PFN_vkCreateAccelerationStructureNV)(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure);
typedef void (VKAPI_PTR* PFN_vkDestroyAccelerationStructureNV)(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator);
typedef void (VKAPI_PTR* PFN_vkGetAccelerationStructureMemoryRequirementsNV)(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements);
typedef VkResult(VKAPI_PTR* PFN_vkBindAccelerationStructureMemoryNV)(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos);
typedef void (VKAPI_PTR* PFN_vkCmdBuildAccelerationStructureNV)(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset);
typedef void (VKAPI_PTR* PFN_vkCmdCopyAccelerationStructureNV)(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeNV mode);
typedef void (VKAPI_PTR* PFN_vkCmdTraceRaysNV)(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth);
typedef VkResult(VKAPI_PTR* PFN_vkCreateRayTracingPipelinesNV)(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
typedef VkResult(VKAPI_PTR* PFN_vkGetRayTracingShaderGroupHandlesNV)(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
typedef VkResult(VKAPI_PTR* PFN_vkGetAccelerationStructureHandleNV)(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData);
typedef void (VKAPI_PTR* PFN_vkCmdWriteAccelerationStructuresPropertiesNV)(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
typedef VkResult(VKAPI_PTR* PFN_vkCompileDeferredNV)(VkDevice device, VkPipeline pipeline, uint32_t shader);


class VulkanRayTracer : public VulkanRenderer {
public:
	PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
	PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
	PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
	PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
	PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
	PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
	PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
	PFN_vkGetRayTracingShaderGroupHandlesNV vkGetRayTracingShaderGroupHandlesNV;
	PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;

	VkPhysicalDeviceRayTracingPropertiesNV rayTracingProperties{};

	AccelerationStructure bottomLevelAS;
	AccelerationStructure topLevelAS;

	Buffer shaderBindingTable;

	struct StorageImage {
		VkDeviceMemory memory;
		VkImage image;
		VkImageView view;
		VkFormat format;
	} storageImage;

	struct UniformData {
		glm::mat4 viewInverse;
		glm::mat4 projInverse;
		glm::vec4 lightPos;
	} uniformData;
	Buffer ubo;

	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
	VkDescriptorSet descriptorSet;
	VkDescriptorSetLayout descriptorSetLayout;

	VertexLayout vertexLayout = VertexLayout({
		VERTEX_COMPONENT_POSITION,
		VERTEX_COMPONENT_NORMAL,
		VERTEX_COMPONENT_COLOR,
		VERTEX_COMPONENT_UV,
		VERTEX_COMPONENT_DUMMY_FLOAT
		});
	Model scene;

	VulkanRayTracer() : VulkanRenderer() {
		title = "Ray Tracing";
		settings.overlay = false;
		timerSpeed *= 0.001f;
		camera.type = Camera::CameraType::firstperson;
		camera.setPerspective(60.0f, (float)width / (float)height, 0.1f, 512.0f);
		camera.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
		camera.setTranslation(glm::vec3(0.0f, 0.0f, -1.5f));
		// Enable instance and device extensions required to use VK_NV_ray_tracing
		enabledInstanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
		enabledDeviceExtensions.push_back(VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME);
		enabledDeviceExtensions.push_back(VK_NV_RAY_TRACING_EXTENSION_NAME);
	}

	~VulkanRayTracer() {
		vkDestroyPipeline(device, pipeline, nullptr);
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
		vkDestroyImageView(device, storageImage.view, nullptr);
		vkDestroyImage(device, storageImage.image, nullptr);
		vkFreeMemory(device, storageImage.memory, nullptr);
		vkFreeMemory(device, bottomLevelAS.memory, nullptr);
		vkFreeMemory(device, topLevelAS.memory, nullptr);
		vkDestroyAccelerationStructureNV(device, bottomLevelAS.accelerationStructure, nullptr);
		vkDestroyAccelerationStructureNV(device, topLevelAS.accelerationStructure, nullptr);
		shaderBindingTable.destroy();
		ubo.destroy();
		scene.destroy();
	}

	/*
		Set up a storage image that the ray generation shader will be writing to
	*/
	void createStorageImage() {
		VkImageCreateInfo image = initializers::imageCreateInfo();
		image.imageType = VK_IMAGE_TYPE_2D;
		image.format = swapChain.colorFormat;
		image.extent.width = width;
		image.extent.height = height;
		image.extent.depth = 1;
		image.mipLevels = 1;
		image.arrayLayers = 1;
		image.samples = VK_SAMPLE_COUNT_1_BIT;
		image.tiling = VK_IMAGE_TILING_OPTIMAL;
		image.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
		image.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		tools::VK_VERIFY_SUCCESS(vkCreateImage(device, &image, nullptr, &storageImage.image));

		VkMemoryRequirements memReqs;
		vkGetImageMemoryRequirements(device, storageImage.image, &memReqs);
		VkMemoryAllocateInfo memoryAllocateInfo = initializers::memoryAllocateInfo();
		memoryAllocateInfo.allocationSize = memReqs.size;
		memoryAllocateInfo.memoryTypeIndex = vulkanDevice->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &storageImage.memory));
		tools::VK_VERIFY_SUCCESS(vkBindImageMemory(device, storageImage.image, storageImage.memory, 0));

		VkImageViewCreateInfo colorImageView = initializers::imageViewCreateInfo();
		colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
		colorImageView.format = swapChain.colorFormat;
		colorImageView.subresourceRange = {};
		colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		colorImageView.subresourceRange.baseMipLevel = 0;
		colorImageView.subresourceRange.levelCount = 1;
		colorImageView.subresourceRange.baseArrayLayer = 0;
		colorImageView.subresourceRange.layerCount = 1;
		colorImageView.image = storageImage.image;
		tools::VK_VERIFY_SUCCESS(vkCreateImageView(device, &colorImageView, nullptr, &storageImage.view));

		VkCommandBuffer cmdBuffer = vulkanDevice->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
		tools::setImageLayout(cmdBuffer, storageImage.image,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_GENERAL,
			{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
		vulkanDevice->flushCommandBuffer(cmdBuffer, queue);
	}

	/*
		The bottom level acceleration structure contains the scene's geometry (vertices, triangles)
	*/
	void createBottomLevelAccelerationStructure(const VkGeometryNV* geometries) {
		VkAccelerationStructureInfoNV accelerationStructureInfo{};
		accelerationStructureInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
		accelerationStructureInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV;
		accelerationStructureInfo.instanceCount = 0;
		accelerationStructureInfo.geometryCount = 1;
		accelerationStructureInfo.pGeometries = geometries;

		VkAccelerationStructureCreateInfoNV accelerationStructureCI{};
		accelerationStructureCI.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
		accelerationStructureCI.info = accelerationStructureInfo;
		tools::VK_VERIFY_SUCCESS(vkCreateAccelerationStructureNV(device, &accelerationStructureCI, nullptr, &bottomLevelAS.accelerationStructure));

		VkAccelerationStructureMemoryRequirementsInfoNV memoryRequirementsInfo{};
		memoryRequirementsInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
		memoryRequirementsInfo.accelerationStructure = bottomLevelAS.accelerationStructure;

		VkMemoryRequirements2 memoryRequirements2{};
		vkGetAccelerationStructureMemoryRequirementsNV(device, &memoryRequirementsInfo, &memoryRequirements2);

		VkMemoryAllocateInfo memoryAllocateInfo = initializers::memoryAllocateInfo();
		memoryAllocateInfo.allocationSize = memoryRequirements2.memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = vulkanDevice->getMemoryType(memoryRequirements2.memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &bottomLevelAS.memory));

		VkBindAccelerationStructureMemoryInfoNV accelerationStructureMemoryInfo{};
		accelerationStructureMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
		accelerationStructureMemoryInfo.accelerationStructure = bottomLevelAS.accelerationStructure;
		accelerationStructureMemoryInfo.memory = bottomLevelAS.memory;
		tools::VK_VERIFY_SUCCESS(vkBindAccelerationStructureMemoryNV(device, 1, &accelerationStructureMemoryInfo));

		tools::VK_VERIFY_SUCCESS(vkGetAccelerationStructureHandleNV(device, bottomLevelAS.accelerationStructure, sizeof(uint64_t), &bottomLevelAS.handle));
	}

	/*
		The top level acceleration structure contains the scene's object instances
	*/
	void createTopLevelAccelerationStructure() {
		VkAccelerationStructureInfoNV accelerationStructureInfo{};
		accelerationStructureInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
		accelerationStructureInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV;
		accelerationStructureInfo.instanceCount = 1;
		accelerationStructureInfo.geometryCount = 0;

		VkAccelerationStructureCreateInfoNV accelerationStructureCI{};
		accelerationStructureCI.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV;
		accelerationStructureCI.info = accelerationStructureInfo;
		tools::VK_VERIFY_SUCCESS(vkCreateAccelerationStructureNV(device, &accelerationStructureCI, nullptr, &topLevelAS.accelerationStructure));

		VkAccelerationStructureMemoryRequirementsInfoNV memoryRequirementsInfo{};
		memoryRequirementsInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
		memoryRequirementsInfo.accelerationStructure = topLevelAS.accelerationStructure;

		VkMemoryRequirements2 memoryRequirements2{};
		vkGetAccelerationStructureMemoryRequirementsNV(device, &memoryRequirementsInfo, &memoryRequirements2);

		VkMemoryAllocateInfo memoryAllocateInfo = initializers::memoryAllocateInfo();
		memoryAllocateInfo.allocationSize = memoryRequirements2.memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = vulkanDevice->getMemoryType(memoryRequirements2.memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		tools::VK_VERIFY_SUCCESS(vkAllocateMemory(device, &memoryAllocateInfo, nullptr, &topLevelAS.memory));

		VkBindAccelerationStructureMemoryInfoNV accelerationStructureMemoryInfo{};
		accelerationStructureMemoryInfo.sType = VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV;
		accelerationStructureMemoryInfo.accelerationStructure = topLevelAS.accelerationStructure;
		accelerationStructureMemoryInfo.memory = topLevelAS.memory;
		tools::VK_VERIFY_SUCCESS(vkBindAccelerationStructureMemoryNV(device, 1, &accelerationStructureMemoryInfo));

		tools::VK_VERIFY_SUCCESS(vkGetAccelerationStructureHandleNV(device, topLevelAS.accelerationStructure, sizeof(uint64_t), &topLevelAS.handle));
	}

	void createScene() {
		ModelCreateInfo modelCI{};
		modelCI.scale = glm::vec3(0.25f);
		modelCI.memoryPropertyFlags = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		scene.loadFromFile(getAssetPath() + "models/sampleroom2.dae", vertexLayout, &modelCI, vulkanDevice, queue);

		// BLAS
		VkGeometryNV geometry{};
		geometry.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
		geometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_NV;
		geometry.geometry.triangles.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
		geometry.geometry.triangles.vertexData = scene.vertices.buffer;
		geometry.geometry.triangles.vertexOffset = 0;
		geometry.geometry.triangles.vertexCount = static_cast<uint32_t>(scene.vertexCount);
		geometry.geometry.triangles.vertexStride = vertexLayout.stride();
		geometry.geometry.triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;
		geometry.geometry.triangles.indexData = scene.indices.buffer;
		geometry.geometry.triangles.indexOffset = 0;
		geometry.geometry.triangles.indexCount = scene.indexCount;
		geometry.geometry.triangles.indexType = VK_INDEX_TYPE_UINT32;
		geometry.geometry.triangles.transformData = VK_NULL_HANDLE;
		geometry.geometry.triangles.transformOffset = 0;
		geometry.geometry.aabbs = {};
		geometry.geometry.aabbs.sType = { VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV };
		geometry.flags = VK_GEOMETRY_OPAQUE_BIT_NV;

		createBottomLevelAccelerationStructure(&geometry);

		// TLAS
		Buffer instanceBuffer;

		glm::mat3x4 transform = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
		};

		std::array<GeometryInstance, 2> geometryInstances{};
		// hit and miss shaders
		geometryInstances[0].transform = transform;
		geometryInstances[0].instanceId = 0;
		geometryInstances[0].mask = 0xff;
		geometryInstances[0].instanceOffset = 0;
		geometryInstances[0].flags = VK_GEOMETRY_INSTANCE_TRIANGLE_CULL_DISABLE_BIT_NV;
		geometryInstances[0].accelerationStructureHandle = bottomLevelAS.handle;
		// shadow hit and miss shaders
		geometryInstances[1].transform = transform;
		geometryInstances[1].instanceId = 1;
		geometryInstances[1].mask = 0xff;
		geometryInstances[1].instanceOffset = 2;
		geometryInstances[1].flags = VK_GEOMETRY_INSTANCE_TRIANGLE_CULL_DISABLE_BIT_NV;
		geometryInstances[1].accelerationStructureHandle = bottomLevelAS.handle;

		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&instanceBuffer,
			sizeof(GeometryInstance) * geometryInstances.size(),
			geometryInstances.data()));

		createTopLevelAccelerationStructure();

		/*
			Acceleration Structure
		*/

		VkAccelerationStructureMemoryRequirementsInfoNV memoryRequirementsInfo{};
		memoryRequirementsInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
		memoryRequirementsInfo.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV;

		VkMemoryRequirements2 memReqBottomLevelAS;
		memoryRequirementsInfo.accelerationStructure = bottomLevelAS.accelerationStructure;
		vkGetAccelerationStructureMemoryRequirementsNV(device, &memoryRequirementsInfo, &memReqBottomLevelAS);

		VkMemoryRequirements2 memReqTopLevelAS;
		memoryRequirementsInfo.accelerationStructure = topLevelAS.accelerationStructure;
		vkGetAccelerationStructureMemoryRequirementsNV(device, &memoryRequirementsInfo, &memReqTopLevelAS);

		const VkDeviceSize scratchBufferSize = std::max(memReqBottomLevelAS.memoryRequirements.size, memReqTopLevelAS.memoryRequirements.size);

		Buffer scratchBuffer;
		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&scratchBuffer,
			scratchBufferSize));

		VkCommandBuffer cmdBuffer = vulkanDevice->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

		/*
			More BLAS
		*/
		VkAccelerationStructureInfoNV buildInfo{};
		buildInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV;
		buildInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV;
		buildInfo.geometryCount = 1;
		buildInfo.pGeometries = &geometry;

		vkCmdBuildAccelerationStructureNV(
			cmdBuffer,
			&buildInfo,
			VK_NULL_HANDLE,
			0,
			VK_FALSE,
			bottomLevelAS.accelerationStructure,
			VK_NULL_HANDLE,
			scratchBuffer.buffer,
			0);

		VkMemoryBarrier memoryBarrier = initializers::memoryBarrier();
		memoryBarrier.srcAccessMask = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV | VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV;
		memoryBarrier.dstAccessMask = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV | VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV;
		vkCmdPipelineBarrier(cmdBuffer, VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV, VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV, 0, 1, &memoryBarrier, 0, 0, 0, 0);

		/*
			More TLAS
		*/
		buildInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV;
		buildInfo.pGeometries = 0;
		buildInfo.geometryCount = 0;
		buildInfo.instanceCount = 1;

		vkCmdBuildAccelerationStructureNV(
			cmdBuffer,
			&buildInfo,
			instanceBuffer.buffer,
			0,
			VK_FALSE,
			topLevelAS.accelerationStructure,
			VK_NULL_HANDLE,
			scratchBuffer.buffer,
			0);

		// FINALLY, we're done building
		vkCmdPipelineBarrier(cmdBuffer, VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV, VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV, 0, 1, &memoryBarrier, 0, 0, 0, 0);

		vulkanDevice->flushCommandBuffer(cmdBuffer, queue);

		scratchBuffer.destroy();
		instanceBuffer.destroy();
	}

	VkDeviceSize copyShaderIdentifier(uint8_t* data, const uint8_t* shaderHandleStorage, uint32_t groupIndex) {
		const uint32_t shaderGroupHandleSize = rayTracingProperties.shaderGroupHandleSize;
		memcpy(data, shaderHandleStorage + groupIndex * shaderGroupHandleSize, shaderGroupHandleSize);
		data += shaderGroupHandleSize;
		return shaderGroupHandleSize;
	}

	void createShaderBindingTable() {
		// Create buffer for the shader binding table
		const uint32_t sbtSize = rayTracingProperties.shaderGroupHandleSize * NUM_SHADER_GROUPS;
		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			&shaderBindingTable,
			sbtSize));
		shaderBindingTable.map();

		auto shaderHandleStorage = new uint8_t[sbtSize];
		// Get shader identifiers
		tools::VK_VERIFY_SUCCESS(vkGetRayTracingShaderGroupHandlesNV(device, pipeline, 0, NUM_SHADER_GROUPS, sbtSize, shaderHandleStorage));
		auto* data = static_cast<uint8_t*>(shaderBindingTable.mapped);
		// Copy the shader identifiers to the shader binding table
		VkDeviceSize offset = 0;
		data += copyShaderIdentifier(data, shaderHandleStorage, INDEX_RAYGEN);
		data += copyShaderIdentifier(data, shaderHandleStorage, INDEX_MISS);
		data += copyShaderIdentifier(data, shaderHandleStorage, INDEX_SHADOW_MISS);
		data += copyShaderIdentifier(data, shaderHandleStorage, INDEX_CLOSEST_HIT);
		data += copyShaderIdentifier(data, shaderHandleStorage, INDEX_SHADOW_HIT);
		shaderBindingTable.unmap();
	}

	void createDescriptorSets() {
		std::vector<VkDescriptorPoolSize> poolSizes = {
			{ VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV, 1 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2 }
		};
		VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = initializers::descriptorPoolCreateInfo(poolSizes, 1);
		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

		VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = initializers::descriptorSetAllocateInfo(descriptorPool, &descriptorSetLayout, 1);
		tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet));

		VkWriteDescriptorSetAccelerationStructureNV descriptorAccelerationStructureInfo{};
		descriptorAccelerationStructureInfo.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV;
		descriptorAccelerationStructureInfo.accelerationStructureCount = 1;
		descriptorAccelerationStructureInfo.pAccelerationStructures = &topLevelAS.accelerationStructure;

		VkWriteDescriptorSet accelerationStructureWrite{};
		accelerationStructureWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		// The specialized acceleration structure descriptor has to be chained
		accelerationStructureWrite.pNext = &descriptorAccelerationStructureInfo;
		accelerationStructureWrite.dstSet = descriptorSet;
		accelerationStructureWrite.dstBinding = 0;
		accelerationStructureWrite.descriptorCount = 1;
		accelerationStructureWrite.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;

		VkDescriptorImageInfo storageImageDescriptor{};
		storageImageDescriptor.imageView = storageImage.view;
		storageImageDescriptor.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

		VkDescriptorBufferInfo vertexBufferDescriptor{};
		vertexBufferDescriptor.buffer = scene.vertices.buffer;
		vertexBufferDescriptor.range = VK_WHOLE_SIZE;

		VkDescriptorBufferInfo indexBufferDescriptor{};
		indexBufferDescriptor.buffer = scene.indices.buffer;
		indexBufferDescriptor.range = VK_WHOLE_SIZE;

		VkWriteDescriptorSet resultImageWrite = initializers::writeDescriptorSet(descriptorSet, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1, &storageImageDescriptor);
		VkWriteDescriptorSet uniformBufferWrite = initializers::writeDescriptorSet(descriptorSet, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2, &ubo.descriptor);
		VkWriteDescriptorSet vertexBufferWrite = initializers::writeDescriptorSet(descriptorSet, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3, &vertexBufferDescriptor);
		VkWriteDescriptorSet indexBufferWrite = initializers::writeDescriptorSet(descriptorSet, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4, &indexBufferDescriptor);

		std::vector<VkWriteDescriptorSet> writeDescriptorSets = {
			accelerationStructureWrite,
			resultImageWrite,
			uniformBufferWrite,
			vertexBufferWrite,
			indexBufferWrite
		};
		vkUpdateDescriptorSets(device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, VK_NULL_HANDLE);
	}

	void createRayTracingPipeline() {
		VkDescriptorSetLayoutBinding accelerationStructureLayoutBinding{};
		accelerationStructureLayoutBinding.binding = 0;
		accelerationStructureLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
		accelerationStructureLayoutBinding.descriptorCount = 1;
		accelerationStructureLayoutBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_NV | VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;

		VkDescriptorSetLayoutBinding resultImageLayoutBinding{};
		resultImageLayoutBinding.binding = 1;
		resultImageLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		resultImageLayoutBinding.descriptorCount = 1;
		resultImageLayoutBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_NV;

		VkDescriptorSetLayoutBinding uniformBufferBinding{};
		uniformBufferBinding.binding = 2;
		uniformBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uniformBufferBinding.descriptorCount = 1;
		uniformBufferBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_NV | VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;

		VkDescriptorSetLayoutBinding vertexBufferBinding{};
		vertexBufferBinding.binding = 3;
		vertexBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		vertexBufferBinding.descriptorCount = 1;
		vertexBufferBinding.stageFlags = VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;

		VkDescriptorSetLayoutBinding indexBufferBinding{};
		indexBufferBinding.binding = 4;
		indexBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		indexBufferBinding.descriptorCount = 1;
		indexBufferBinding.stageFlags = VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;

		std::vector<VkDescriptorSetLayoutBinding> bindings({
			accelerationStructureLayoutBinding,
			resultImageLayoutBinding,
			uniformBufferBinding,
			vertexBufferBinding,
			indexBufferBinding
			});

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();
		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout));

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = 1;
		pipelineLayoutCreateInfo.pSetLayouts = &descriptorSetLayout;

		tools::VK_VERIFY_SUCCESS(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

		const uint32_t shaderIndexRaygen = 0;
		const uint32_t shaderIndexMiss = 1;
		const uint32_t shaderIndexShadowMiss = 2;
		const uint32_t shaderIndexClosestHit = 3;

		std::array<VkPipelineShaderStageCreateInfo, 4> shaderStages;
		shaderStages[shaderIndexRaygen] = loadShader(getAssetPath() + "shaders/rtx/raygen.rgen.spv", VK_SHADER_STAGE_RAYGEN_BIT_NV);
		shaderStages[shaderIndexMiss] = loadShader(getAssetPath() + "shaders/rtx/miss.rmiss.spv", VK_SHADER_STAGE_MISS_BIT_NV);
		shaderStages[shaderIndexShadowMiss] = loadShader(getAssetPath() + "shaders/rtx/shadow.rmiss.spv", VK_SHADER_STAGE_MISS_BIT_NV);
		shaderStages[shaderIndexClosestHit] = loadShader(getAssetPath() + "shaders/rtx/closesthit.rchit.spv", VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV);

		std::array<VkRayTracingShaderGroupCreateInfoNV, NUM_SHADER_GROUPS> groups{};
		for (auto& group : groups) {
			group.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV;
			group.generalShader = VK_SHADER_UNUSED_NV;
			group.closestHitShader = VK_SHADER_UNUSED_NV;
			group.anyHitShader = VK_SHADER_UNUSED_NV;
			group.intersectionShader = VK_SHADER_UNUSED_NV;
		}

		// Ray generation shader group
		groups[INDEX_RAYGEN].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV;
		groups[INDEX_RAYGEN].generalShader = shaderIndexRaygen;
		// Scene miss shader group
		groups[INDEX_MISS].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV;
		groups[INDEX_MISS].generalShader = shaderIndexMiss;
		// Shadow miss shader group 
		groups[INDEX_SHADOW_MISS].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV;
		groups[INDEX_SHADOW_MISS].generalShader = shaderIndexShadowMiss;
		// Scene closest hit shader group
		groups[INDEX_CLOSEST_HIT].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV;
		groups[INDEX_CLOSEST_HIT].generalShader = VK_SHADER_UNUSED_NV;
		groups[INDEX_CLOSEST_HIT].closestHitShader = shaderIndexClosestHit;
		// Shadow closest hit shader group
		groups[INDEX_SHADOW_HIT].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV;
		groups[INDEX_SHADOW_HIT].generalShader = VK_SHADER_UNUSED_NV;
		// Reuse shadow miss shader
		groups[INDEX_SHADOW_HIT].closestHitShader = shaderIndexShadowMiss;

		VkRayTracingPipelineCreateInfoNV rayPipelineInfo{};
		rayPipelineInfo.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV;
		rayPipelineInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
		rayPipelineInfo.pStages = shaderStages.data();
		rayPipelineInfo.groupCount = static_cast<uint32_t>(groups.size());
		rayPipelineInfo.pGroups = groups.data();
		rayPipelineInfo.maxRecursionDepth = 2;
		rayPipelineInfo.layout = pipelineLayout;
		tools::VK_VERIFY_SUCCESS(vkCreateRayTracingPipelinesNV(device, VK_NULL_HANDLE, 1, &rayPipelineInfo, nullptr, &pipeline));
	}

	void createUniformBuffer() {
		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&ubo,
			sizeof(uniformData),
			&uniformData));
		tools::VK_VERIFY_SUCCESS(ubo.map());

		updateUniformBuffers();
	}

	void buildCommandBuffers() {
		VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();

		VkImageSubresourceRange subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

		for (int32_t i = 0; i < drawCmdBuffers.size(); ++i) {
			tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(drawCmdBuffers[i], &cmdBufInfo));

			vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_RAY_TRACING_NV, pipeline);
			vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_RAY_TRACING_NV, pipelineLayout, 0, 1, &descriptorSet, 0, 0);

			// Calculate shader binding offsets, which is pretty straight forward in our example 
			VkDeviceSize bindingOffsetRayGenShader = rayTracingProperties.shaderGroupHandleSize * INDEX_RAYGEN;
			VkDeviceSize bindingOffsetMissShader = rayTracingProperties.shaderGroupHandleSize * INDEX_MISS;
			VkDeviceSize bindingOffsetHitShader = rayTracingProperties.shaderGroupHandleSize * INDEX_CLOSEST_HIT;
			VkDeviceSize bindingStride = rayTracingProperties.shaderGroupHandleSize;

			vkCmdTraceRaysNV(drawCmdBuffers[i],
				shaderBindingTable.buffer, bindingOffsetRayGenShader,
				shaderBindingTable.buffer, bindingOffsetMissShader, bindingStride,
				shaderBindingTable.buffer, bindingOffsetHitShader, bindingStride,
				VK_NULL_HANDLE, 0, 0,
				width, height, 1);


			// Prepare current swapchain image as transfer destination
			tools::setImageLayout(
				drawCmdBuffers[i],
				swapChain.images[i],
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				subresourceRange);

			// Prepare ray tracing output image as transfer source
			tools::setImageLayout(
				drawCmdBuffers[i],
				storageImage.image,
				VK_IMAGE_LAYOUT_GENERAL,
				VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				subresourceRange);

			VkImageCopy copyRegion{};
			copyRegion.srcSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
			copyRegion.srcOffset = { 0, 0, 0 };
			copyRegion.dstSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
			copyRegion.dstOffset = { 0, 0, 0 };
			copyRegion.extent = { width, height, 1 };
			vkCmdCopyImage(drawCmdBuffers[i], storageImage.image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, swapChain.images[i], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

			// Transition swap chain image back for presentation
			tools::setImageLayout(
				drawCmdBuffers[i],
				swapChain.images[i],
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
				subresourceRange);

			// Transition ray tracing output image back to general layout
			tools::setImageLayout(
				drawCmdBuffers[i],
				storageImage.image,
				VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				VK_IMAGE_LAYOUT_GENERAL,
				subresourceRange);

			tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(drawCmdBuffers[i]));
		}
	}

	void updateUniformBuffers() {
		uniformData.projInverse = glm::inverse(camera.matrices.perspective);
		uniformData.viewInverse = glm::inverse(camera.matrices.view);
		//uniformData.lightPos = glm::vec4(cos(glm::radians(timer * 360.0f)) * 40.0f, -50.0f + sin(glm::radians(timer * 360.0f)) * 20.0f, 25.0f + sin(glm::radians(timer * 360.0f)) * 5.0f, 0.0f);
		uniformData.lightPos = glm::vec4(cos(glm::radians(timer * 360.0f)) * 40.0f, 0.0f, 25.0f + sin(glm::radians(timer * 360.0f)) * 5.0f, 0.0f);
		memcpy(ubo.mapped, &uniformData, sizeof(uniformData));
	}

	void prepare() {
		VulkanRenderer::prepare();

		// Query the ray tracing properties of the current implementation, we will need them later on
		rayTracingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV;
		VkPhysicalDeviceProperties2 deviceProps2{};
		deviceProps2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		deviceProps2.pNext = &rayTracingProperties;
		vkGetPhysicalDeviceProperties2(physicalDevice, &deviceProps2);

		// Get VK_NV_ray_tracing related function pointers
		vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(vkGetDeviceProcAddr(device, "vkCreateAccelerationStructureNV"));
		vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(vkGetDeviceProcAddr(device, "vkDestroyAccelerationStructureNV"));
		vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(vkGetDeviceProcAddr(device, "vkBindAccelerationStructureMemoryNV"));
		vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(vkGetDeviceProcAddr(device, "vkGetAccelerationStructureHandleNV"));
		vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(vkGetDeviceProcAddr(device, "vkGetAccelerationStructureMemoryRequirementsNV"));
		vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(vkGetDeviceProcAddr(device, "vkCmdBuildAccelerationStructureNV"));
		vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(vkGetDeviceProcAddr(device, "vkCreateRayTracingPipelinesNV"));
		vkGetRayTracingShaderGroupHandlesNV = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesNV>(vkGetDeviceProcAddr(device, "vkGetRayTracingShaderGroupHandlesNV"));
		vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(vkGetDeviceProcAddr(device, "vkCmdTraceRaysNV"));

		createScene();
		createStorageImage();
		createUniformBuffer();
		createRayTracingPipeline();
		createShaderBindingTable();
		createDescriptorSets();
		buildCommandBuffers();
		prepared = true;
	}

	void draw() {
		VulkanRenderer::prepareFrame();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer];
		tools::VK_VERIFY_SUCCESS(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));
		VulkanRenderer::submitFrame();
	}

	virtual void render() {
		if (!prepared)
			return;
		draw();
		if (!paused || camera.updated)
			updateUniformBuffers();
	}
};









/**

VULKAN CLOTH SIMULATION FORK

**/

class VulkanCloth : public VulkanRenderer {
public:
	uint32_t sceneSetup = 1;
	uint32_t readSet = 0;
	uint32_t indexCount;

	VertexLayout vertexLayout = VertexLayout({
		VERTEX_COMPONENT_POSITION,
		VERTEX_COMPONENT_UV,
		VERTEX_COMPONENT_NORMAL,
		});
	Model modelSphere;

	// Resources for the graphics part of the example
	struct {
		VkDescriptorSetLayout descriptorSetLayout;
		VkDescriptorSet descriptorSet;
		VkPipelineLayout pipelineLayout;
		struct Pipelines {
			VkPipeline cloth;
			VkPipeline sphere;
		} pipelines;
		Buffer indices;
		Buffer uniformBuffer;
		struct graphicsUBO {
			glm::mat4 projection;
			glm::mat4 view;
			glm::vec4 lightPos = glm::vec4(-30.0f, 50.0f, -30.0f, 1.0f);
			//glm::vec4 lightPos = glm::vec4(-1.0f, 2.0f, -1.0f, 1.0f);
		} ubo;
	} graphics;

	VulkanCloth() : VulkanRenderer(ENABLE_VALIDATION) {
		title = "Vulkan Cloth Simulation";
		camera.type = Camera::CameraType::firstperson;
		camera.setPerspective(60.0f, (float)width / (float)height, 0.1f, 512.0f);
		camera.setRotation(glm::vec3(-30.0f, -45.0f, 0.0f));
		camera.setTranslation(glm::vec3(0.0f, 0.0f, -3.5f));
		settings.overlay = true;
		simulateWind = true;
	}

	~VulkanCloth() {
		// Graphics
		graphics.uniformBuffer.destroy();
		vkDestroyPipeline(device, graphics.pipelines.cloth, nullptr);
		vkDestroyPipeline(device, graphics.pipelines.sphere, nullptr);
		vkDestroyPipelineLayout(device, graphics.pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device, graphics.descriptorSetLayout, nullptr);
		textureCloth.destroy();
		modelSphere.destroy();

		// Compute
		compute.storageBuffers.input.destroy();
		compute.storageBuffers.output.destroy();
		compute.uniformBuffer.destroy();
		vkDestroyPipelineLayout(device, compute.pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device, compute.descriptorSetLayout, nullptr);
		vkDestroyPipeline(device, compute.pipeline, nullptr);
		vkDestroyFence(device, compute.fence, nullptr);
		vkDestroyCommandPool(device, compute.commandPool, nullptr);
	}

	// Enable physical device features required for this example				
	virtual void getEnabledFeatures() {
		if (deviceFeatures.samplerAnisotropy) {
			enabledFeatures.samplerAnisotropy = VK_TRUE;
		}
	};

	void loadAssets() {
		textureCloth.loadFromFile(getAssetPath() + "textures/vulkan_cloth_basic.ktx", VK_FORMAT_R8G8B8A8_UNORM, vulkanDevice, queue);
		modelSphere.loadFromFile(getAssetPath() + "models/geosphere.obj", vertexLayout, compute.ubo.sphereRadius * 0.05f, vulkanDevice, queue);
		modelSphere.enabled = false;
	}

	void buildCommandBuffers() {
		// Destroy command buffers if already present
		if (!checkCommandBuffers()) {
			destroyCommandBuffers();
			createCommandBuffers();
		}

		VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();

		VkClearValue clearValues[2];
		clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };;
		clearValues[1].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderPassBeginInfo = initializers::renderPassBeginInfo();
		renderPassBeginInfo.renderPass = renderPass;
		renderPassBeginInfo.renderArea.offset.x = 0;
		renderPassBeginInfo.renderArea.offset.y = 0;
		renderPassBeginInfo.renderArea.extent.width = width;
		renderPassBeginInfo.renderArea.extent.height = height;
		renderPassBeginInfo.clearValueCount = 2;
		renderPassBeginInfo.pClearValues = clearValues;

		for (int32_t i = 0; i < drawCmdBuffers.size(); ++i) {
			// Set target frame buffer
			renderPassBeginInfo.framebuffer = frameBuffers[i];

			tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(drawCmdBuffers[i], &cmdBufInfo));

			// Draw the particle system using the update vertex buffer

			vkCmdBeginRenderPass(drawCmdBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

			VkViewport viewport = initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
			vkCmdSetViewport(drawCmdBuffers[i], 0, 1, &viewport);

			VkRect2D scissor = initializers::rect2D(width, height, 0, 0);
			vkCmdSetScissor(drawCmdBuffers[i], 0, 1, &scissor);

			VkDeviceSize offsets[1] = { 0 };

			// Render sphere
			if (modelSphere.enabled) {
				vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics.pipelines.sphere);
				vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics.pipelineLayout, 0, 1, &graphics.descriptorSet, 0, NULL);
				vkCmdBindIndexBuffer(drawCmdBuffers[i], modelSphere.indices.buffer, 0, VK_INDEX_TYPE_UINT32);
				vkCmdBindVertexBuffers(drawCmdBuffers[i], 0, 1, &modelSphere.vertices.buffer, offsets);
				vkCmdDrawIndexed(drawCmdBuffers[i], modelSphere.indexCount, 1, 0, 0, 0);
			}

			// Render cloth
			vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics.pipelines.cloth);
			vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphics.pipelineLayout, 0, 1, &graphics.descriptorSet, 0, NULL);
			vkCmdBindIndexBuffer(drawCmdBuffers[i], graphics.indices.buffer, 0, VK_INDEX_TYPE_UINT32);
			vkCmdBindVertexBuffers(drawCmdBuffers[i], 0, 1, &compute.storageBuffers.output.buffer, offsets);
			vkCmdDrawIndexed(drawCmdBuffers[i], indexCount, 1, 0, 0, 0);

			drawUI(drawCmdBuffers[i]);

			vkCmdEndRenderPass(drawCmdBuffers[i]);

			tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(drawCmdBuffers[i]));
		}

	}

	// todo: check barriers (validation, separate compute queue)
	void buildComputeCommandBuffer() {
		VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();

		for (uint32_t i = 0; i < 2; i++) {

			tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(compute.commandBuffers[i], &cmdBufInfo));

			VkBufferMemoryBarrier bufferBarrier = initializers::bufferMemoryBarrier();
			bufferBarrier.srcAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
			bufferBarrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			bufferBarrier.srcQueueFamilyIndex = vulkanDevice->queueFamilyIndices.graphics;
			bufferBarrier.dstQueueFamilyIndex = vulkanDevice->queueFamilyIndices.compute;
			bufferBarrier.size = VK_WHOLE_SIZE;

			std::vector<VkBufferMemoryBarrier> bufferBarriers;
			bufferBarrier.buffer = compute.storageBuffers.input.buffer;
			bufferBarriers.push_back(bufferBarrier);
			bufferBarrier.buffer = compute.storageBuffers.output.buffer;
			bufferBarriers.push_back(bufferBarrier);

			vkCmdPipelineBarrier(compute.commandBuffers[i],
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_FLAGS_NONE,
				0, nullptr,
				static_cast<uint32_t>(bufferBarriers.size()), bufferBarriers.data(),
				0, nullptr);

			vkCmdBindPipeline(compute.commandBuffers[i], VK_PIPELINE_BIND_POINT_COMPUTE, compute.pipeline);

			uint32_t calculateNormals = 0;
			vkCmdPushConstants(compute.commandBuffers[i], compute.pipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(uint32_t), &calculateNormals);

			// Dispatch the compute job
			const uint32_t iterations = 64;
			for (uint32_t j = 0; j < iterations; j++) {
				readSet = 1 - readSet;
				vkCmdBindDescriptorSets(compute.commandBuffers[i], VK_PIPELINE_BIND_POINT_COMPUTE, compute.pipelineLayout, 0, 1, &compute.descriptorSets[readSet], 0, 0);

				if (j == iterations - 1) {
					calculateNormals = 1;
					vkCmdPushConstants(compute.commandBuffers[i], compute.pipelineLayout, VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(uint32_t), &calculateNormals);
				}

				vkCmdDispatch(compute.commandBuffers[i], cloth.gridsize.x / 10, cloth.gridsize.y / 10, 1);

				for (auto& barrier : bufferBarriers) {
					barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
					barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
					barrier.srcQueueFamilyIndex = vulkanDevice->queueFamilyIndices.compute;
					barrier.dstQueueFamilyIndex = vulkanDevice->queueFamilyIndices.graphics;
				}

				vkCmdPipelineBarrier(
					compute.commandBuffers[i],
					VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
					VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
					VK_FLAGS_NONE,
					0, nullptr,
					static_cast<uint32_t>(bufferBarriers.size()), bufferBarriers.data(),
					0, nullptr);

			}

			for (auto& barrier : bufferBarriers) {
				barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
				barrier.dstAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
				barrier.srcQueueFamilyIndex = vulkanDevice->queueFamilyIndices.compute;
				barrier.dstQueueFamilyIndex = vulkanDevice->queueFamilyIndices.graphics;
			}

			vkCmdPipelineBarrier(
				compute.commandBuffers[i],
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				VK_FLAGS_NONE,
				0, nullptr,
				static_cast<uint32_t>(bufferBarriers.size()), bufferBarriers.data(),
				0, nullptr);

			vkEndCommandBuffer(compute.commandBuffers[i]);
		}
	}

	// Setup and fill the compute shader storage buffers containing the particles
	void prepareStorageBuffers() {
		std::vector<Particle> particleBuffer(cloth.gridsize.x * cloth.gridsize.y);

		float dx = cloth.size.x / (cloth.gridsize.x - 1);
		float dy = cloth.size.y / (cloth.gridsize.y - 1);
		float du = 1.0f / (cloth.gridsize.x - 1);
		float dv = 1.0f / (cloth.gridsize.y - 1);

		switch (sceneSetup) {
		case 0:
		{
			// Horz. cloth falls onto sphere
			glm::mat4 transM = glm::translate(glm::mat4(1.0f), glm::vec3(-cloth.size.x / 2.0f, -2.0f, -cloth.size.y / 2.0f));
			for (uint32_t i = 0; i < cloth.gridsize.y; i++) {
				for (uint32_t j = 0; j < cloth.gridsize.x; j++) {
					particleBuffer[i + j * cloth.gridsize.y].pos = transM * glm::vec4(dx * j, 0.0f, dy * i, 1.0f);
					particleBuffer[i + j * cloth.gridsize.y].vel = glm::vec4(0.0f);
					particleBuffer[i + j * cloth.gridsize.y].uv = glm::vec4(1.0f - du * i, dv * j, 0.0f, 0.0f);
				}
			}
			break;
		}
		case 1:
		{
			// Vert. Pinned cloth
			glm::mat4 transM = glm::translate(glm::mat4(1.0f), glm::vec3(-cloth.size.x / 2.0f, -cloth.size.y / 2.0f, 0.0f));
			//compute.ubo.spherePos.x = 5.0f;
			//compute.ubo.spherePos.z = -10.0f;
			compute.ubo.spherePos = glm::vec4(modelSphere.position, 1.0f);
			for (uint32_t i = 0; i < cloth.gridsize.y; i++) {
				for (uint32_t j = 0; j < cloth.gridsize.x; j++) {
					particleBuffer[i + j * cloth.gridsize.y].pos = transM * glm::vec4(dx * j, dy * i, 0.0f, 1.0f);
					particleBuffer[i + j * cloth.gridsize.y].vel = glm::vec4(0.0f);
					particleBuffer[i + j * cloth.gridsize.y].uv = glm::vec4(du * j, dv * i, 0.0f, 0.0f);
					// Pin some particles
					//particleBuffer[i + j * cloth.gridsize.y].pinned = (i == 0) && ((j == 0) || (j == cloth.gridsize.x / 3) || (j == cloth.gridsize.x - cloth.gridsize.x / 3) || (j == cloth.gridsize.x - 1));
					particleBuffer[i + j * cloth.gridsize.y].pinned = (i == 0) && ((j == 0) || (j == cloth.gridsize.x / 2) || (j == cloth.gridsize.x - 1));
				}
			}
			break;
		}
		}

		VkDeviceSize storageBufferSize = particleBuffer.size() * sizeof(Particle);

		// Staging
		// SSBO won't be changed on the host after upload so copy to device local memory 

		Buffer stagingBuffer;

		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&stagingBuffer,
			storageBufferSize,
			particleBuffer.data());

		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&compute.storageBuffers.input,
			storageBufferSize);

		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&compute.storageBuffers.output,
			storageBufferSize);

		// Copy from staging buffer
		VkCommandBuffer copyCmd = VulkanRenderer::createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
		VkBufferCopy copyRegion = {};
		copyRegion.size = storageBufferSize;
		vkCmdCopyBuffer(copyCmd, stagingBuffer.buffer, compute.storageBuffers.input.buffer, 1, &copyRegion);
		vkCmdCopyBuffer(copyCmd, stagingBuffer.buffer, compute.storageBuffers.output.buffer, 1, &copyRegion);
		VulkanRenderer::flushCommandBuffer(copyCmd, queue, true);

		stagingBuffer.destroy();

		// Indices
		std::vector<uint32_t> indices;
		for (uint32_t y = 0; y < cloth.gridsize.y - 1; y++) {
			for (uint32_t x = 0; x < cloth.gridsize.x; x++) {
				indices.push_back((y + 1) * cloth.gridsize.x + x);
				indices.push_back((y)* cloth.gridsize.x + x);
			}
			// Primitive restart (signlaed by special value 0xFFFFFFFF)
			indices.push_back(0xFFFFFFFF);
		}
		uint32_t indexBufferSize = static_cast<uint32_t>(indices.size()) * sizeof(uint32_t);
		indexCount = static_cast<uint32_t>(indices.size());

		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&stagingBuffer,
			indexBufferSize,
			indices.data());

		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&graphics.indices,
			indexBufferSize);

		// Copy from staging buffer
		copyCmd = VulkanRenderer::createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
		copyRegion = {};
		copyRegion.size = indexBufferSize;
		vkCmdCopyBuffer(copyCmd, stagingBuffer.buffer, graphics.indices.buffer, 1, &copyRegion);
		VulkanRenderer::flushCommandBuffer(copyCmd, queue, true);

		stagingBuffer.destroy();
	}

	void setupDescriptorPool() {
		std::vector<VkDescriptorPoolSize> poolSizes = {
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 3),
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 4),
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 2)
		};

		VkDescriptorPoolCreateInfo descriptorPoolInfo =
			initializers::descriptorPoolCreateInfo(poolSizes, 3);

		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorPool(device, &descriptorPoolInfo, nullptr, &descriptorPool));
	}

	void setupLayoutsAndDescriptors() {
		// Set layout
		std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
			initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, 0),
			initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT, 1)
		};
		VkDescriptorSetLayoutCreateInfo descriptorLayout =
			initializers::descriptorSetLayoutCreateInfo(setLayoutBindings);
		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorSetLayout(device, &descriptorLayout, nullptr, &graphics.descriptorSetLayout));

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo =
			initializers::pipelineLayoutCreateInfo(&graphics.descriptorSetLayout, 1);
		tools::VK_VERIFY_SUCCESS(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &graphics.pipelineLayout));

		// Set
		VkDescriptorSetAllocateInfo allocInfo =
			initializers::descriptorSetAllocateInfo(descriptorPool, &graphics.descriptorSetLayout, 1);
		tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device, &allocInfo, &graphics.descriptorSet));

		std::vector<VkWriteDescriptorSet> writeDescriptorSets = {
			initializers::writeDescriptorSet(graphics.descriptorSet, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 0, &graphics.uniformBuffer.descriptor),
			initializers::writeDescriptorSet(graphics.descriptorSet, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, &textureCloth.descriptor)
		};
		vkUpdateDescriptorSets(device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, NULL);
	}

	void preparePipelines() {
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState =
			initializers::pipelineInputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP, 0, VK_TRUE);

		VkPipelineRasterizationStateCreateInfo rasterizationState =
			initializers::pipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_COUNTER_CLOCKWISE, 0);

		VkPipelineColorBlendAttachmentState blendAttachmentState =
			initializers::pipelineColorBlendAttachmentState(0xf, VK_FALSE);

		VkPipelineColorBlendStateCreateInfo colorBlendState =
			initializers::pipelineColorBlendStateCreateInfo(1, &blendAttachmentState);

		VkPipelineDepthStencilStateCreateInfo depthStencilState =
			initializers::pipelineDepthStencilStateCreateInfo(VK_TRUE, VK_TRUE, VK_COMPARE_OP_LESS_OR_EQUAL);

		VkPipelineViewportStateCreateInfo viewportState =
			initializers::pipelineViewportStateCreateInfo(1, 1, 0);

		VkPipelineMultisampleStateCreateInfo multisampleState =
			initializers::pipelineMultisampleStateCreateInfo(VK_SAMPLE_COUNT_1_BIT, 0);

		std::vector<VkDynamicState> dynamicStateEnables = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamicState =
			initializers::pipelineDynamicStateCreateInfo(dynamicStateEnables, 0);

		// Rendering pipeline
		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

		shaderStages[0] = loadShader(getAssetPath() + "shaders/cloth/cloth.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
		shaderStages[1] = loadShader(getAssetPath() + "shaders/cloth/cloth.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

		VkGraphicsPipelineCreateInfo pipelineCreateInfo =
			initializers::pipelineCreateInfo(
				graphics.pipelineLayout,
				renderPass,
				0);

		// Input attributes	

		// Binding description
		std::vector<VkVertexInputBindingDescription> inputBindings = {
			initializers::vertexInputBindingDescription(0, sizeof(Particle), VK_VERTEX_INPUT_RATE_VERTEX)
		};

		// Attribute descriptions
		std::vector<VkVertexInputAttributeDescription> inputAttributes = {
			initializers::vertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Particle, pos)),
			initializers::vertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(Particle, uv)),
			initializers::vertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Particle, normal))
		};

		// Assign to vertex buffer
		VkPipelineVertexInputStateCreateInfo inputState = initializers::pipelineVertexInputStateCreateInfo();
		inputState.vertexBindingDescriptionCount = static_cast<uint32_t>(inputBindings.size());
		inputState.pVertexBindingDescriptions = inputBindings.data();
		inputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(inputAttributes.size());
		inputState.pVertexAttributeDescriptions = inputAttributes.data();

		pipelineCreateInfo.pVertexInputState = &inputState;
		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
		pipelineCreateInfo.pRasterizationState = &rasterizationState;
		pipelineCreateInfo.pColorBlendState = &colorBlendState;
		pipelineCreateInfo.pMultisampleState = &multisampleState;
		pipelineCreateInfo.pViewportState = &viewportState;
		pipelineCreateInfo.pDepthStencilState = &depthStencilState;
		pipelineCreateInfo.pDynamicState = &dynamicState;
		pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
		pipelineCreateInfo.pStages = shaderStages.data();
		pipelineCreateInfo.renderPass = renderPass;

		tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCreateInfo, nullptr, &graphics.pipelines.cloth));

		// Sphere rendering pipeline
		inputBindings = {
			initializers::vertexInputBindingDescription(0, vertexLayout.stride(), VK_VERTEX_INPUT_RATE_VERTEX)
		};
		inputAttributes = {
			initializers::vertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0),
			initializers::vertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 3),
			initializers::vertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 5)
		};
		inputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(inputAttributes.size());
		inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		rasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
		shaderStages[0] = loadShader(getAssetPath() + "shaders/cloth/sphere.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
		shaderStages[1] = loadShader(getAssetPath() + "shaders/cloth/sphere.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);
		tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCreateInfo, nullptr, &graphics.pipelines.sphere));
	}

	void prepareCompute() {
		// Create a compute capable device queue
		vkGetDeviceQueue(device, vulkanDevice->queueFamilyIndices.compute, 0, &compute.queue);

		// Create compute pipeline
		std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
			initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_COMPUTE_BIT, 0),
			initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_COMPUTE_BIT, 1),
			initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_COMPUTE_BIT, 2),
		};

		VkDescriptorSetLayoutCreateInfo descriptorLayout =
			initializers::descriptorSetLayoutCreateInfo(setLayoutBindings);

		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorSetLayout(device, &descriptorLayout, nullptr, &compute.descriptorSetLayout));

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo =
			initializers::pipelineLayoutCreateInfo(&compute.descriptorSetLayout, 1);

		// Push constants used to pass some parameters
		VkPushConstantRange pushConstantRange =
			initializers::pushConstantRange(VK_SHADER_STAGE_COMPUTE_BIT, sizeof(uint32_t), 0);
		pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
		pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;

		tools::VK_VERIFY_SUCCESS(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &compute.pipelineLayout));

		VkDescriptorSetAllocateInfo allocInfo =
			initializers::descriptorSetAllocateInfo(descriptorPool, &compute.descriptorSetLayout, 1);

		// Create two descriptor sets with input and output buffers switched 
		tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device, &allocInfo, &compute.descriptorSets[0]));
		tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device, &allocInfo, &compute.descriptorSets[1]));

		std::vector<VkWriteDescriptorSet> computeWriteDescriptorSets = {
			initializers::writeDescriptorSet(compute.descriptorSets[0], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 0, &compute.storageBuffers.input.descriptor),
			initializers::writeDescriptorSet(compute.descriptorSets[0], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, &compute.storageBuffers.output.descriptor),
			initializers::writeDescriptorSet(compute.descriptorSets[0], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2, &compute.uniformBuffer.descriptor),

			initializers::writeDescriptorSet(compute.descriptorSets[1], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 0, &compute.storageBuffers.output.descriptor),
			initializers::writeDescriptorSet(compute.descriptorSets[1], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, &compute.storageBuffers.input.descriptor),
			initializers::writeDescriptorSet(compute.descriptorSets[1], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2, &compute.uniformBuffer.descriptor)
		};

		vkUpdateDescriptorSets(device, static_cast<uint32_t>(computeWriteDescriptorSets.size()), computeWriteDescriptorSets.data(), 0, NULL);

		// Create pipeline		
		VkComputePipelineCreateInfo computePipelineCreateInfo = initializers::computePipelineCreateInfo(compute.pipelineLayout, 0);
		computePipelineCreateInfo.stage = loadShader(getAssetPath() + "shaders/cloth/cloth.comp.spv", VK_SHADER_STAGE_COMPUTE_BIT);
		tools::VK_VERIFY_SUCCESS(vkCreateComputePipelines(device, pipelineCache, 1, &computePipelineCreateInfo, nullptr, &compute.pipeline));

		// Separate command pool as queue family for compute may be different than graphics
		VkCommandPoolCreateInfo cmdPoolInfo = {};
		cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cmdPoolInfo.queueFamilyIndex = vulkanDevice->queueFamilyIndices.compute;
		cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		tools::VK_VERIFY_SUCCESS(vkCreateCommandPool(device, &cmdPoolInfo, nullptr, &compute.commandPool));

		// Create a command buffer for compute operations
		VkCommandBufferAllocateInfo cmdBufAllocateInfo =
			initializers::commandBufferAllocateInfo(compute.commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 2);

		tools::VK_VERIFY_SUCCESS(vkAllocateCommandBuffers(device, &cmdBufAllocateInfo, &compute.commandBuffers[0]));

		// Fence for compute CB sync
		VkFenceCreateInfo fenceCreateInfo = initializers::fenceCreateInfo(VK_FENCE_CREATE_SIGNALED_BIT);
		tools::VK_VERIFY_SUCCESS(vkCreateFence(device, &fenceCreateInfo, nullptr, &compute.fence));

		// Build a single command buffer containing the compute dispatch commands
		buildComputeCommandBuffer();
	}

	// Prepare and initialize uniform buffer containing shader uniforms
	void prepareUniformBuffers() {
		// Compute shader uniform buffer block
		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&compute.uniformBuffer,
			sizeof(compute.ubo));
		tools::VK_VERIFY_SUCCESS(compute.uniformBuffer.map());

		// Initial values
		float dx = cloth.size.x / (cloth.gridsize.x - 1);
		float dy = cloth.size.y / (cloth.gridsize.y - 1);

		compute.ubo.restDistH = dx;
		compute.ubo.restDistV = dy;
		compute.ubo.restDistD = sqrtf(dx * dx + dy * dy);
		compute.ubo.particleCount = cloth.gridsize;

		updateComputeUBO();

		// Vertex shader uniform buffer block
		vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&graphics.uniformBuffer,
			sizeof(graphics.ubo));
		tools::VK_VERIFY_SUCCESS(graphics.uniformBuffer.map());

		updateGraphicsUBO();
	}

	void updateComputeUBO() {
		if (!paused) {
			compute.ubo.deltaT = 0.00003f;//0.000005f;
			//compute.ubo.deltaT = frameTime;// *0.0075f;

			if (simulateWind) {
				std::default_random_engine rndEngine(benchmark.active ? 0 : (unsigned)time(nullptr));
				std::uniform_real_distribution<float> rd(1.0f, 6.0f);
				compute.ubo.gravity.x = cos(glm::radians(-rand() * 360.0f)) * (rd(rndEngine) - rd(rndEngine));
				compute.ubo.gravity.z = sin(glm::radians(rand() * 360.0f)) * (rd(rndEngine) - rd(rndEngine));
			} else {
				compute.ubo.gravity.x = 0.0f;
				compute.ubo.gravity.z = 0.0f;
			}
			compute.ubo.spherePos = glm::vec4(modelSphere.position, 1.0f);
		} else {
			compute.ubo.deltaT = 0.0f;
		}
		memcpy(compute.uniformBuffer.mapped, &compute.ubo, sizeof(compute.ubo));
	}

	void updateGraphicsUBO() {
		graphics.ubo.projection = camera.matrices.perspective;
		graphics.ubo.view = camera.matrices.view;
		memcpy(graphics.uniformBuffer.mapped, &graphics.ubo, sizeof(graphics.ubo));
	}

	void draw() {
		VkSubmitInfo computeSubmitInfo = initializers::submitInfo();
		computeSubmitInfo.commandBufferCount = 1;
		computeSubmitInfo.pCommandBuffers = &compute.commandBuffers[readSet];

		tools::VK_VERIFY_SUCCESS(vkQueueSubmit(compute.queue, 1, &computeSubmitInfo, compute.fence));

		// Submit graphics commands
		VulkanRenderer::prepareFrame();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer];
		tools::VK_VERIFY_SUCCESS(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));

		VulkanRenderer::submitFrame();

		vkWaitForFences(device, 1, &compute.fence, VK_TRUE, UINT64_MAX);
		vkResetFences(device, 1, &compute.fence);
	}

	void prepare() {
		VulkanRenderer::prepare();
		loadAssets();
		prepareStorageBuffers();
		prepareUniformBuffers();
		setupDescriptorPool();
		setupLayoutsAndDescriptors();
		preparePipelines();
		prepareCompute();
		buildCommandBuffers();
		prepared = true;
	}

	void animate() {
		std::chrono::milliseconds time_since_reset = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - resetTime);
		float time = time_since_reset.count() / 1000.0;

		modelSphere.position = glm::vec3(
			0.0f,	// x
			0.0f,	// y
			0.0f	// z
		);
	}

	virtual void render() {
		if (!prepared)
			return;

		animate();

		draw();

		updateComputeUBO();
	}

	virtual void viewChanged() {
		updateGraphicsUBO();
	}

	virtual void OnUpdateUIOverlay(UIOverlay* overlay) {
		if (overlay->header("Settings")) {
			overlay->checkBox("Simulate wind", &simulateWind);
		}
	}
};








/**

VULKAN PARTICLE SYSTEM FORK

**/
#define VERTEX_BUFFER_BIND_ID 0
#define ENABLE_VALIDATION false
#define PARTICLE_COUNT 512
#define PARTICLE_SIZE 10.0f
#define PARTICLE_LIFESPAN 1.0f

#define FLAME_RADIUS 8.0f

#define PARTICLE_TYPE_FLAME 0
#define PARTICLE_TYPE_SMOKE 1

class VulkanParticles : public VulkanRenderer {
public:
	struct Particle {
		glm::vec4 pos;
		glm::vec4 color;
		float alpha;
		float size;
		float rotation;
		uint32_t type;
		// Attributes not used in shader
		glm::vec4 vel;
		float rotationSpeed;
		float lifespan = PARTICLE_LIFESPAN;
	};

	struct {
		struct {
			Texture2D smoke;
			Texture2D fire;
			// Use a custom sampler to change sampler attributes required for rotating the uvs in the shader for alpha blended textures
			VkSampler sampler;
			int color[3]; //rgb
		} particles;
		struct {
			Texture2D colorMap;
			Texture2D normalMap;
		} floor;
	} textures;

	// Vertex layout for the models
	VertexLayout vertexLayout = VertexLayout({
		VERTEX_COMPONENT_POSITION,
		VERTEX_COMPONENT_UV,
		VERTEX_COMPONENT_NORMAL,
		VERTEX_COMPONENT_TANGENT,
		VERTEX_COMPONENT_BITANGENT,
		});

	struct {
		Model environment;
	} models;

	//glm::vec3 emitterPos = glm::vec3(0.0f, -FLAME_RADIUS + 2.0f, 0.0f);
	glm::vec3 minVel = glm::vec3(-3.0f, -3.0f, -3.0f);
	glm::vec3 maxVel = glm::vec3( 3.0f,  3.0f,  3.0f);

	struct {
		VkBuffer buffer;
		VkDeviceMemory memory;
		// Store the mapped address of the particle data for reuse
		void* mappedMemory;
		// Size of the particle buffer in bytes
		size_t size;
	} particles;

	struct {
		Buffer fire;
		Buffer environment;
	} uniformBuffers;

	struct UBOVS {
		glm::mat4 projection;
		glm::mat4 model;
		glm::vec2 viewportDim;
		float pointSize = PARTICLE_SIZE;
	} uboVS;

	struct UBOEnv {
		glm::mat4 projection;
		glm::mat4 model;
		glm::mat4 normal;
		glm::vec4 lightPos = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	} uboEnv;

	struct {
		VkPipeline particles;
		VkPipeline environment;
	} pipelines;

	VkPipelineLayout pipelineLayout;
	VkDescriptorSetLayout descriptorSetLayout;

	struct {
		VkDescriptorSet particles;
		VkDescriptorSet environment;
	} descriptorSets;

	std::vector<Particle> particleBuffer;

	std::default_random_engine rndEngine;

	VulkanParticles() : VulkanRenderer(ENABLE_VALIDATION) {
		zoom = -75.0f;
		rotation = { -15.0f, 45.0f, 0.0f };
		title = "Particle System";
		settings.overlay = true;
		zoomSpeed *= 1.5f;
		timerSpeed *= 0.000003f;// 8.0f;
		rndEngine.seed(benchmark.active ? 0 : (unsigned)time(nullptr));
	}

	~VulkanParticles() {
		textures.particles.smoke.destroy();
		textures.particles.fire.destroy();
		textures.floor.colorMap.destroy();
		textures.floor.normalMap.destroy();

		vkDestroyPipeline(device, pipelines.particles, nullptr);
		vkDestroyPipeline(device, pipelines.environment, nullptr);

		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

		vkUnmapMemory(device, particles.memory);
		vkDestroyBuffer(device, particles.buffer, nullptr);
		vkFreeMemory(device, particles.memory, nullptr);

		uniformBuffers.environment.destroy();
		uniformBuffers.fire.destroy();

		models.environment.destroy();

		vkDestroySampler(device, textures.particles.sampler, nullptr);
	}

	void buildCommandBuffers() {
		VkCommandBufferBeginInfo cmdBufInfo = initializers::commandBufferBeginInfo();

		VkClearValue clearValues[2];
		clearValues[0].color = defaultClearColor;
		clearValues[1].depthStencil = { 1.0f, 0 };

		VkRenderPassBeginInfo renderPassBeginInfo = initializers::renderPassBeginInfo();
		renderPassBeginInfo.renderPass = renderPass;
		renderPassBeginInfo.renderArea.offset.x = 0;
		renderPassBeginInfo.renderArea.offset.y = 0;
		renderPassBeginInfo.renderArea.extent.width = width;
		renderPassBeginInfo.renderArea.extent.height = height;
		renderPassBeginInfo.clearValueCount = 2;
		renderPassBeginInfo.pClearValues = clearValues;

		for (int32_t i = 0; i < drawCmdBuffers.size(); ++i) {
			// Set target frame buffer
			renderPassBeginInfo.framebuffer = frameBuffers[i];

			tools::VK_VERIFY_SUCCESS(vkBeginCommandBuffer(drawCmdBuffers[i], &cmdBufInfo));

			vkCmdBeginRenderPass(drawCmdBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

			VkViewport viewport = initializers::viewport((float)width, (float)height, 0.0f, 1.0f);
			vkCmdSetViewport(drawCmdBuffers[i], 0, 1, &viewport);

			VkRect2D scissor = initializers::rect2D(width, height, 0, 0);
			vkCmdSetScissor(drawCmdBuffers[i], 0, 1, &scissor);

			VkDeviceSize offsets[1] = { 0 };

			// Environment
			if (models.environment.enabled) {
				vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets.environment, 0, NULL);
				vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.environment);
				vkCmdBindVertexBuffers(drawCmdBuffers[i], VERTEX_BUFFER_BIND_ID, 1, &models.environment.vertices.buffer, offsets);
				vkCmdBindIndexBuffer(drawCmdBuffers[i], models.environment.indices.buffer, 0, VK_INDEX_TYPE_UINT32);
				vkCmdDrawIndexed(drawCmdBuffers[i], models.environment.indexCount, 1, 0, 0, 0);
			}

			// Particle system (no index buffer)
			vkCmdBindDescriptorSets(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets.particles, 0, NULL);
			vkCmdBindPipeline(drawCmdBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.particles);
			vkCmdBindVertexBuffers(drawCmdBuffers[i], VERTEX_BUFFER_BIND_ID, 1, &particles.buffer, offsets);
			vkCmdDraw(drawCmdBuffers[i], PARTICLE_COUNT, 1, 0, 0);

			drawUI(drawCmdBuffers[i]);

			vkCmdEndRenderPass(drawCmdBuffers[i]);

			tools::VK_VERIFY_SUCCESS(vkEndCommandBuffer(drawCmdBuffers[i]));
		}
	}

	void initParticle(Particle* particle, glm::vec3 emitterPos) {
		particle->vel = glm::vec4(rnd(minVel.x, maxVel.x), rnd(minVel.y, maxVel.y), rnd(minVel.z, maxVel.z), 0.0f);
		particle->alpha = rnd(0.75f);
		particle->size = 0.3f;//1.0f + rnd(0.5f);
		particle->color = glm::vec4(1.0f);
		particle->type = PARTICLE_TYPE_FLAME;
		particle->rotation = rnd(2.0f * float(M_PI));
		particle->rotationSpeed = rnd(2.0f) - rnd(2.0f);
		particle->lifespan = PARTICLE_LIFESPAN;

		// Get random sphere point
		//float theta = rnd(2.0f * float(M_PI));
		//float phi = rnd(float(M_PI)) - float(M_PI) / 2.0f;
		//float r = rnd(FLAME_RADIUS);

		//particle->pos.x = r * cos(theta) * cos(phi);
		//particle->pos.y = r * sin(phi);
		//particle->pos.z = r * sin(theta) * cos(phi);

		particle->pos = glm::vec4(emitterPos, 0.0f);
	}

	void transitionParticle(Particle* particle) {
		switch (particle->type) {
		case PARTICLE_TYPE_FLAME:
			// Flame particles have a chance of turning into smoke
			if (rnd(1.0f) < 0.05f && false) {
				particle->alpha = 0.0f;
				particle->color = glm::vec4(0.25f + rnd(0.25f));
				particle->pos.x *= 0.5f;
				particle->pos.z *= 0.5f;
				particle->vel = glm::vec4(rnd(1.0f) - rnd(1.0f), (minVel.y * 2) + rnd(maxVel.y - minVel.y), rnd(1.0f) - rnd(1.0f), 0.0f);
				particle->size = rnd(1.0f, 1.5f);
				particle->rotationSpeed = rnd(1.0f) - rnd(1.0f);
				particle->type = PARTICLE_TYPE_SMOKE;
			} else {
				//initParticle(particle, emitterPos);
				initParticle(particle, models.environment.position);
			}
			break;
		case PARTICLE_TYPE_SMOKE:
			// Respawn at end of life
			//initParticle(particle, emitterPos);
			//initParticle(particle, models.environment.position);
			break;
		}
	}

	void prepareParticles() {
		particleBuffer.resize(PARTICLE_COUNT);
		for (Particle& particle : particleBuffer) {
			initParticle(&particle, models.environment.position);
			particle.alpha = 1.0f - (abs(particle.pos.y) / (FLAME_RADIUS * 2.0f));
		}

		particles.size = particleBuffer.size() * sizeof(Particle);

		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			particles.size,
			&particles.buffer,
			&particles.memory,
			particleBuffer.data()));

		// Map the memory and store the pointer for reuse
		tools::VK_VERIFY_SUCCESS(vkMapMemory(device, particles.memory, 0, particles.size, 0, &particles.mappedMemory));
	}

	void updateParticles() {
		float particleTimer = frameTimer * 0.45f;
		for (Particle& particle : particleBuffer) {
			particle.pos += particle.vel * 0.1f;
			particle.alpha += particleTimer * 2.5f;
			//particle.size -= particleTimer * 0.5f;
			particle.rotation += particleTimer * particle.rotationSpeed;
			// Transition particle state
			particle.lifespan -= frameTime;
			if (particle.lifespan - rnd(0.25f) < 0.0f) {
				initParticle(&particle, models.environment.position);
			}
		}
		size_t size = particleBuffer.size() * sizeof(Particle);
		memcpy(particles.mappedMemory, particleBuffer.data(), size);
	}

	void loadAssets() {
		// Textures
		std::string texFormatSuffix;
		VkFormat texFormat;
		// Get supported compressed texture format
		if (vulkanDevice->features.textureCompressionBC) {
			texFormatSuffix = "_bc3_unorm";
			texFormat = VK_FORMAT_BC3_UNORM_BLOCK;
		} else if (vulkanDevice->features.textureCompressionASTC_LDR) {
			texFormatSuffix = "_astc_8x8_unorm";
			texFormat = VK_FORMAT_ASTC_8x8_UNORM_BLOCK;
		} else if (vulkanDevice->features.textureCompressionETC2) {
			texFormatSuffix = "_etc2_unorm";
			texFormat = VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
		} else {
			tools::exitFatal("Device does not support any compressed texture format!", VK_ERROR_FEATURE_NOT_PRESENT);
		}

		// Particles
		textures.particles.smoke.loadFromFile(getAssetPath() + "textures/particle_smoke.ktx", VK_FORMAT_R8G8B8A8_UNORM, vulkanDevice, queue);
		textures.particles.fire.loadFromFile(getAssetPath() + "textures/particle_fire.ktx", VK_FORMAT_R8G8B8A8_UNORM, vulkanDevice, queue);

		// Floor
		textures.floor.colorMap.loadFromFile(getAssetPath() + "textures/fireplace_colormap" + texFormatSuffix + ".ktx", texFormat, vulkanDevice, queue);
		textures.floor.normalMap.loadFromFile(getAssetPath() + "textures/fireplace_normalmap" + texFormatSuffix + ".ktx", texFormat, vulkanDevice, queue);

		// Create a custom sampler to be used with the particle textures
		// Create sampler
		VkSamplerCreateInfo samplerCreateInfo = initializers::samplerCreateInfo();
		samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		// Different address mode
		samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		samplerCreateInfo.addressModeV = samplerCreateInfo.addressModeU;
		samplerCreateInfo.addressModeW = samplerCreateInfo.addressModeU;
		samplerCreateInfo.mipLodBias = 0.0f;
		samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
		samplerCreateInfo.minLod = 0.0f;
		// Both particle textures have the same number of mip maps
		samplerCreateInfo.maxLod = float(textures.particles.fire.mipLevels);
		// Enable anisotropic filtering
		samplerCreateInfo.maxAnisotropy = 8.0f;
		samplerCreateInfo.anisotropyEnable = VK_TRUE;
		// Use a different border color (than the normal texture loader) for additive blending
		samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
		tools::VK_VERIFY_SUCCESS(vkCreateSampler(device, &samplerCreateInfo, nullptr, &textures.particles.sampler));

		//models.environment.loadFromFile(getAssetPath() + "models/fireplace.obj", vertexLayout, 10.0f, vulkanDevice, queue);
		//models.environment.loadFromFile(getAssetPath() + "models/voyager/voyager.dae", vertexLayout, 1.0f, vulkanDevice, queue);
		models.environment.loadFromFile(getAssetPath() + "models/asteroid_sc0001.blend", vertexLayout, 1.0f, vulkanDevice, queue);
		models.environment.aniType = ANI_KEYFRAMES;
	}

	void setupDescriptorPool() {
		// Example uses one ubo and one image sampler
		std::vector<VkDescriptorPoolSize> poolSizes =
		{
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2),
			initializers::descriptorPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 4)
		};

		VkDescriptorPoolCreateInfo descriptorPoolInfo =
			initializers::descriptorPoolCreateInfo(
				poolSizes.size(),
				poolSizes.data(),
				2);

		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorPool(device, &descriptorPoolInfo, nullptr, &descriptorPool));
	}

	void setupDescriptorSetLayout() {
		std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings =
		{
			// Binding 0 : Vertex shader uniform buffer
			initializers::descriptorSetLayoutBinding(
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				VK_SHADER_STAGE_VERTEX_BIT,
				0),
			// Binding 1 : Fragment shader image sampler
			initializers::descriptorSetLayoutBinding(
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				VK_SHADER_STAGE_FRAGMENT_BIT,
				1),
			// Binding 1 : Fragment shader image sampler
			initializers::descriptorSetLayoutBinding(
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				VK_SHADER_STAGE_FRAGMENT_BIT,
				2)
		};

		VkDescriptorSetLayoutCreateInfo descriptorLayout =
			initializers::descriptorSetLayoutCreateInfo(
				setLayoutBindings.data(),
				setLayoutBindings.size());

		tools::VK_VERIFY_SUCCESS(vkCreateDescriptorSetLayout(device, &descriptorLayout, nullptr, &descriptorSetLayout));

		VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo =
			initializers::pipelineLayoutCreateInfo(
				&descriptorSetLayout,
				1);

		tools::VK_VERIFY_SUCCESS(vkCreatePipelineLayout(device, &pPipelineLayoutCreateInfo, nullptr, &pipelineLayout));
	}

	void setupDescriptorSets() {
		std::vector<VkWriteDescriptorSet> writeDescriptorSets;

		VkDescriptorSetAllocateInfo allocInfo =
			initializers::descriptorSetAllocateInfo(
				descriptorPool,
				&descriptorSetLayout,
				1);

		tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSets.particles));

		// Image descriptor for the color map texture
		VkDescriptorImageInfo texDescriptorSmoke =
			initializers::descriptorImageInfo(
				textures.particles.sampler,
				textures.particles.smoke.view,
				VK_IMAGE_LAYOUT_GENERAL);
		VkDescriptorImageInfo texDescriptorFire =
			initializers::descriptorImageInfo(
				textures.particles.sampler,
				textures.particles.fire.view,
				VK_IMAGE_LAYOUT_GENERAL);

		writeDescriptorSets = {
			// Binding 0: Vertex shader uniform buffer
			initializers::writeDescriptorSet(
				descriptorSets.particles,
				VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				0,
				&uniformBuffers.fire.descriptor),
			// Binding 1: Smoke texture
			initializers::writeDescriptorSet(
				descriptorSets.particles,
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				1,
				&texDescriptorSmoke),
			// Binding 1: Fire texture array
			initializers::writeDescriptorSet(
				descriptorSets.particles,
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				2,
				&texDescriptorFire)
		};

		vkUpdateDescriptorSets(device, writeDescriptorSets.size(), writeDescriptorSets.data(), 0, NULL);

		// Environment
		tools::VK_VERIFY_SUCCESS(vkAllocateDescriptorSets(device, &allocInfo, &descriptorSets.environment));

		writeDescriptorSets = {
			// Binding 0: Vertex shader uniform buffer
			initializers::writeDescriptorSet(
				descriptorSets.environment,
				VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				0,
				&uniformBuffers.environment.descriptor),
			// Binding 1: Color map
			initializers::writeDescriptorSet(
				descriptorSets.environment,
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				1,
				&textures.floor.colorMap.descriptor),
			// Binding 2: Normal map
			initializers::writeDescriptorSet(
				descriptorSets.environment,
				VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				2,
				&textures.floor.normalMap.descriptor),
		};

		vkUpdateDescriptorSets(device, writeDescriptorSets.size(), writeDescriptorSets.data(), 0, NULL);
	}

	void preparePipelines() {
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState =
			initializers::pipelineInputAssemblyStateCreateInfo(
				VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
				0,
				VK_FALSE);

		VkPipelineRasterizationStateCreateInfo rasterizationState =
			initializers::pipelineRasterizationStateCreateInfo(
				VK_POLYGON_MODE_FILL,
				VK_CULL_MODE_BACK_BIT,
				VK_FRONT_FACE_CLOCKWISE,
				0);

		VkPipelineColorBlendAttachmentState blendAttachmentState =
			initializers::pipelineColorBlendAttachmentState(
				0xf,
				VK_FALSE);

		VkPipelineColorBlendStateCreateInfo colorBlendState =
			initializers::pipelineColorBlendStateCreateInfo(
				1,
				&blendAttachmentState);

		VkPipelineDepthStencilStateCreateInfo depthStencilState =
			initializers::pipelineDepthStencilStateCreateInfo(
				VK_TRUE,
				VK_TRUE,
				VK_COMPARE_OP_LESS_OR_EQUAL);

		VkPipelineViewportStateCreateInfo viewportState =
			initializers::pipelineViewportStateCreateInfo(1, 1, 0);

		VkPipelineMultisampleStateCreateInfo multisampleState =
			initializers::pipelineMultisampleStateCreateInfo(
				VK_SAMPLE_COUNT_1_BIT,
				0);

		std::vector<VkDynamicState> dynamicStateEnables = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamicState =
			initializers::pipelineDynamicStateCreateInfo(
				dynamicStateEnables.data(),
				dynamicStateEnables.size(),
				0);

		// Load shaders
		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

		VkGraphicsPipelineCreateInfo pipelineCreateInfo =
			initializers::pipelineCreateInfo(
				pipelineLayout,
				renderPass,
				0);

		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
		pipelineCreateInfo.pRasterizationState = &rasterizationState;
		pipelineCreateInfo.pColorBlendState = &colorBlendState;
		pipelineCreateInfo.pMultisampleState = &multisampleState;
		pipelineCreateInfo.pViewportState = &viewportState;
		pipelineCreateInfo.pDepthStencilState = &depthStencilState;
		pipelineCreateInfo.pDynamicState = &dynamicState;
		pipelineCreateInfo.stageCount = shaderStages.size();
		pipelineCreateInfo.pStages = shaderStages.data();

		// Particle rendering pipeline
		{
			// Shaders
			shaderStages[0] = loadShader(getAssetPath() + "shaders/particles/particle.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
			shaderStages[1] = loadShader(getAssetPath() + "shaders/particles/particle.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

			// Vertex input state
			VkVertexInputBindingDescription vertexInputBinding =
				initializers::vertexInputBindingDescription(VERTEX_BUFFER_BIND_ID, sizeof(Particle), VK_VERTEX_INPUT_RATE_VERTEX);

			std::vector<VkVertexInputAttributeDescription> vertexInputAttributes = {
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 0, VK_FORMAT_R32G32B32A32_SFLOAT,	offsetof(Particle, pos)),	// Location 0: Position
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 1, VK_FORMAT_R32G32B32A32_SFLOAT,	offsetof(Particle, color)),	// Location 1: Color
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 2, VK_FORMAT_R32_SFLOAT, offsetof(Particle, alpha)),			// Location 2: Alpha			
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 3, VK_FORMAT_R32_SFLOAT, offsetof(Particle, size)),			// Location 3: Size
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 4, VK_FORMAT_R32_SFLOAT, offsetof(Particle, rotation)),		// Location 4: Rotation
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 5, VK_FORMAT_R32_SINT, offsetof(Particle, type)),				// Location 5: Particle type
			};

			VkPipelineVertexInputStateCreateInfo vertexInputState = initializers::pipelineVertexInputStateCreateInfo();
			vertexInputState.vertexBindingDescriptionCount = 1;
			vertexInputState.pVertexBindingDescriptions = &vertexInputBinding;
			vertexInputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributes.size());
			vertexInputState.pVertexAttributeDescriptions = vertexInputAttributes.data();

			pipelineCreateInfo.pVertexInputState = &vertexInputState;

			// Dont' write to depth buffer
			depthStencilState.depthWriteEnable = VK_FALSE;

			// Premulitplied alpha
			blendAttachmentState.blendEnable = VK_TRUE;
			blendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			blendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			blendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
			blendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			blendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			blendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
			blendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

			tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCreateInfo, nullptr, &pipelines.particles));
		}

		// Environment rendering pipeline (normal mapped)
		{
			// Shaders
			shaderStages[0] = loadShader(getAssetPath() + "shaders/particles/normalmap.vert.spv", VK_SHADER_STAGE_VERTEX_BIT);
			shaderStages[1] = loadShader(getAssetPath() + "shaders/particles/normalmap.frag.spv", VK_SHADER_STAGE_FRAGMENT_BIT);

			// Vertex input state
			VkVertexInputBindingDescription vertexInputBinding =
				initializers::vertexInputBindingDescription(VERTEX_BUFFER_BIND_ID, vertexLayout.stride(), VK_VERTEX_INPUT_RATE_VERTEX);

			std::vector<VkVertexInputAttributeDescription> vertexInputAttributes = {
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 0, VK_FORMAT_R32G32B32_SFLOAT, 0),							// Location 0: Position
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 1, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 3),			// Location 1: UV
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 2, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 5),			// Location 2: Normal	
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 3, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 8),			// Location 3: Tangent
				initializers::vertexInputAttributeDescription(VERTEX_BUFFER_BIND_ID, 4, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 11),		// Location 4: Bitangen
			};

			VkPipelineVertexInputStateCreateInfo vertexInputState = initializers::pipelineVertexInputStateCreateInfo();
			vertexInputState.vertexBindingDescriptionCount = 1;
			vertexInputState.pVertexBindingDescriptions = &vertexInputBinding;
			vertexInputState.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributes.size());
			vertexInputState.pVertexAttributeDescriptions = vertexInputAttributes.data();

			pipelineCreateInfo.pVertexInputState = &vertexInputState;

			blendAttachmentState.blendEnable = VK_FALSE;
			depthStencilState.depthWriteEnable = VK_TRUE;
			inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

			tools::VK_VERIFY_SUCCESS(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCreateInfo, nullptr, &pipelines.environment));
		}
	}

	// Prepare and initialize uniform buffer containing shader uniforms
	void prepareUniformBuffers() {
		// Vertex shader uniform buffer block
		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&uniformBuffers.fire,
			sizeof(uboVS)));

		// Vertex shader uniform buffer block
		tools::VK_VERIFY_SUCCESS(vulkanDevice->createBuffer(
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&uniformBuffers.environment,
			sizeof(uboEnv)));

		// Map persistent
		tools::VK_VERIFY_SUCCESS(uniformBuffers.fire.map());
		if (models.environment.enabled) tools::VK_VERIFY_SUCCESS(uniformBuffers.environment.map());

		updateUniformBuffers();
	}

	void updateUniformBufferLight() {
		// Environment
		uboEnv.lightPos.x = sin(timer * 2.0f * float(M_PI)) * 1.5f;
		uboEnv.lightPos.y = 0.0f;
		uboEnv.lightPos.z = cos(timer * 2.0f * float(M_PI)) * 1.5f;
		memcpy(uniformBuffers.environment.mapped, &uboEnv, sizeof(uboEnv));
	}

	void updateUniformBuffers() {
		// Vertex shader
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		uboVS.projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.001f, 256.0f);
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, zoom));

		uboVS.model = glm::mat4(1.0f);
		uboVS.model = viewMatrix * glm::translate(uboVS.model, glm::vec3(0.0f, 15.0f, 0.0f));
		uboVS.model = glm::rotate(uboVS.model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		uboVS.model = glm::rotate(uboVS.model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		uboVS.model = glm::rotate(uboVS.model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		uboVS.viewportDim = glm::vec2((float)width, (float)height);
		memcpy(uniformBuffers.fire.mapped, &uboVS, sizeof(uboVS));

		// Environment
		if (models.environment.enabled) {
			uboEnv.projection = uboVS.projection;
			uboEnv.model = uboVS.model;
			uboEnv.normal = glm::inverseTranspose(uboEnv.model);
			memcpy(uniformBuffers.environment.mapped, &uboEnv, sizeof(uboEnv));
		}
	}

	void animate() {
		float RADIUS = 100.0f;
		std::chrono::milliseconds time_since_reset = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - resetTime);
		float time = time_since_reset.count() / 1000.0;
		float radial_speed = 0.15f;

		models.environment.position = glm::vec3(RADIUS*cos(time*radial_speed), RADIUS*sin(time*radial_speed), 0);
	}

	void draw() {
		VulkanRenderer::prepareFrame();

		// Command buffer to be sumitted to the queue
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer];

		// Submit to queue
		tools::VK_VERIFY_SUCCESS(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));

		VulkanRenderer::submitFrame();
	}

	void prepare() {
		VulkanRenderer::prepare();
		loadAssets();
		prepareParticles();
		prepareUniformBuffers();
		setupDescriptorSetLayout();
		preparePipelines();
		setupDescriptorPool();
		setupDescriptorSets();
		buildCommandBuffers();
		prepared = true;
	}

	virtual void render() {
		if (!prepared)
			return;

		draw();
		if (!paused) {
			animate();
			updateUniformBufferLight();
			updateParticles();
		}
	}

	virtual void viewChanged() {
		updateUniformBuffers();
	}

	virtual void OnUpdateUIOverlay(UIOverlay* overlay) {
		if (overlay->header("Settings")) {
			if (overlay->sliderInt("Color Red", &textures.particles.color[0], 0, 255)) {
				updateUniformBuffers();
			}
			if (overlay->sliderInt("Color Green", &textures.particles.color[1], 0, 255)) {
				updateUniformBuffers();
			}
			if (overlay->sliderInt("Color Blue", &textures.particles.color[2], 0, 255)) {
				updateUniformBuffers();
			}
			if (overlay->checkBox("Display Model", &models.environment.enabled)) {
				updateUniformBuffers();
			}
		}
	}
};