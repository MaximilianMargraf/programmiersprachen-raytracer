#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>
#include <string>

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
	virtual HitPoint intersect(Ray const&, float const&) = 0;

	std::string getName() const {
		return name_;
	}

protected:
	std::string name_;
	std::shared_ptr<Material> material;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // SHAPE_HPP