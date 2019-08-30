#include "sphere.hpp"

Sphere::Sphere():
	Shape(),
	center{glm::vec3(0.0, 0.0, 0.0)},
	radius{1}
	{
		world_transformation_[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation_[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation_[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
	}
Sphere::Sphere(glm::vec3 v, float r):
	Shape(),
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}

		world_transformation_[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation_[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation_[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
	}

Sphere::Sphere(glm::vec3 v, float r, std::string name, std::shared_ptr<Material> mat):
	Shape(name, mat),
	center{v},
	radius{r}
	{
		if(r < 0){
			radius = 0;
		}

		world_transformation_[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation_[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation_[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
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

HitPoint Sphere::intersect(Ray const& rey){
	HitPoint hitpoint;
	float distance = 0.0f;

	// apply inverse of the matrix to the ray
	Ray ray = transformRay(world_transformation_inv_, rey);

	// do intersection with ray in the objects coordinate system
	hitpoint.intersected = glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center, radius * radius, distance);
	hitpoint.name = name_;
	hitpoint.material = material;
	hitpoint.distance = distance;

	hitpoint.intersection_point = ray.origin + distance * glm::normalize(ray.direction);
	hitpoint.normal =  hitpoint.intersection_point - center;

	// transform intersection point and normal back into worldcoor.
	glm::vec4 h_normal = glm::vec4(hitpoint.normal, 0.0f);
	glm::vec3 b_normal = glm::vec3{glm::transpose(world_transformation_inv_)*h_normal};
	hitpoint.normal = glm::normalize(b_normal);
	// correct intersection point is M * p
	hitpoint.intersection_point = glm::vec3(world_transformation_* glm::vec4{hitpoint.intersection_point, 1.0f});

	return hitpoint;
}

void Sphere::translate(glm::vec3 const& translation){
	// center += translation;
	// add the translation to the last row of the matrix
	glm::mat4 trans;
	trans[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
	trans[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
	trans[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
	trans[3] = glm::vec4{translation.x, translation.y, translation.z, 1.0f};
	world_transformation_ = world_transformation_ * trans;
	world_transformation_inv_ =  glm::inverse(world_transformation_);
}

// this function seems to not be called
void Sphere::scale(glm::vec3 const& factor){
	//radius = radius * factor.x;
	//std::cout<<radius;
	glm::mat4 scale;
	scale[0] = glm::vec4{factor.x, 0.0f, 0.0f, 0.0f};
	scale[1] = glm::vec4{0.0f, factor.y, 0.0f, 0.0f};
	scale[2] = glm::vec4{0.0f, 0.0f, factor.z, 0.0f};
	scale[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
	world_transformation_ = scale * world_transformation_;
	world_transformation_inv_ = glm::inverse(world_transformation_);
	//std::cout<<"Sphere Position: "<<center.x<<", "<<center.y<<", "<<center.z<<"\n";
}

std::ostream& operator<<(std::ostream& os, Sphere const& s){
	s.print(os);
	return os;
}
