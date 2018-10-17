#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include "lib/glm/glm.hpp"
#include "lib/glm/ext.hpp"
#include "lib/glm/gtx/hash.hpp"

#include <stdexcept>
#include <iostream>
#include <thread>

class EngineEntity {
private:
	bool assetsLoaded; //This functions as an object lock, so assets can be updated in between frames.
	std::string model_path;
	std::string texture_path;
	glm::mat4 scale_mat;
	glm::mat4 rotate_mat;
	glm::mat4 translate_mat;

public:
	//returns false on any sort of failure, handles the exceptions
	bool drawEntity();

	void setAssetPaths(std::string s);
	std::string getTexturePath() { return texture_path; }
	std::string getModelPath() { return model_path; }
	void loadAssets();
	void markAssetsLoaded();

	glm::mat4 getTransformation() { return translate_mat * scale_mat * rotate_mat; }
	void setTranslate(glm::mat4 m) { translate_mat = m; }
	void setRotate(glm::mat4 m) { rotate_mat = m; }
	void setScale(glm::mat4 m) { scale_mat = m; }
	void resetTransformation() {
		scale_mat = glm::mat4(1.0);
		rotate_mat = glm::mat4(1.0);
		translate_mat = glm::mat4(1.0);
	}

	void translate(float x, float y, float z) { translate_mat = glm::translate(translate_mat, glm::vec3(x, y, z)); }
	void scale(float v) { scale_mat = glm::scale(scale_mat, glm::vec3(v, v, v)); }
	void scaleX(float v) { scale_mat = glm::scale(scale_mat, glm::vec3(v, 1, 1)); }
	void scaleY(float v) { scale_mat = glm::scale(scale_mat, glm::vec3(1, v, 1)); }
	void scaleZ(float v) { scale_mat = glm::scale(scale_mat, glm::vec3(1, 1, v)); }
	void rotateX(float rads) { rotate_mat = glm::rotate(rotate_mat, rads, glm::vec3(1, 0, 0)); }
	void rotateY(float rads) { rotate_mat = glm::rotate(rotate_mat, rads, glm::vec3(0, 1, 0)); }
	void rotateZ(float rads) { rotate_mat = glm::rotate(rotate_mat, rads, glm::vec3(0, 0, 1)); }
	void rotate(float rads, glm::vec3 axis) { rotate_mat = glm::rotate(rotate_mat, rads, axis); }

	EngineEntity();
	//this constructor assumes the file path and file name, but NOT extension are in the string
	// it will automatically select jpg
	EngineEntity(std::string path);
	~EngineEntity();
};
