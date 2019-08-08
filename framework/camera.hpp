#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <string>

struct Camera {

	Camera(std::string, float);
	Camera(std::string, float, glm::vec3, glm::vec3, glm::vec3);

	std::ostream& print(std::ostream& os) const;

	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 direction = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 up = glm::vec3(0.0, 0.0, 0.0);
	std::string name = "";
	float fov_x = 90.0;
};

std::ostream& operator<<(std::ostream& os, Camera const& c);

#endif // CAMERA_HPP