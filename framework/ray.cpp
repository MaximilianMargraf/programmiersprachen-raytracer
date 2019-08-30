#include "ray.hpp"

Ray transformRay(glm::mat4 const& mat, Ray const& ray){
	glm::vec4 a {ray.origin, 1.0f};
	glm::vec4 b {ray.direction, 0.0f};

	Ray rey;
	rey.origin = glm::vec3{mat * a};
	rey.direction = glm::normalize(glm::vec3{mat * b});
	return rey;
}