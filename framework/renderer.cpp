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
	float a = scene.find_camera(cam)->fov_x;

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
			Pixel p(x,y);

			// Antialiasing: from coordinate go 0.5 in each direction (4 values)
			for(float i = 0.0f; i<1.0f; i += 0.5f){
				for(float j = 0.0f; j<1.0f; j += 0.5f){
					float xa = (float)x + i;
					float ya = (float)y + j;

					// determine direction of ray
					shooty.direction = glm::vec3{(xa-w), (ya-h), -distance};
					shooty.direction = glm::normalize(shooty.direction);

					// this just changes the ray according to the camera transformation
					shooty.transformRay(scene.find_camera(scene.cam_name)->camTrans());

					// we interpolate with 4 color values
					p.color += raytrace(shooty) * 0.25f;
				}
			}
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
		px = px/(px+1);
		return px;
	}
}

Color Renderer::shade(HitPoint const& hit) const{
	//std::cout<<"Ǵet material information of HitPoint.\n";
	Color ka = hit.material->ka;
	Color kd = hit.material->kd;
	Color ks = hit.material->ks;

	// Color of ambient light is simply multiplied with the c. of the material
	Color ltotal = scene.ambient * ka;

	// for diffuse lighting we need the normal of the point as well as the vector to the light
	float bias = 0.01;

	HitPoint hp;
	float light_norm_angle;
	float norm_cam_angle;

	glm::vec3 direction_inverted = glm::normalize(-hit.direction);
	glm::vec3 norm = glm::normalize(hit.normal);

	// do this to check the normals of the shapes
	//return Color{(norm.x+1)/2,(norm.y+1)/2,(norm.z+1)/2};

	// for every light in the scene
	for(auto it = scene.light_map.begin(); it != scene.light_map.end(); it++){
		// ray from the intersection point to the light source to check shadows
		Ray lightray;
		// vector to the light from intersection point
		glm::vec3 lightvec = it->second.position - hit.intersection_point;
		// move the hitpoint slightly from the actual object for better calculations
		lightray.origin = hit.intersection_point + norm * bias;
		lightray.direction = glm::normalize(lightvec);
		//return Color{(lightray.direction.x+1)/2,(lightray.direction.y+1)/2,(lightray.direction.z+1)/2};

		// iterate over all shapes to see if there is a shape between intersection and light
		for(auto jt = scene.shape_map.begin(); jt != scene.shape_map.end(); jt++){
			hp = jt->second->intersect(lightray);
			if(hp.intersected) {
				break;
			}
		}

		// if there was no intersection
		if(hp.intersected == false){
			light_norm_angle = std::max(0.0f, glm::dot(norm, lightray.direction));
			//return Color{light_norm_angle, light_norm_angle , light_norm_angle};

			glm::vec3 reflection = glm::reflect(-lightray.direction, norm);
			norm_cam_angle = std::max(0.0f, glm::dot(reflection, direction_inverted));
			norm_cam_angle = pow(norm_cam_angle, hit.material->m);
			//return Color{norm_cam_angle, norm_cam_angle , norm_cam_angle};
			
			ltotal += it->second.color * it->second.brightness *
					(kd * light_norm_angle + ks * norm_cam_angle);
		}
		
	}

	// Reflection of light from other object, this will be executed up to 3 times
	if(depth > 0){
		//std::cout<<"Depth: "<<depth<<"\n";
		--depth;
		Color rs{0.0, 0.0, 0.0};
		// angle between camera ray and normal of intersection point
		float camera_normal = std::max(0.0f, glm::dot(norm, direction_inverted));

		// reflected ray from camera to object into scene
		glm::vec3 reflection = glm::normalize(2.0f * camera_normal * norm - direction_inverted);
		Ray reflec{hit.intersection_point + norm * bias, reflection};

		// raytrace the reflected ray to determine color
		Color reflection_c{0.0, 0.0, 0.0};
		reflection_c = raytrace(reflec);
		reflection_c = reflection_c * hit.material->r;

		ltotal += reflection_c;
		return ltotal;
	}

	depth = 3;
	// if all reflections are handled we can return the normal color
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