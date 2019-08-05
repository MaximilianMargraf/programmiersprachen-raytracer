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
#include "color.hpp"

struct Scene{
	std::shared_ptr<Material> find_material(std::string const&) const;
	std::shared_ptr<Shape> find_shape(std::string const&) const;
	Light find_light(std::string const&) const;
	std::shared_ptr<Camera> find_camera(std::string const&) const;

	std::map<std::string, std::shared_ptr<Material> > material_map;
	std::map<std::string, std::shared_ptr<Shape> > shape_map;
	std::map<std::string, Light> light_map;
	std::map<std::string, std::shared_ptr<Camera> > camera_map;

	std::string cam_name = "";
	std::string file_name = "";
	unsigned int xres = 0;
	unsigned int yres = 0;
	Color ambient = Color{0.0,0.0, 0.0};
};

#endif // SCENE_HPP