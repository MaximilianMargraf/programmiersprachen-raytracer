#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "material.hpp"
#include "color.hpp"

struct HitPoint
{
	HitPoint():
		intersected{false},
		distance{0.0},
		name{""},
		mat{Material("",{0,0,0},{0,0,0},{0,0,0}, 0)},
		intersection_point{glm::vec3(0.0, 0.0, 0.0)},
		direction{glm::vec3(0.0, 0.0, 0.0)},
		normal{glm::vec3(0.0, 0.0, 0.0)}
		{}

	bool intersected;
	float distance;
	std::string name;
	Material mat;
	glm::vec3 intersection_point;
	glm::vec3 direction;
	glm::vec3 normal;
};

#endif // HITPOINT_HPP