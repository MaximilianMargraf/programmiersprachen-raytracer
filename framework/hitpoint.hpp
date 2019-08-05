#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "material.hpp"
#include "color.hpp"

struct HitPoint
{
	bool intersected = false;
	float distance = 0.0;
	std::string name = "";
	std::shared_ptr<Material> material = nullptr;
	glm::vec3 intersection_point = glm::vec3{0.0, 0.0, 0.0};
	glm::vec3 direction = glm::vec3{0.0, 0.0, 0.0};
	glm::vec3 normal = glm::vec3{0.0, 0.0, 0.0};
};

#endif // HITPOINT_HPP