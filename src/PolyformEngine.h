#pragma once

//#include <vector>


class PolyformEngine {
private:
	bool windowed = false;
	bool scene_loaded = false;
	bool prepared = false;
	//VulkanRenderer* renderer;
	//std::vector<Entities> units_list;

public:
	void SetupWindow() {
		//renderer->prepare();
	}

	void LoadScene() {
		// Load text/binary/xml file with objects, placements, etc
	}

	void RunScene() {
		//renderer->renderLoop();
	}

	void Start() {
		if (!windowed) { SetupWindow(); }
		if (!scene_loaded) { LoadScene(); }

		RunScene();
	}

	PolyformEngine() {
		//renderer = new VulkanRasterizer();
	}
};