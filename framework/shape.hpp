#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <string>

#include "color.hpp"

class Shape{
public:
	Shape():
		name_{""},
		color{Color(0.0, 0.0, 0.0)}
		{}

	Shape(std::string name, Color rgb):
		name_{name},
		color{rgb}
		{}

	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual void printClassName() const{
		std::cout<<"Shape Class Object\n";
	}
	std::string getName(){return name_;};
	Color getColor(){return color;};

protected:
	std::string name_;
	Color color;
};

#endif // SHAPE_HPP