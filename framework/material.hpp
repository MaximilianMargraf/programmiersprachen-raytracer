#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include <string>

#include "color.hpp"

struct Material
{
	Material();
	Material(std::string const& name_, Color const& ka_,
		Color const& kd_, Color const& ks_, float m_);
	~Material();

	std::ostream& print(std::ostream& os) const;

	//Variablen
	std::string name;
	Color ka;
	Color kd;
	Color ks;
	float m;
};

std::ostream& operator <<(std::ostream& os, Material const& mat);

#endif