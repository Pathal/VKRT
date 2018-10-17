#include "Engine.h"

void Engine::run() {
	return;
}

Engine::Engine() {
	cam = new Camera();
}

Engine::~Engine() {
	if(cam != NULL) { delete cam; }
	for(int i = 0; i < entities.size(); i++) {
		if(entities.at(i) != NULL) {
			delete entities.at(i);
		}
	}
}
