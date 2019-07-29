#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "camera.hpp"
#include "light.hpp"
#include "material.hpp"
#include "shape.hpp"

struct Scene{
	std::shared_ptr<Material> find_material(std::string const&) const;
	std::shared_ptr<Shape> find_shape(std::string const&) const;
	std::shared_ptr<Light> find_light(std::string const&) const;
	std::shared_ptr<Camera> find_camera(std::string const&) const;

	std::map<std::string, std::shared_ptr<Material> > material_map;
	std::map<std::string, std::shared_ptr<Shape> > shape_map;
	std::map<std::string, std::shared_ptr<Light> > light_map;
	std::map<std::string, std::shared_ptr<Camera> > camera_map;

	std::string cam_name;
	std::string file_name;
	unsigned int xres;
	unsigned int yres;
};

#endif // SCENE_HPP