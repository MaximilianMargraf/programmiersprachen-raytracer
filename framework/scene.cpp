#include "scene.hpp"

std::shared_ptr<Material> Scene::find_material(std::string const& name_) const{
	// initally nullptr
	std::shared_ptr<Material> ptr(nullptr);
	auto it = material_map.find(name_);
	if(it != material_map.end()){
		ptr = it->second;
	}

	return ptr;
}


std::shared_ptr<Shape> Scene::find_shape(std::string const& name_) const{
	// initally nullptr
	std::shared_ptr<Shape> ptr(nullptr);
	auto it = shape_map.find(name_);
	if(it != shape_map.end()){
		ptr = it->second;
	}

	return ptr;
}

Light Scene::find_light(std::string const& name_) const{
	Light light;
	auto it = light_map.find(name_);
	if(it != light_map.end()){
		light = it->second;
	}

	return light;
}


std::shared_ptr<Camera> Scene::find_camera(std::string const& name_) const{
	// initally nullptr
	std::shared_ptr<Camera> ptr(nullptr);
	auto it = camera_map.find(name_);
	if(it != camera_map.end()){
		ptr = it->second;
	}

	return ptr;
}