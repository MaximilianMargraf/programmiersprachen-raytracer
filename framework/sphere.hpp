#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <math.h>

#include "hitpoint.hpp"
#include "ray.hpp"
#include "shape.hpp"

class Sphere : public Shape{
public:
	Sphere();
	Sphere(glm::vec3, float);
	Sphere(glm::vec3, float, std::string, std::shared_ptr<Material>);
	~Sphere();

	glm::vec3 getCenter() const;
	float getRadius() const;

	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;
	void translate(glm::vec3 const&) override;
	void scale(glm::vec3 const&) override;

	HitPoint intersect(Ray const&) override;

private:
	glm::vec3 center;
	float radius;
};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif // SPHERE_HPP