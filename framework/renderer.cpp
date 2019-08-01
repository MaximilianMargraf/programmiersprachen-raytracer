// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
	width_(w),
	height_(h),
	color_buffer_(w*h, Color(0.0, 0.0, 0.0)),
	filename_(file),
	ppm_(width_, height_)
	{}

Renderer::Renderer(Scene const& scene_):
	width_(scene_.xres),
	height_(scene_.yres),
	color_buffer_(scene_.xres*scene_.yres, Color(0.0, 0.0, 0.0)),
	filename_(scene_.file_name),
	cam(scene_.cam_name),
	ppm_(scene_.xres, scene_.yres),
	scene(scene_)
	{
		std::cout<<"Scene camera name: "<<scene_.cam_name<<"\n";
		std::cout<<"Camera name: "<<cam<<"\n";
	}

void Renderer::render()
{
	std::cout<<"Starting rendering process\n";
	// calculate the distance of the camera to the near plane
	// width of the image plan for calculation = 1
	// horizontal image angle is the fovx of the camera
	std::cout<<"Camera name: "<<cam<<"\n";
	float a = scene.find_camera(cam)->fov_x;
	std::cout<<"Fov_x: "<<a<<"\n";


	// smallest distance from camera angle to image plane
	float distance = (width_/2)/tan((a/2)*M_PI / 180);

	// "mirror"
	float h = height_/2;
	float w = width_/2;

	// create ray through image plane
	Ray shooty;
	shooty.origin = scene.find_camera(scene.cam_name)->position;

	// from bottom left to top right
	for (unsigned y = 0; y < height_; ++y) {
		for (unsigned x = 0; x < width_; ++x) {
			std::cout<<"Y: "<<y<<", X: "<<x<<"\n";
			Pixel p(x,y);

			shooty.direction = glm::normalize(glm::vec3{w/width_, h/height_, -distance});
			std::cout<<"Introduced the normalized direction\n";

			//p.color = raytrace(shooty);
			p.color = Color(0.0, 0.0, 0.0);
			std::cout<<"R: "<<p.color.r<<", G: "<<p.color.g<<", B: "<<p.color.b<<"\n\n";
			write(p);
			std::cout<<"Written the pixel, now onto next.\n";
		}
	}
	ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray) const{
	// List of Hitpoints, we need the one with the smallest distance
	std::vector<HitPoint> hits;
	Color px(0.0, 0.0, 0.0);
	HitPoint hp, closest;
	closest.distance = 9999.0;

	for(auto it = scene.shape_map.begin(); it != scene.shape_map.end(); it++){
		hp = it->second->intersect(ray);
		std::cout<<"Check if Ray intersects with Shape: "<<hp.name<<"\n";
		// if there was an actual intersection add the HitPoint to the vector
		if(hp.intersected == true){
			hits.push_back(hp);
			std::cout<<"Elements in intersection list: "<<hits.size()<<"\n";
		}
		else{
			std::cout<<hp.name<<"Did not intersect with Ray\n";
		}
	}

	// only HitPoint with closest distance needed
	for(auto h : hits){
		if(h.distance <= closest.distance){
			closest = h;
		}
	}

	// now closest is the hitpoint with the smallest distance to camera, we use it for color calculation
	px = shade(closest);

	return px;
}

Color Renderer::shade(HitPoint const& hit) const{
	Color ka = hit.mat.ka;
	Color kd = hit.mat.ks;
	Color ks = hit.mat.kd;

	Color Sa = scene.find_light("Ambient").color;

	Color L_amb = Sa * ka;

	return L_amb;
}

void Renderer::write(Pixel const& p)
{
	// flip pixels, because of opengl glDrawPixels
	size_t buf_pos = (width_*p.y + p.x);
	if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
		std::cerr << "Fatal Error Renderer::write(Pixel p) : "
			<< "pixel out of ppm_ : "
			<< (int)p.x << "," << (int)p.y
			<< std::endl;
	} else {
		color_buffer_[buf_pos] = p.color;
	}

	ppm_.write(p);
}