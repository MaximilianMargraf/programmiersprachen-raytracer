#include "triangle.hpp"

Triangle::Triangle():
    Shape(),
    p1_{0.0, 0.0, 0.0},
    p2_{0.0, 1.0, 0.0},
    p3_{0.0, 0.0, 3.0}
    {}

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3):
    Shape(),
    p1_{p1},
    p2_{p2},
    p3_{p3}
    {}

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, std::string name, std::shared_ptr<Material> mat):
    Shape(name, mat),
    p1_{p1},
    p2_{p2},
    p3_{p3}
    {}

Triangle::~Triangle(){

}

float Triangle::area() const{
    return 1.0;
}

float Triangle::volume() const{
    return 1.0;
}

std::ostream& Triangle::print(std::ostream& os) const{
	Shape::print(os);
	os << "Punkt 1: " << p1_.x << ", " << p1_.y << ", " << p1_.z << "\n"
    << "Punkt 2: " << p2_.x << ", " << p2_.y << ", " << p2_.z << "\n"
    << "Punkt 3: " << p3_.x << ", " << p3_.y << ", " << p3_.z << "\n";
	return os;
}

HitPoint Triangle::intersect(Ray const& ray){
    HitPoint hitpoint;
    Ray norm;
    norm.direction = glm::normalize(ray.direction);
    float distance = 0.0f;
    glm::vec3 dl;

    hitpoint.intersected = glm::intersectRayTriangle(ray.origin, norm.direction, p1_, p2_, p3_, dl);
    hitpoint.name = name_;
    //hitpoint.distance = distance;

    return hitpoint;
}

void Triangle::translate(glm::vec3 const& translation){
}

void Triangle::scale(float const& factor){
    
}