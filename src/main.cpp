#include <stdexcept>

#include <iostream> 

#include "EngineEntity.h"
#include "Resources.h"
#include "VulkanRenderer.h"

const int sleep_iterations = 100;
const double sleep_time = 1e-9;

int main() {
	VulkanRenderer app;
	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}