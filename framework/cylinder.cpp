#include "cylinder.hpp"

Cylinder::Cylinder():
    Shape(),
    p1_{0.0, 0.0, 0.0},
    p2_{0.0, 1.0, 0.0},
    radius_{0.0}
    {}

Cylinder::Cylinder(glm::vec3 p1, glm::vec3 p2, float radius):
    Shape(),
    p1_{p1},
    p2_{p2},
    radius_{radius}
    {}

Cylinder::Cylinder(glm::vec3 p1, glm::vec3 p2, float radius, std::string name, std::shared_ptr<Material> mat):
    Shape(name, mat),
    p1_{p1},
    p2_{p2},
    radius_{radius}
    {}

Cylinder::~Cylinder(){

}

float Cylinder::area() const{
    return 1.0;
}

float Cylinder::volume() const{
    return 1.0;
}

void Cylinder::translate(glm::vec3 const& translation){

}

void Cylinder::scale(glm::vec3 const& factor){

}

std::ostream& Cylinder::print(std::ostream& os) const{
	Shape::print(os);
	os << "Punkt 1: " << p1_.x << ", " << p1_.y << ", " << p1_.z << "\n"
    << "Punkt 2: " << p2_.x << ", " << p2_.y << ", " << p2_.z << "\n"
    << "Radius: " << radius_ << "\n";
	return os;
}