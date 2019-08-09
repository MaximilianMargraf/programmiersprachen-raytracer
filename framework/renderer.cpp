// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
int depth = 3;

// How often we want to reflect from 
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
	{}

void Renderer::render()
{
	//std::cout<<"Starting rendering process\n";
	// width of the image plan for calculation = 1
	// horizontal image angle is the fovx of the camera
	//std::cout<<"Camera name: "<<cam<<"\n";
	float a = scene.find_camera(cam)->fov_x;
	//std::cout<<"Fov_x: "<<a<<"\n";

	// smallest distance from camera angle to image plane
	float distance = (width_/2)/tan((a/2)*M_PI / 180);

	// "mirror"
	float h = height_/2;
	float w = width_/2;

	// create ray through image plane
	Ray shooty;
	shooty.origin = scene.find_camera(scene.cam_name)->position;

	// from bottom left to top right
	// botom left is -(width/2)/width
	for (unsigned y = 0; y < height_; ++y) {
		for (unsigned x = 0; x < width_; ++x) {
			//std::cout<<"Y: "<<y<<", X: "<<x<<"\n";
			Pixel p(x,y);

			// Antialiasing !!!!! from coordinate go 0.5 in each direction (4 values)

			// determine direction of ray
			// (x-w)/width ensure a value of -0.5 to 0.5 according to the lecture
			shooty.direction = glm::vec3{(x-w)/width_, (y-h)/height_, -distance};
			shooty.direction = glm::normalize(shooty.direction);

			// include the camera transformation
			// this just changes the ray according to the camera transformation
			shooty.transformRay(scene.find_camera(scene.cam_name)->camTrans());

			//std::cout<<"Start raytracer.\n";
			p.color = raytrace(shooty);
			//std::cout<<"Raytracing finished\n";
			write(p);
		}
	}
	ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray) const{
	Color px(0.0, 0.0, 0.0);
	HitPoint hp, closest;
	closest.distance = 99999.0;

	for(auto it = scene.shape_map.begin(); it != scene.shape_map.end(); it++){
		hp = it->second->intersect(ray);
		// if there was an actual intersection and distance is smaller than before
		if(hp.intersected == true && hp.distance < closest.distance){
			closest = hp;
		}
	}

	// no intersection, return scene ambient color
	if(closest.distance == 99999.0){
		return scene.ambient;
	}
	// intersection ahead, do this with the closest hitpoint
	else{
		px = shade(closest);
		return px;
	}
}

Color Renderer::shade(HitPoint const& hit) const{
	//std::cout<<"Ǵet material information of HitPoint.\n";
	Color ka = hit.material->ka;
	Color kd = hit.material->ks;
	Color ks = hit.material->kd;

	//std::cout<<"Declaring most of the important variables\n";
	// Color of ambient light is simply multiplied with the c. of the material
	Color ltotal = scene.ambient * ka;

	// for diffuse lighting we need the normal of the point as well as the vector to the light
	float bias = 0.01;

	HitPoint hp;
	float light_norm_angle;
	float norm_cam_angle;

	std::vector<Light> lights_reached;
	std::vector<float> light_norm_angle_vec;
	std::vector<float> norm_cam_angle_vec;

	glm::vec3 direction_inverted = glm::normalize(-hit.direction);
	glm::vec3 norm = glm::normalize(hit.normal);

	// for every light in the scene
	for(auto it = scene.light_map.begin(); it != scene.light_map.end(); it++){
		// ray from the intersection point to the light source to check shadows
		Ray lightray;
		// vector to the light from intersection point
		glm::vec3 lightvec = it->second.position - hit.intersection_point;
		// move the hitpoint slightly from the actual object for better calculations
		lightray.origin = hit.intersection_point + norm * bias;
		lightray.direction = glm::normalize(lightvec);

		// iterate over all shapes to see if there is a shape between intersection and light
		for(auto jt = scene.shape_map.begin(); jt != scene.shape_map.end(); jt++){
			hp = jt->second->intersect(lightray);

			// if there was no intersection
			if(hp.intersected == false){
				lights_reached.push_back(it->second);
				light_norm_angle = std::max(0.0f, glm::dot(norm, lightvec));
				light_norm_angle_vec.push_back(light_norm_angle);

				glm::vec3 reflection = 2.0f * light_norm_angle * norm - lightvec;
				norm_cam_angle = std::max(0.0f, glm::dot(reflection, direction_inverted));
				norm_cam_angle_vec.push_back(pow((norm_cam_angle), hit.material->m));
			}
		}
	}

	// onto specular light, formula from the scripts for multiple light sources
	//std::cout<<"Calculate final color.\n";
	Color ss{0.0,0.0,0.0};
	for(int i = 0; i < lights_reached.size(); i++){
		ss += lights_reached[i].color * lights_reached[i].brightness *
						(kd * light_norm_angle_vec[i] + ks * norm_cam_angle_vec[i]);
	}

	// Reflection of light from other object, this will be executed up to 3 times
	if(depth > 0){
		--depth;
		// angle between camera ray and normal of intersection point
		float camera_normal = glm::dot(norm, direction_inverted);

		// reflected ray from object into scene
		glm::vec3 reflection = 2.0f * camera_normal * norm - direction_inverted;
		Ray reflec{hit.intersection_point + norm * bias, reflection};

		// raytrace the reflected ray to determine color
		Color reflection_c{0.0, 0.0, 0.0};
		reflection_c = raytrace(reflec);
		reflection_c = reflection_c * hit.material->r;

		// add color of reflection to the color of the object
		ss = ss*(1-hit.material->r)+reflection_c;
		ltotal = ss + scene.ambient;
		return ltotal;
	}

	// if all reflections are handled we can return the normal color
	ltotal += ss;
	return ltotal;
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