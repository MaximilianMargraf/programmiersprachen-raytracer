#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <glm/vec3.hpp>

#include "box.hpp"
#include "color.hpp"
#include "light.hpp"
#include "camera.hpp"
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
		//std::cout<<"Opened file for reading\n";
		while (getline(myfile,line))
		{
			std::stringstream ss;
			ss << line;
			std::string keyword;
			ss>>keyword;

			if(keyword == "define"){
				ss>>keyword;

				if(keyword == "material"){
					float r, g, b;
					std::string name;
					float specular, reflection;
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
					ss>>reflection;

					std::shared_ptr<Material> mat(new Material(name, ka, kd, ks, specular, reflection));
					scene.material_map[name] = mat;
					//std::cout<<"Loaded material: "<<name<<".\n";
				}

				if(keyword == "sphere"){
					std::string name, mat;
					float x, y, z, rad;

					ss>>name;
					ss>>mat;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 pos = glm::vec3(x, y, z);

					ss>>rad;

					std::shared_ptr<Shape> sphere(new Sphere(pos, rad, name, scene.find_material(mat)));
					scene.shape_map[name] = sphere;
					//std::cout<<"Loaded sphere: "<<name<<".\n";
				}

				if(keyword == "box"){
					std::string name, mat;
					float x, y, z;

					ss>>name;
					ss>>mat;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 min = glm::vec3(x, y, z);

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 max = glm::vec3(x, y, z);

					std::shared_ptr<Shape> box(new Box(min, max, name, scene.find_material(mat)));
					scene.shape_map[name] = box;
					//std::cout<<"Loaded box: "<<name<<".\n";
				}

				if(keyword == "light"){
					std::string name;
					float x, y, z, brightness;

					ss>>name;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 pos = glm::vec3(x, y, z);

					ss>>x;
					ss>>y;
					ss>>z;
					Color color(x, y, z);

					ss>>brightness;

					Light light;
					light.name = name;
					light.position = pos;
					light.color = color;
					light.brightness = brightness;
					//std::cout<<"Light got its values.\n";

					scene.light_map[name] = light;
					//std::cout<<"Loaded light: "<<name<<".\n";
				}

				if(keyword == "camera"){
					std::string name;
					float fov_x, x, y, z;

					ss>>name;
					ss>>fov_x;

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 position = glm::vec3{x, y, z}; 

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 direction = glm::vec3{x, y, z};

					ss>>x;
					ss>>y;
					ss>>z;
					glm::vec3 up = glm::vec3{x, y, z};

					std::shared_ptr<Camera> camera(new Camera(name, fov_x, position, direction, up));
					scene.camera_map[name] = camera;
					//std::cout<<"Loaded camera: "<<name<<".\n";
				}
			}// define keyword

			if(keyword == "render"){
				ss>>scene.cam_name;
				ss>>scene.file_name;
				ss>>scene.xres;
				ss>>scene.yres;
				//std::cout<<"Loaded renderer.\n";
			}

			if(keyword == "ambient"){
				float x, y, z;
				ss>>x;
				ss>>y;
				ss>>z;
				Color color(x, y, z);
				scene.ambient = color;
				//std::cout<<"Loaded ambient light.\n";
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