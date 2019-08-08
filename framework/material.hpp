#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include <memory>
#include <string>

#include "color.hpp"

struct Material
{
	Material();
	Material(std::string);
	Material(std::string const& name_, Color const& ka_,
		Color const& kd_, Color const& ks_, float m_, float r_);
	~Material();

	std::ostream& print(std::ostream& os) const;

	bool operator ==(Material const& m);

	//Variablen
	std::string name;
	Color ka;
	Color kd;
	Color ks;
	float m;
	float r;
};

std::ostream& operator <<(std::ostream& os, Material const& mat);

#endif // MATERIAL_HPP