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

glm::mat4 Camera::camTrans() const{
	// from the scrips: position, u, n and up needed
	// u is orthogonal to up and n
	// v is orthogonal to u and n
	glm::vec3 n = glm::normalize(direction);
	glm::vec3 up_ = glm::normalize(up);

	glm::vec3 u = glm::normalize(glm::cross(n, up_));
	glm::vec3 v = glm::normalize(glm::cross(u, n));

	// create the mat4 with the camera stuff
	glm::mat4 cam;
	cam[0] = glm::vec4{u, 0.0f};
	cam[1] = glm::vec4{v, 0.0f};
	cam[2] = glm::vec4{-n, 0.0f};
	cam[3] = glm::vec4{position, 1.0f};
	return cam;
}

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