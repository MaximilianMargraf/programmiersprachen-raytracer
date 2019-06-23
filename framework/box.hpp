#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include <math.h>

#include "shape.hpp"

class Box : public Shape{
public:
	Box();
	Box(glm::vec3, glm::vec3);
	Box(glm::vec3, glm::vec3, std::string name, Color);

	glm::vec3 getMin() const;
	glm::vec3 getMax() const;

	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;

private:
	glm::vec3 min;
	glm::vec3 max;
};

std::ostream& operator<<(std::ostream& os, Box const& s);

#endif // BOX_HPP