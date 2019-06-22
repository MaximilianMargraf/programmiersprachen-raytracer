#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <math.h>

#include "shape.hpp"

class Sphere : public Shape{
public:
	Sphere();
	Sphere(glm::vec3, float);
	Sphere(glm::vec3, float, std::string, Color);

	glm::vec3 getCenter() const;
	float getRadius() const;

	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;

private:
	glm::vec3 center;
	float radius;
};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif // SPHERE_HPP