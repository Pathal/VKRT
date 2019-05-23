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
protected:
	bool dataOverlay;
public:
	void run(); //MUST BE IMPLEMENTED BY EACH RENDERER
	Camera* getCamera() { return cam; };
	EngineEntity* getEntity(int i) { return entities.at(i); }
	std::vector<EngineEntity*>* getEntitiesList() { return &entities; }
	unsigned int getEntitiesSize() { return entities.size(); }

	Engine();
	~Engine();
};