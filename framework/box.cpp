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

Box::Box(glm::vec3 v, glm::vec3 w, std::string name, Color rgb):
	Shape(name, rgb),
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
