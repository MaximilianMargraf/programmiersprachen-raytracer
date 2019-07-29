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
	width_(scene.xres),
	height_(scene.yres),
	color_buffer_(scene.xres*scene.yres, Color(0.0, 0.0, 0.0)),
	filename_(scene.file_name),
	cam{scene.cam_name},
	ppm_(scene.xres, scene.yres),
	scene{scene}
	{}

void Renderer::render()
{
	std::size_t const checker_pattern_size = 20;

	for (unsigned y = 0; y < height_; ++y) {
		for (unsigned x = 0; x < width_; ++x) {
			Pixel p(x,y);
			if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
				p.color = Color(0.0, 1.0, float(x)/height_);
			} else {
				p.color = Color(1.0, 0.0, float(y)/width_);
			}

			write(p);
		}
	}
	ppm_.save(filename_);

	// calculate the distance of the camera to the near plane
	// width of the image plan for calculation = 1
	// horizontal image angle is the fovx of the camera
	float a = scene.find_camera(cam)->fov_x;

	// calculate last angle of triangle
	float b = 90 - a/2;
	// smallest distance from camera angle to image plane
	float distance = sin(b)/(2*sin(a/2));

	// List of Hitpoints, we need the one with the smallest distance

	for (unsigned y = 0; y < height_; ++y) {
		for (unsigned x = 0; x < width_; ++x) {
			Pixel p(x,y);
			/*

			for(auto c : scene.shape_map){
				p.color = raytrace stuff	
			}
			*/

			write(p);
		}
	}
	ppm_.save(filename_);
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