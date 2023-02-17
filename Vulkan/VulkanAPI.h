#pragma once
#define GLAD_VULKAN_IMPLEMENTATION
#include <vulkan/vulkan.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <optional>
#include <vector>
#include <array>

#include "Window.h"
#include "Utils.h"
#include "Camera.h"

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::string MODEL_PATH = "models/Room.obj";
const std::string TEXTURE_PATH = "textures/Room.png";

class VkAPI
{
private:

	VkInstance vkInstance;
	VkDebugUtilsMessengerEXT vkDebugMessenger;
	VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
	VkDevice vkDevice;
	VkQueue vkQueue;
	VkQueue vkPresentQueue;
	VkSurfaceKHR vkSurface;
	VkSwapchainKHR vkSwapChain;
	VkFormat vkSwapChainImageFormat;
	VkExtent2D vkSwapChainExtent;
	VkPipelineLayout vkPipelineLayout;
	VkRenderPass vkRenderPass;
	VkPipeline vkGraphicsPipeline;
	VkCommandPool vkCommandPool;
	VkBuffer vkVertexBuffer;
	VkDeviceMemory vkVertexBufferMemory;
	VkBuffer vkIndexBuffer;
	VkDeviceMemory vkIndexBufferMemory;
	VkDescriptorSetLayout vkDescriptorSetLayout;
	VkDescriptorPool vkDescriptorPool;
	VkBuffer vkStagingBuffer;
	VkDeviceMemory vkStagingBufferMemory;
	VkImage vkTextureImage;
	VkDeviceMemory vkTextureImageMemory;
	VkPipelineStageFlags vkSourceStage;
	VkPipelineStageFlags vkDestinationStage;
	VkImageView vkTextureImageView;
	VkSampler vkTextureSampler;
	VkImage vkDepthImage;
	VkDeviceMemory vkDepthImageMemory;
	VkImageView vkDepthImageView;
	uint32_t mipLevels;
	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
	VkImage vkColorImage;
	VkDeviceMemory vkColorImageMemory;
	VkImageView vkColorImageView;

	Utils utils;
	Camera camera;

private:

	std::vector<VkImage> vkSwapChainImages;
	std::vector<VkImageView> vkSwapChainImageViews;
	std::vector<VkFramebuffer> vkSwapChainFramebuffers;
	std::vector<VkCommandBuffer> vkCommandBuffers;
	std::vector<VkSemaphore> vkImageAvailableSemaphores;
	std::vector<VkSemaphore> vkRenderFinishedSemaphores;
	std::vector<VkFence> vkInFlightFences;
	std::vector<VkDynamicState> vkDynamicStates = 
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	std::vector<VkBuffer> vkUniformBuffers;
	std::vector<VkDeviceMemory> vkUniformBuffersMemory;
	std::vector<void*> vkUniformBuffersMapped;
	std::vector<VkDescriptorSet> vkDescriptorSets;
	std::vector<Vertex> vkVertices;
	std::vector<uint32_t> vkIndices;
	

	
public:

	Window* window;
	uint32_t currentFrame = 0;
	bool framebufferResized = false;

public:

	//Window + Init
	void SetWindow(Window* window);
	void InitVulkanAPI();

	//Debug
	void SetupDebugMessenger();
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	//Create/Destroy
	void CreateAPI();
	void DestroyAPI();

	//Validation Layers
	bool CheckValidationLayerSupport();

	//Queue Families
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	bool IsDeviceSuitable(VkPhysicalDevice device);
	void PickPhysicalDevice();
	void CreateLogicalDevice();

	//Window Surface
	void CreateSurface(GLFWwindow* window);

	//Swap Chain
	void CreateSwapChain();
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

	//Image views
	void CreateImageViews();

	//Graphics Pipeline / Shaders
	void CreateGraphicsPipeline();
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	//RenderPass
	void CreateRenderPass();

	//Framebuffers
	void CreateFramebuffers();

	//Command buffers
	void CreateCommandPool();
	void CreateCommandBuffers();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	//Rendering
	void CreateSyncObjects();
	void DrawFrame();
	void DeviceWaitIdle();

	//Recreation Swapchain
	void RecreateSwapChain();
	void CleanupSwapChain();
	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

	//VertexBuffer Creation
	void CreateVertexBuffer();
	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	//Staging Buffer
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	//Index Buffer
	void CreateIndexBuffer();

	//Descriptor Layout & Buffer | Pool & Sets
	void CreateDescriptorSetLayout();
	void CreateUniformBuffers();
	void UpdateUniformBuffer(uint32_t currentImage);
	void CreateDescriptorPool();
	void CreateDescriptorSets();

	//Texture Mapping
	void CreateTextureImage();
	void CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	VkCommandBuffer BeginSingleTimeCommands();
	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
	void CreateTextureImageView();
	VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
	void CreateTextureSampler();

	//Depth Buffering
	void CreateDepthResources();
	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat FindDepthFormat();
	bool HasStencilComponent(VkFormat format);

	//Loading Models
	void LoadModel();

	//Generating Mipmaps
	void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

	//Multisamplimg
	VkSampleCountFlagBits GetMaxUsableSampleCount();
	void CreateColorResources();
};