#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <set>

#include "material.hpp"

struct Scene{
	std::shared_ptr<Material> find_vec(std::string const&) const;
	std::shared_ptr<Material> find_set(std::string const&) const;
	std::shared_ptr<Material> find_map(std::string const&) const;

	std::vector<std::shared_ptr<Material>> mat_vec;
	std::set<std::shared_ptr<Material> > mat_set;
	std::map<std::string, std::shared_ptr<Material> > mat_map;
};

bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs);

#endif // SCENE_HPP