#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <string>

#include "color.hpp"

class Shape{
public:
	Shape();
	Shape(std::string name, Color rgb);
	virtual ~Shape();

	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;

	std::string getName() const {
		return name_;
	}

	Color getColor() const {
		return color;
	}

protected:
	std::string name_;
	Color color;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif // SHAPE_HPP