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
	HitPoint hp;

	// vector between origin and center
	glm::vec3 origin_center = center - ray.origin;

	// projecting this vector on the direction vector
	float skalar = glm::dot(origin_center, ray.direction);
	glm::vec3 least_distance = skalar * ray.direction;

	// distance to point with least distance from center of sphere
	float distance = glm::distance(least_distance, center);
	//float distance = sqrt(glm::dot(origin_center, origin_center) -
	//						glm::dot(least_distance, least_distance));

	//if this distance is > radius, the ray misses the sphere
	if(distance > radius){
		hp.intersected = false;
	}
	else{
		hp.intersected = true;
	}

	// vector from center to point with least distance
	glm::vec3 center_least = center - least_distance;

	// intersection point
	float length = sqrt(pow(radius, 2) - glm::dot(center_least, center_least));
	glm::vec3 intersection_point = least_distance - (length * ray.direction);

	hp.intersection_point = intersection_point;
	hp.name = name_;
	hp.direction = ray.direction;
	hp.distance = sqrt(glm::dot(hp.intersection_point, intersection_point));
	hp.mat = *material;

	return hp;
}

std::ostream& operator<<(std::ostream& os, Sphere const& s){
	s.print(os);
	return os;
}
