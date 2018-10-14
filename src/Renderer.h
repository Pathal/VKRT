#pragma once

#include "Engine.h"

class Renderer {
public:
	virtual void init() = 0;
	virtual void drawFrame() = 0;
};