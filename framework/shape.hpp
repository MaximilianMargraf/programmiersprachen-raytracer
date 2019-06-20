#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

class Shape{
public:
	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual void printClassName() const{
		std::cout<<"Shape Class Object\n";
	}
};

#endif // SHAPE_HPP