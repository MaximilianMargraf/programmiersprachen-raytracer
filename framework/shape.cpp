#include "shape.hpp"

Shape::Shape():
	name_{""}
	{
		std::cout<<"Called Shape default constructor\n";
	}

Shape::Shape(std::string name, std::shared_ptr<Material> mat):
	name_{name},
	material{mat}
	{
		std::cout<<"Called Shape value constructor\n";
	}

Shape::~Shape(){
	std::cout<<"Called Shape Destructor\n";
}

std::ostream& Shape::print(std::ostream& os) const{
	os <<"Name: "<<name_<<
	"\nMaterial: "<< material;
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
	s.print(os);
	return os;
}