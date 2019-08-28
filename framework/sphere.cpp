#include "sphere.hpp"

Sphere::Sphere():
	Shape(),
	center{glm::vec3(0.0, 0.0, 0.0)},
	radius{1}
	{
		world_transformation[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation[3] = glm::vec4{center, 1.0f};
	}
Sphere::Sphere(glm::vec3 v, float r):
	Shape(),
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}

		world_transformation[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation[3] = glm::vec4{center, 1.0f};
	}

Sphere::Sphere(glm::vec3 v, float r, std::string name, std::shared_ptr<Material> mat):
	Shape(name, mat),
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}

		world_transformation[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation[3] = glm::vec4{center, 1.0f};
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
    float distance = 0.0f;

    hitpoint.intersected = glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center, radius * radius, distance);
    hitpoint.name = name_;
    hitpoint.material = material;
    hitpoint.distance = distance;
    //std::cout<<center.x<<", "<<center.y<<", "<<center.z<<"\n";
    hitpoint.intersection_point = ray.origin + distance * glm::normalize(ray.direction);
    hitpoint.normal =  hitpoint.intersection_point - center;
    hitpoint.direction = glm::normalize(ray.direction);

    return hitpoint;
}

void Sphere::translate(glm::vec3 const& translation){
	center += translation;
	world_transformation[3] = glm::vec4{center, 1.0f};
}

// this function seems to not be called
void Sphere::scale(float const& factor){
	radius = radius * factor;
	//std::cout<<radius;
}

std::ostream& operator<<(std::ostream& os, Sphere const& s){
	s.print(os);
	return os;
}
