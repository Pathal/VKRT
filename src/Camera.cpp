#include "Camera.h"

glm::mat4 Camera::getViewTransform() {
	return glm::lookAt(center, lookAt, up);
}

void Camera::rotateCamera(GLFWwindow* window) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, NULL, NULL);
	float cam_vturn_coeff = 100.0;
	float cam_hturn_coeff = 100.0;

	glm::vec3 camera_direction = glm::normalize(lookAt - center);
	glm::vec3 camera_axis = glm::cross(camera_direction, upwards);
	glm::vec3 tmpCamUp = glm::cross(camera_axis, camera_direction);

#define MOUSE_MAX_TURN_VALUE 1000.
	if(x >  MOUSE_MAX_TURN_VALUE) { x =  MOUSE_MAX_TURN_VALUE; }
	if(x < -MOUSE_MAX_TURN_VALUE) { x = -MOUSE_MAX_TURN_VALUE; }
	if(y >  MOUSE_MAX_TURN_VALUE) { y =  MOUSE_MAX_TURN_VALUE; }
	if(y < -MOUSE_MAX_TURN_VALUE) { y = -MOUSE_MAX_TURN_VALUE; }

	//following C-style casts are to suppress compiler warnings
	float xAngle = (float)glm::radians(100000 * camera_rotation_sensitivity * x / MOUSE_MAX_TURN_VALUE);
	float yAngle = (float)glm::radians(100000 * camera_rotation_sensitivity * y / MOUSE_MAX_TURN_VALUE);
	camera_direction = glm::rotate(camera_direction, -xAngle, tmpCamUp);
	camera_direction = glm::rotate(camera_direction, -yAngle, camera_axis);
	//Now update the axis and such
	camera_axis = glm::cross(camera_direction, upwards);
	tmpCamUp = glm::cross(camera_axis, camera_direction);
	lookAt = center + glm::normalize(camera_direction); //unnecessary, but for peace of mind
	up = tmpCamUp;
}

void Camera::updateCameraMovements(GLFWwindow* window) {
	rotateCamera(window);
	if(!free) {
		return;
	}

	//determine movement of the camera "center"
	glm::vec3 camera_direction = glm::normalize(lookAt - center);
	glm::vec3 camera_trajectory = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 camera_axis = glm::cross(camera_direction, upwards);
	glm::vec3 tmpCamUp = glm::cross(camera_axis, camera_direction);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS) {
		//forward
		camera_trajectory = camera_trajectory + camera_direction;
	} else if(glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//backwards
		camera_trajectory = camera_trajectory - camera_direction;
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) {
		//left
		camera_trajectory = camera_trajectory - camera_axis;
	} else if(glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//right
		camera_trajectory = camera_trajectory + camera_axis;
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) != GLFW_PRESS) {
		//up
		camera_trajectory = camera_trajectory + tmpCamUp;
	} else if(glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		//down
		camera_trajectory = camera_trajectory - tmpCamUp;
	}

	//move the camera
	if(glm::length(camera_trajectory) > 0.1) {
		camera_trajectory = glm::normalize(camera_trajectory) * camera_speed;
		center = center + camera_trajectory;
		lookAt = center + camera_direction;
		up = glm::cross(camera_axis, camera_direction);
	}
}

void Camera::moveTo(glm::vec3 loc) {
	if(free) {
		glm::vec3 direction = lookAt - center;
		center = loc;
		lookAt = center + direction;
	}
}

glm::vec3 Camera::getCenter() {
	return center;
}

void Camera::setCenter(glm::vec3 c) {
	center = c;
}

glm::vec3 Camera::getLookAt() {
	return lookAt;
}

void Camera::setLookAt(glm::vec3 l) {
	lookAt = l;
}

glm::vec3 Camera::getUp() {
	return up;
}

void Camera::setUp(glm::vec3 u) {
	up = u;
}

bool Camera::getFreeCamStatus() {
	return free;
}

void Camera::setFreeCam(bool v) {
	free = v;
}

bool Camera::toggleFreeCam() {
	if(free) {
		free = !free;
		return false;
	}
	free = !free;
	return true;
}

Camera::Camera() {
	locked_to = NULL;
	free = true;
	center = glm::vec3(2, 2, 2);
	lookAt = glm::vec3(1, 0, 1);
	up = glm::vec3(0, 0, 1);
}

Camera::~Camera() { }
