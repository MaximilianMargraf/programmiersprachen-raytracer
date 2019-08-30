#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <glm/vec3.hpp>

#include "material.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"

class Shape{
public:
	Shape();
	Shape(std::string, std::shared_ptr<Material>);
	virtual ~Shape();

	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
	virtual HitPoint intersect(Ray const&) = 0;
	virtual void translate(glm::vec3 const&) = 0;
	virtual void scale(glm::vec3 const&) = 0;

	std::string getName() const {
		return name_;
	}

	std::string getMaterialName() const{
		return material->name;
	}

protected:
	std::string name_;
	std::shared_ptr<Material> material;
	// accumulated matrices
	glm::mat4 world_transformation_, world_transformation_inv_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // SHAPE_HPP