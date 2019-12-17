#include "VulkanRenderer.h"

const int sleep_iterations = 100;
const double sleep_time = 1e-9;

// OS specific macros for the example main entry points
#if defined(_WIN32)
VulkanCloth* render_instance;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (render_instance != NULL) {
		render_instance->handleMessages(hWnd, uMsg, wParam, lParam);
	}
	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	std::cout << "Staring up...\n";
	for (int32_t i = 0; i < __argc; i++) {
		VulkanCloth::args.push_back(__argv[i]);
	};
	render_instance = new VulkanCloth();
	std::cout << "Initializing Vulkan...\n";
	render_instance->initVulkan();
	std::cout << "Setting up the window...\n";
	render_instance->setupWindow(hInstance, WndProc);
	std::cout << "Preparing Assetts...\n";
	render_instance->prepare();
	std::cout << "Running...\n";
	render_instance->renderLoop();

	delete(render_instance);

	return 0;
}
#else
int main() {
	render_instance = new VulkanRasterizer();
	std::cout << "Initializing Vulkan...\n";
	render_instance->initVulkan();
	std::cout << "Setting up the window...\n";
	render_instance->setupWindow(hInstance, WndProc);
	std::cout << "Preparing Assetts...\n";
	render_instance->prepare();
	std::cout << "Running...\n";
	render_instance->renderLoop();

	delete(render_instance);

	return 0;
}
#endif