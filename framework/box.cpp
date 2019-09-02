#include "box.hpp"

Box::Box():
	Shape(),
	min{glm::vec3(0.0, 0.0, 0.0)},
	max{glm::vec3(1.0, 1.0, 1.0)}
	{
		world_transformation_[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation_[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation_[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
		world_transformation_inv_ = glm::inverse(world_transformation_);
	}

Box::Box(glm::vec3 v, glm::vec3 w):
	Shape(),
	min{v},
	max{w}
	{
		float tmp = 0.0;
		if(max.x < min.x){
			tmp = max.x;
			max.x = min.x;
			min.x = tmp;
		}
		if(max.y < min.y){
			tmp = max.y;
			max.y = min.y;
			min.y = tmp;
		}
		if(max.z < min.z){
			tmp = max.z;
			max.z = min.z;
			min.z = tmp;
		}
		world_transformation_[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation_[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation_[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
		world_transformation_inv_ = glm::inverse(world_transformation_);
	}

Box::Box(glm::vec3 v, glm::vec3 w, std::string name, std::shared_ptr<Material> mat):
	Shape(name, mat),
	min{v},
	max{w}
	{
		float tmp = 0.0;
		if(max.x < min.x){
			tmp = max.x;
			max.x = min.x;
			min.x = tmp;
		}
		if(max.y < min.y){
			tmp = max.y;
			max.y = min.y;
			min.y = tmp;
		}
		if(max.z < min.z){
			tmp = max.z;
			max.z = min.z;
			min.z = tmp;
		}
		world_transformation_[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		world_transformation_[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
		world_transformation_[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		world_transformation_[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
		world_transformation_inv_ = glm::inverse(world_transformation_);
	}

Box::~Box(){}

glm::vec3 Box::getMin() const{
	return min;
}

glm::vec3 Box::getMax() const{
	return max;
}

float Box::area() const{
	float length = abs(max.x - min.x);
	float width = abs(max.y - min.y);
	float height = abs(max.z - min.y);
	return 2 * length * width + 2 * length * height + 2 * width * height;
}

float Box::volume() const{
	float length = abs(max.x - min.x);
	float width = abs(max.y - min.y);
	float height = abs(max.z - min.z);
	return length * width * height;
}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	os << "Min: "<<min.x<<", "<<min.y<<", "<<min.z<<
		"\nMax: "<<max.x<<", "<<max.y<<", "<<max.z<<"\n";
	return os;
}

HitPoint Box::intersect(Ray const& r){

	HitPoint hit;
	Ray ray = transformRay(world_transformation_inv_, r);

	float tmin = -INFINITY, tmax = INFINITY;

	float t1 = (min.x - ray.origin.x)/ray.direction.x;
	float t2 = (max.x - ray.origin.x)/ray.direction.x;
	tmin = std::max(tmin,std::min(t1,t2));
	tmax = std::min(tmax,std::max(t1,t2));

	t1 = (min.y - ray.origin.y)/ray.direction.y;
	t2 = (max.y - ray.origin.y)/ray.direction.y;
	tmin = std::max(tmin,std::min(t1,t2));
	tmax = std::min(tmax,std::max(t1,t2));

	t1 = (min.z - ray.origin.z)/ray.direction.z;
	t2 = (max.z - ray.origin.z)/ray.direction.z;
	tmin = std::max(tmin,std::min(t1,t2));
	tmax = std::min(tmax,std::max(t1,t2));

	if (tmax > std::max(0.0F, tmin))
	{
		hit.distance = sqrt(tmin*tmin*(
			ray.direction.x*ray.direction.x +
			ray.direction.y*ray.direction.y +
			ray.direction.z*ray.direction.z ));

		hit.intersection_point = this->calc_intersection_point(ray, hit.distance);
		hit.intersected = true;
		hit.material = material;
		hit.normal = this->calc_n(hit);
		hit.name = name_;
		hit.intersection_point = glm::vec3(world_transformation_*
									glm::vec4(hit.intersection_point,1.0));
		hit.normal = glm::normalize(glm::vec3(
				glm::transpose(world_transformation_inv_)*glm::vec4(hit.normal, 0.0)));
	}
	//std::cout<<"return HitPoint\n";
	return hit;
}

void Box::translate(glm::vec3 const& translation){
	min += translation;
	max += translation;
}

void Box::scale(glm::vec3 const& factor){
	
}

std::ostream& operator<<(std::ostream& os, Box const& s){
	s.print(os);
	return os;
}

glm::vec3 Box::calc_intersection_point(Ray const& ray, float distance){
	glm::vec3 s_pt{ray.origin + ray.direction*distance};
	return s_pt;
}

// get the correct normal depending on which size was hit
glm::vec3 Box::calc_n(HitPoint const& hit){
	auto surface_pt = hit.intersection_point; 
	if(surface_pt.x == Approx(min.x))
	{
		return glm::vec3{-1.0,0.0,0.0};
	}
	if(surface_pt.y == Approx(min.y))
	{
		return glm::vec3{0.0,-1.0,0.0};
	}
	if(surface_pt.z == Approx(min.z))
	{
		return glm::vec3{0.0,0.0,-1.0};
	}
	if(surface_pt.x == Approx(max.x))
	{
		return glm::vec3{1.0,0.0,0.0};
	}
	if(surface_pt.y == Approx(max.y))
	{
		return glm::vec3{0.0,1.0,0.0};
	}
	if(surface_pt.z == Approx(max.z))
	{
		return glm::vec3{0.0,0.0,1.0};
	}
}