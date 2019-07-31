#include "sphere.hpp"

Sphere::Sphere():
	Shape(),
	center{glm::vec3(0.0, 0.0, 0.0)},
	radius{1}
	{}

Sphere::Sphere(glm::vec3 v, float r):
	Shape(),
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}
	}

Sphere::Sphere(glm::vec3 v, float r, std::string name, std::shared_ptr<Material> mat):
	Shape(name, mat),
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}
	}

Sphere::~Sphere(){}

glm::vec3 Sphere::getCenter() const{
	return center;
}

float Sphere::getRadius() const{
	return radius;
}

float Sphere::area() const{
	return 4 * M_PI * radius * radius;
}

float Sphere::volume() const{
	return (4* M_PI * pow(radius, 3))/3;
}

std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	os << "Center: "<<center.x<<", "<<center.y<<", "<<center.z<<
		"\nRadius:"<<radius<<"\n";
	return os;
}

HitPoint Sphere::intersect(Ray const& ray){
    HitPoint hitpoint;
    Ray norm;
    norm.direction = glm::normalize(ray.direction);
    float distance = 0.0f;

    hitpoint.intersected = glm::intersectRaySphere(ray.origin, norm.direction, center, radius * radius, distance);
    hitpoint.name = name_;
    //hitpoint.color = color_;
    hitpoint.distance = distance;

    return hitpoint;
}


std::ostream& operator<<(std::ostream& os, Sphere const& s){
	s.print(os);
	return os;
}
