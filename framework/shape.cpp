#include "shape.hpp"

Shape::Shape():
	name_{""}
	{}

Shape::Shape(std::string name, std::shared_ptr<Material> mat):
	name_{name},
	material{mat}
	{}

Shape::~Shape(){}

std::ostream& Shape::print(std::ostream& os) const{
	os <<"Name: "<<name_<<
	"\nMaterial: "<< material;
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
	s.print(os);
	return os;
}