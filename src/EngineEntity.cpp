#include "EngineEntity.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "lib/stb/stb_image.h"

void loadAssetsThread(EngineEntity* e) {
	//load obj
	//load texture
	int texWidth, texHeight, texChannels;
	//stbi_uc* pixels = stbi_load(e->getTexturePath().c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	/*
	VkDeviceSize imageSize = texWidth * texHeight * 4;
	mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

	if(!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(device, stagingBufferMemory);

	stbi_image_free(pixels);

	createImage(texWidth, texHeight, mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

	transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
	copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
	//transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps
	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);

	generateMipmaps(textureImage, VK_FORMAT_R8G8B8A8_UNORM, texWidth, texHeight, mipLevels);
	*/

	//end thread
	e->markAssetsLoaded();
}
void EngineEntity::setAssetPaths(std::string s) {
	std::string str = s;
	model_path = str.append(".obj");
	str = s;
	texture_path = str.append(".jpg");
}
void EngineEntity::loadAssets() {
	assetsLoaded = false;
	/*
	This generates a new thread that will mark the assets as loaded when it finishes.
	For simplicity, assets are loaded in series rather than making other new threads.
	*/
	std::thread loader(loadAssetsThread, this);
}
void EngineEntity::markAssetsLoaded() {
	assetsLoaded = true;
}
bool EngineEntity::drawEntity() {
	if(assetsLoaded) {
		try {
			return true;
		} catch(const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
	}
	return false;
}

EngineEntity::EngineEntity() {
	EngineEntity("empty");
}
//this constructor assumes the file path and file name, but NOT extension are in the string
EngineEntity::EngineEntity(std::string path) {
	//file path setup, should eventually check for existing file extensions
	assetsLoaded = false;
	loadAssets();

	//model position and directioning setup
	scale_mat = glm::mat4(1.0);
	rotate_mat = glm::mat4(1.0);
	translate_mat = glm::mat4(1.0);
}
EngineEntity::~EngineEntity() {} //no pointers to clean up