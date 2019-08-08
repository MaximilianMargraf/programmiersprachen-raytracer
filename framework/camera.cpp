#include "camera.hpp"

Camera::Camera(std::string name_, float fov_):
	name{name_},
	fov_x{fov_}
	{}

Camera::Camera(std::string name_, float fov_, glm::vec3 pos_, glm::vec3 direction_, glm::vec3 up_):
	name{name_},
	fov_x{fov_},
	position{pos_},
	direction{direction_},
	up{up_}
	{}

std::ostream& Camera::print(std::ostream& os) const{
	os 
	<<name
	<<"\n Position: "<<position.x<<", "<<position.y<<", "<<position.z
	<<"\n Direction: "<<direction.x<<", "<<direction.y<<", "<<direction.z
	<<"\n Up-Vector: "<<up.x<<", "<<up.y<<", "<<up.z
	<<"\n Fov-x: "<<fov_x<<"\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Camera const& c){
	c.print(os);
	return os;
}