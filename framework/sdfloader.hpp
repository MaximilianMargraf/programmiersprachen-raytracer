#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <glm/vec3.hpp>

#include "box.hpp"
#include "color.hpp"
//#include "light.hpp"
//#include "camera.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"

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
					scene.material_map[name] = mat;
				}

				if(keyword == "sphere"){
					std::string name;
					std::string mat;
					float x, y, z;
					float rad;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 pos = glm::vec3(x, y, z);

					ss>>rad;
					ss>>name;
					ss>>mat;

					std::shared_ptr<Shape> sphere(new Sphere(pos, rad, name, scene.find_material(mat)));
					scene.shape_map[name] = sphere;
				}

				if(keyword == "box"){
					std::string name;
					std::string mat;
					float x, y, z;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 min = glm::vec3(x, y, z);

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 max = glm::vec3(x, y, z);

					ss>>name;
					ss>>mat;

					std::shared_ptr<Shape> box(new Box(min, max, name, scene.find_material(mat)));
					scene.shape_map[name] = box;
				}

				/* Light not yet implemented
				if(keyword == "light"){
					std::string name;
					float x, y, z, brightness;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 pos = glm::vec3(x, y, z);

					ss>>x;
					ss>>y;
					ss>>z;
					Color color(x, y, z);

					ss>>brightness;

					std::shared_ptr<Light> light(new Light(name, pos, color, brightness);
					scene.light_map[name] = light;
				}*/

				/* Camera not yet implemented
				if(keyword == "camera"){
					std::string name;
					float fov-x;

					ss>>name
					ss>>fov-x;

					std::shared_ptr<Camera> camera(new Camera(name, fov-x);
					scene.camera_map[name] = camera;
				}*/
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