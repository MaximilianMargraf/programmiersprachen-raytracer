#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

#include "scene.hpp"
#include "sdfloader.hpp"

int main(int argc, char* argv[])
{
	std::string const filename = "./sphere.ppm";

	//std::string filepath = "/home/lyrrok/Documents/programmiersprachen-raytracer/files/scene.txt";
	std::string filepath = "/home/eric/Programmiersprachen_Uebungen/raytracer-collab/programmiersprachen-raytracer/files";
	Scene scene = sdfloader(filepath);

	Renderer renderer{scene};
	std::cout<<"Init Renderer worked\n";

	//create separate thread to see updates of pixels while rendering
	std::thread render_thread([&renderer]() {renderer.render();});

	Window window{{renderer.scene.xres, renderer.scene.yres}};

	while (!window.should_close()) {
		if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			window.close();
		}
		window.show(renderer.color_buffer());
	}

	//"join" threads, i.e. synchronize main thread with render_thread
	render_thread.join();
	return 0;
}
