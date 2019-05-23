#pragma once

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include "lib/glfw/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include "lib/glm/glm.hpp"
#include "lib/glm/ext.hpp"
#include "lib/glm/gtx/hash.hpp"
#include "lib/glm/gtx/rotate_vector.hpp"

#include "EngineEntity.h"

class Camera {
private:
	glm::vec3 center;
	glm::vec3 lookAt;
	glm::vec3 up;
	glm::vec3 upwards = glm::vec3(0.0f, 0.0f, 1.0f);
	bool free;
	EngineEntity* locked_to; //DO NOT FREE ON DECONSTRUCTION
	glm::vec3 entity_offset; //floating value, hovers at entity_offset_range length
	float entity_offset_range;

	float camera_speed = 100;
	int camera_rotation_sensitivity = 7;

	void rotateCamera(GLFWwindow* window); //used by updateCameraMovements() only for now
public:
	glm::mat4 getViewTransform();
	void updateCameraMovements(GLFWwindow* window);
	void moveTo(glm::vec3 loc); //does nothing if the camera is not free to move

	//getters and setters
	glm::vec3 getCenter();
	void setCenter(glm::vec3 c);
	glm::vec3 getLookAt();
	void setLookAt(glm::vec3 l);
	glm::vec3 getUp();
	void setUp(glm::vec3 u);
	bool getFreeCamStatus();
	void setFreeCam(bool v);
	bool toggleFreeCam();

	Camera();
	~Camera();
};