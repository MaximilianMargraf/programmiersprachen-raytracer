#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"

struct Light {
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	std::string name = "";
	Color color = Color(0.0, 0.0, 0.0);
	float brightness = 0.0;

	std::ostream& print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream& os, Light const& light);

#endif // LIGHT_HPP