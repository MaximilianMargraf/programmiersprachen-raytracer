#include "scene.hpp"

std::shared_ptr<Material> Scene::find_vec(std::string const& name_) const{
	// initally nullptr
	std::shared_ptr<Material> ptr(nullptr);

	for(auto c : mat_vec){
		if(c->name == name_){
			ptr = c;
		}
	}

	return ptr;
}

std::shared_ptr<Material> Scene::find_set(std::string const& name_) const{
	// initally nullptr
	std::shared_ptr<Material> ptr(nullptr);
//	std::shared_ptr<Material> sPtr(new Material(name_));

	// this doesnt seem to work
//	auto it = mat_set.find(sPtr);

//	if(it != mat_set.end()){
//		ptr = *it;
//	}

	for( auto it : mat_set){
		if(it->name == name_){
			ptr = it;
		}
	}

	return ptr;
}

std::shared_ptr<Material> Scene::find_map(std::string const& name_) const{
	// initally nullptr
	std::shared_ptr<Material> ptr(nullptr);
	auto it = mat_map.find(name_);
	if(it != mat_map.end()){
		ptr = it->second;
	}

	return ptr;
}

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs){
	std::cout<<"lhs name: "<<lhs->name
			<<"\n rhs name: "<< rhs->name<<"\n";
	return lhs->name < rhs->name;
}