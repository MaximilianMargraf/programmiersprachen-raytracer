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
    HitPoint hit;
    const float EPSILON = 0.0000001;
    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = p2_ - p1_;
    edge2 = p3_ - p1_;
    h = glm::cross(ray.direction, edge2);
    a = glm::dot(edge1, h);
    //ray is parallel to triangle:
    if(a > -EPSILON && a < EPSILON) hit.intersected = false;
    f = 1.0/a;
    s = ray.origin - p1_;
    u = f * glm::dot(s, h);
    if(u < 0.0 || u > 1.0) hit.intersected = false;
    q = glm::cross(s, edge1);
    v = f * glm::dot(ray.direction, q);
    if (v < 0.0 || u + v > 1.0) hit.intersected = false;
    //find intersection point:
    float t = f * glm::dot(edge2, q);
    if(t > EPSILON){
        hit.intersected = true;
        hit.distance = t;
        hit.intersection_point = this->intersection_point(ray, hit.distance);
        hit.normal = this->normal();
        hit.material = material;
        hit.name = name_;
    }
    return hit;
}

glm::vec3 Triangle::intersection_point(Ray ray, float t){
    glm::vec3 intersection_point = ray.origin + t * ray.direction;
    return intersection_point;
}

glm::vec3 Triangle::normal(){
    glm::vec3 normal, edge1, edge2;
    edge1 = p2_ - p1_;
    edge2 = p3_ - p1_;
    normal = glm::normalize(glm::cross(edge1, edge2));
    return normal;
}

void Triangle::translate(glm::vec3 const& translation){
}

void Triangle::scale(glm::vec3 const& factor){
    
}