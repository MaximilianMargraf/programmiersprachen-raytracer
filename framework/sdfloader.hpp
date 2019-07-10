#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <glm/vec3.hpp>

#include "color.hpp"
#include "material.hpp"
#include "scene.hpp"

Scene sdfloader(std::string const& filename)
{
	Scene scene;
	std::string line;
	std::ifstream myfile;
	myfile.open(filename);

	if (myfile.is_open()){
		std::cout<<"Opened file for reading\n";
		while (getline(myfile,line))
		{
			std::stringstream ss;
			ss << line;
			std::string keyword;
			ss>>keyword;

			//material, name, ka, kd, ks input
			if(keyword == "define"){
				ss>>keyword;

				if(keyword == "material"){
					float r, g, b;
					std::string name;
					float specular;
					ss>>name;

					ss>>r;
					ss>>g;
					ss>>b;
					Color ka(r, g, b);

					ss>>r;
					ss>>g;
					ss>>b;
					Color kd(r, g, b);

					ss>>r;
					ss>>g;
					ss>>b;
					Color ks(r, g, b);

					ss>>specular;

					std::shared_ptr<Material> mat(new Material(name, ka, kd, ks, specular));
					scene.mat_vec.push_back(mat);
					scene.mat_set.insert(mat);
					scene.mat_map[name] = mat;
				}
			}
		}
		myfile.close();
	}
	else{
		std::cout << "Datei konnte nicht geöffnet werden!";
	}

	return scene;
}

#endif //define SDFLOADER_HPP