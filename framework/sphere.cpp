#include "sphere.hpp"

Sphere::Sphere():
	center{glm::vec3(0.0, 0.0, 0.0)},
	radius{1}
	{}

Sphere::Sphere(glm::vec3 v, float r):
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}
	}

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
	return 4/3*M_PI * radius * radius * radius;
}
