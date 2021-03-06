#ifndef BOX_HPP
#define BOX_HPP

#include <catch.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <math.h>
#include <cmath>
#include <vector>
#include <algorithm>

#include "shape.hpp"

class Box : public Shape{
public:
	Box();
	Box(glm::vec3, glm::vec3);
	Box(glm::vec3, glm::vec3, std::string name, std::shared_ptr<Material>);
	~Box();

	glm::vec3 getMin() const;
	glm::vec3 getMax() const;
	glm::vec3 calc_intersection_point(Ray const&, float);
	glm::vec3 calc_n(HitPoint const&);

	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;
	void translate(glm::vec3 const&) override;
	void scale(glm::vec3 const&) override;

	HitPoint intersect(Ray const&) override;

private:
	glm::vec3 min;
	glm::vec3 max;
};

std::ostream& operator<<(std::ostream& os, Box const& s);

#endif // BOX_HPP