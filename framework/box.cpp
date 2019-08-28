#include "box.hpp"

Box::Box():
	Shape(),
	min{glm::vec3(0.0, 0.0, 0.0)},
	max{glm::vec3(1.0, 1.0, 1.0)}
	{}

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

/*
HitPoint Box::intersect(Ray const& r){
	Ray n{r};
	HitPoint hit;
	bool intersected = false;

	// Vector for saving the two t
	std::vector<float> intersection_param;

	float t = (min.x-n.origin.x)/(glm::normalize(n.direction)).x;
	glm::vec3 p_x = n.origin + t*(glm::normalize(n.direction)); 
	
	if(p_x.y <= max.y && p_x.y >= min.y
	&& p_x.z <= max.z && p_x.z >= min.z){
		intersected = true;
		intersection_param.push_back(t);
	hit.normal = glm::vec3{1.0, 0.0, 0.0};
	}

	float t_maxx = (max.x-n.origin.x)/(glm::normalize(n.direction)).x;
	glm::vec3 p_x2 = n.origin + t_maxx*(glm::normalize(n.direction)); 
	
	if(p_x2.y <= max.y && p_x2.y >= min.y
	&& p_x2.z <= max.z && p_x2.z >= min.z){
		intersected = true;
		intersection_param.push_back(t_maxx);
	hit.normal = glm::vec3{-1.0, 0.0, 0.0};
	}

	float t_miny = (min.y-n.origin.y)/(glm::normalize(n.direction)).y;
	glm::vec3 p_y = n.origin + t_miny*(glm::normalize(n.direction)); 
	
	if(p_y.x <= max.x && p_y.x >= min.x
	&& p_y.z <= max.z && p_y.z >= min.z){
		intersected = true;
		intersection_param.push_back(t_miny);
	hit.normal = glm::vec3{0.0, 1.0, 0.0};
	}

	float t_maxy = (max.y-n.origin.y)/(glm::normalize(n.direction)).y;
	glm::vec3 p_y2 = n.origin + t_maxy*(glm::normalize(n.direction)); 
	
	if(p_y2.x <= max.x && p_y2.x >= min.x
	&& p_y2.z <= max.z && p_y2.z >= min.z){
		intersected = true;
		intersection_param.push_back(t_maxy);
	hit.normal = glm::vec3{0.0, -1.0, 0.0};
	}
	
	float t_minz = (min.z-n.origin.z)/(glm::normalize(n.direction)).z;
	glm::vec3 p_z = n.origin + t_minz*(glm::normalize(n.direction)); 
	
	if(p_z.y <= max.y && p_z.y >= min.y
	&& p_z.x <= max.x && p_z.x >= min.x){
		intersected = true;
		intersection_param.push_back(t_minz);
	hit.normal = glm::vec3{0.0, 0.0, 1.0};
	}

	float t_maxz = (max.z-n.origin.z)/(glm::normalize(n.direction)).z;
	glm::vec3 p_z2 = n.origin + t_maxz*(glm::normalize(n.direction)); 
	
	if(p_z2.y <= max.y && p_z2.y >= min.y
	&& p_z2.x <= max.x && p_z2.x >= min.x){
		intersected = true;
		intersection_param.push_back(t_maxz);
	hit.normal = glm::vec3{0.0, 0.0, -1.0};
	}

	for(int i = 0; i < 2; i++){
		std::cout << intersection_param[i] << "\n";
	}
	return hit;
}
*/

HitPoint Box::intersect(Ray const& r){

	HitPoint hit;
	hit.intersected = true;

	float tmin = (min.x - r.origin.x) / glm::normalize(r.direction).x;
	float tmax = (max.x - r.origin.x) / glm::normalize(r.direction).x;
	hit.normal = glm::vec3{1.0, 0.0, 0.0};

	if(tmin > tmax){
		float tempx = tmin;
		tmin = tmax;
		tmax = tempx;
		//hit.normal = glm::vec3{1.0, 0.0, 0.0};
	}
	float tymin = (min.y - r.origin.y) / glm::normalize(r.direction).y;
	float tymax = (max.y - r.origin.y) / glm::normalize(r.direction).y;

	if(tymin > tymax){
		float tempy = tymin;
		tymin = tymax;
		tymax = tempy;
	}
	if((tmin > tymax) or (tymin > tmax)){
		hit.intersected = false;
	}

	if(tymin > tmin){
		tmin = tymin;
		hit.normal = glm::vec3{0.0, 1.0, 0.0};
	}
	if(tymax > tmax){
		tmax = tymax;
		//hit.normal = glm::vec3{0.0, -1.0, 0.0};
	}

	float tzmin = (min.z - r.origin.z) / glm::normalize(r.direction).z;
	float tzmax = (max.z - r.origin.z) / glm::normalize(r.direction).z;

	if(tzmin > tzmax){
		float tempz = tzmin;
		tzmin = tzmax;
		tzmax = tempz;
	}
	if((tmin > tzmax) or (tzmin > tmax)){
		hit.intersected = false;
	}

	if(tzmin > tmin){
		tmin = tzmin;
		hit.normal = glm::vec3{0.0, 0.0, 1.0};
	}
	if(tzmax > tmax){
		tmax = tzmax;
		//hit.normal = glm::vec3{0.0, 0.0, -1.0};
	}

	if(hit.intersected == true){
		hit.name = name_;
		hit.material = material;
		hit.direction = glm::normalize(r.direction);
		if(tmin < tmax){
			hit.distance = tmin;
			hit.intersection_point = r.origin + tmin * glm::normalize(r.direction);
		}
		if(tmin > tmax){
			hit.distance = tmax;
			hit.intersection_point = r.origin + tmax * glm::normalize(r.direction);
		}
	}
	return hit;
}


std::ostream& operator<<(std::ostream& os, Box const& s){
	s.print(os);
	return os;
}