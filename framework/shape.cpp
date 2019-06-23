#include "shape.hpp"

Shape::Shape():
	name_{""},
	color{Color(0.0, 0.0, 0.0)}
	{
		std::cout<<"Called Shape default constructor\n";
	}

Shape::Shape(std::string name, Color rgb):
	name_{name},
	color{rgb}
	{
		std::cout<<"Called Shape value constructor\n";
	}

Shape::~Shape(){
	std::cout<<"Called Shape Destructor\n";
}

std::ostream& Shape::print(std::ostream& os) const{
	os <<"Name: "<<name_<<
		"\nColor: R"<<color.r<<", G "<<color.g<<", B "<<color.b<<"\n";
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
	s.print(os);
	return os;
}