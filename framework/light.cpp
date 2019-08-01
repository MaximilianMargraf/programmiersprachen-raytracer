#include "light.hpp"

std::ostream& Light::print(std::ostream& os) const{
	os 
	<<name
	<<"\n Position: "<<position.x<<", "<<position.y<<", "<<position.z
	<<"\n Color: "<<color.r<<", "<<color.g<<", "<<color.b
	<<"\n Brightness: "<<brightness<<"\n";
}


std::ostream& operator<<(std::ostream& os, Light const& light){
	light.print(os);
	return os;
}