#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include "scene.hpp"
#include "sdfloader.hpp"

// executing the animation.cpp will take some sweet time depending on the rig
int main(int argc, char* argv[])
{
	int seconds = 2;
	int frames = 24 * seconds;

	std::string filepath = "../../files/animation.txt";
	Scene scene = sdfloader(filepath);
	// for every frame we need to alter the scene slightly
	for(float i = 0; i < frames; i++){
		float radius1 = 5;
		// convert degrees to radian for c++, needed for circular movement
		float angleDeg = (360/frames) * M_PI/180;
		glm::vec3 circle1 = glm::vec3{sin((angleDeg)*i)*radius1, 0, cos((angleDeg)*i)*radius1};

		Scene scene = sdfloader(filepath);

		// apply translation to sphere
		scene.find_shape("Sphere3")->translate(circle1);

		// scale up sphere in background
		float ff = 1 + (i / frames)*5;
		glm::vec3 factor = glm::vec3{ff, ff, ff};
		//std::cout<<"scale up sphere2 by "<<factor.x<<"\n";
		scene.find_shape("Sphere2")->scale(factor);

		// save the pic with a different filename each time
		scene.file_name = "animation"+std::to_string((int)i)+".ppm";

		Renderer renderer{scene};

		renderer.render();
	}

	// check the build/source 
	return 0;
}
