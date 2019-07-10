#include "material.hpp"

Material::Material():
	name{""},
	ka{Color(0.0, 0.0, 0.0)},
	kd{Color(0.0, 0.0, 0.0)},
	ks{Color(0.0, 0.0, 0.0)},
	m{1.0}
	{}

Material::Material(std::string const& name_, Color const& ka_,
	Color const& kd_, Color const& ks_, float m_):
	name{name_},
	ka{ka_},
	kd{kd_},
	ks{ks_},
	m{m_}
	{}

Material::~Material(){
	std::cout<<"Called Material destructor\n";
}

std::ostream& Material::print(std::ostream& os) const{
	os <<"Name: "<< name << "\n"
	<<"ka: "<< ka << "\n"
	<<"kd: "<< kd << "\n"
	<<"ks: "<< ks << "\n"
	<<"Specular Exponent: "<< m  << "\n";
	return os;
}

std::ostream& operator <<(std::ostream& os, Material const& mat){
	mat.print(os);
	return os;
}
