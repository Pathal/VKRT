#pragma once

#include <vector>

#include "Camera.h"
#include "Renderer.h"

class Engine {
private:
	Camera* cam;
	std::vector<EngineEntity*> entities;
	//renderer reference here
	//Renderer* render;
public:
	Camera* getCamera() { return cam; };
	EngineEntity* getEntity(int i) { return entities.at(i); }
	std::vector<EngineEntity*>* getEntitiesList() { return &entities; }
	unsigned int getEntitiesSize() { return entities.size(); }

	Engine();
	~Engine();
};