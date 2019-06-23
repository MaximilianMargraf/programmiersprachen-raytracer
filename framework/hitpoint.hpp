#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <string>

#include "color.hpp"

struct HitPoint
{
	HitPoint():
		intersected{false},
		distance{0.0},
		name{""},
		color{Color(0.0, 0.0, 0.0)},
		intersection_point{glm::vec3(0.0, 0.0, 0.0)},
		direction_vec{glm::vec3(0.0, 0.0, 0.0)}
		{}

	bool intersected;
	float distance;
	std::string name;
	Color color;
	glm::vec3 intersection_point;
	glm::vec3 direction_vec;
};

#endif // HITPOINT_HPP