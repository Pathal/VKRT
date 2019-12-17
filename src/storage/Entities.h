#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Entities {
private:
	bool loaded = false;

	glm::mat4 trans;		// The full transformation matrix
	glm::mat4 scale_mat;
	glm::mat4 rot_mat;
	glm::mat4 trans_mat;

public:
	void updateModelMatrix() {
		trans = trans_mat * rot_mat * scale_mat;
	}

	void getTransformationMatrix(glm::mat4 matrix) {
		matrix = trans;
	}

	void resetTransformations() {
		trans = scale_mat = rot_mat = trans_mat = glm::mat4();
	}

	/*
	Individual Getters and Setters
	*/
	void setRotationMatrix(glm::mat4& matrix) {
		rot_mat = matrix;
		updateModelMatrix();
	}

	void setRotationMatrix(glm::vec3& axis, float angle) {
		rot_mat = glm::rotate(glm::mat4(), angle, axis);
		updateModelMatrix();
	}

	Entities() {
		//
	}
};