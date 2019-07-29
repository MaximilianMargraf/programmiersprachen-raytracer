#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>

#include "box.hpp"
#include "hitpoint.hpp"
#include "material.hpp"
#include "sdfloader.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"

// task 5.2
TEST_CASE ("Test sphere class", "[Sphere]"){
	// test default constructor
	std::unique_ptr<Sphere> s1(new Sphere());
	REQUIRE(s1->getRadius() == 1);
	REQUIRE(s1->getCenter() == glm::vec3(0.0, 0.0, 0.0));
	REQUIRE(s1->area() == Approx(12.56637));
	REQUIRE(s1->volume() == Approx(4.18879));
	REQUIRE(s1->getName() == "");

	// test value constructor
	glm::vec3 vect = glm::vec3(3.0, 3.0, 4.0);
	float rad = 5;
	std::unique_ptr<Sphere> s2(new Sphere(vect, rad));
	REQUIRE(s2->getRadius() == 5);
	REQUIRE(s2->getCenter() == vect);
	REQUIRE(s2->area() == Approx(314.15927));
	REQUIRE(s2->volume() == Approx(523.599));

	// test smaller 0 as radius
	rad = -4.09;
	std::unique_ptr<Sphere> s3(new Sphere(vect, rad));
	REQUIRE(s3->getRadius() == 0);
	REQUIRE(s3->getCenter() == vect);
	REQUIRE(s3->area() == Approx(0));
	REQUIRE(s3->volume() == Approx(0));

	// test sphere with color
	std::shared_ptr<Material> red(
			new Material("Red", Color(1.0, 160.0/250.0, 122.0/255.0),
				Color(1.0, 160.0/250.0, 122.0/255.0), Color(1.0, 160.0/250.0, 122.0/255.0),
				4.0f));
	std::unique_ptr<Sphere> s4(new Sphere(vect, rad, "Sphere 4", red));
	REQUIRE(s4->getRadius() == 0);
	REQUIRE(s4->getCenter() == vect);
	REQUIRE(s4->area() == Approx(0));
	REQUIRE(s4->volume() == Approx(0));
	REQUIRE(s4->getName() == "Sphere 4");
	std::cout<<*s4<<"\n";
}

// task 5.2
TEST_CASE ("Test box class", "[box]"){
	// test default constructor
	std::unique_ptr<Box> b1(new Box());
	REQUIRE(b1->getMin() == glm::vec3(0.0, 0.0, 0.0));
	REQUIRE(b1->getMax() == glm::vec3(1.0, 1.0, 1.0));
	REQUIRE(b1->area() == 6);
	REQUIRE(b1->volume() == 1);
	REQUIRE(b1->getName() == "");

	// test value constructor
	glm::vec3 min = glm::vec3(1.0, 1.0, 3.0);
	glm::vec3 max = glm::vec3(3.0, 3.0, 6.0);
	std::unique_ptr<Box> b2(new Box(min, max));
	REQUIRE(b2->getMin() == min);
	REQUIRE(b2->getMax() == max);
	REQUIRE(b2->area() == 48.0);
	REQUIRE(b2->volume() == 12);

	// test max smaller than min
	min = glm::vec3(3.0, 3.0, 6.0);
	max = glm::vec3(1.0, 1.0, 3.0);
	std::unique_ptr<Box> b3(new Box(min, max));
	REQUIRE(b3->getMin() == max);
	REQUIRE(b3->getMax() == min);
	REQUIRE(b3->area() == 48);
	REQUIRE(b3->volume() == 12);

	// test box with additional shape param
	std::shared_ptr<Material> red(
			new Material("Red", Color(1.0, 160.0/250.0, 122.0/255.0),
				Color(1.0, 160.0/250.0, 122.0/255.0), Color(1.0, 160.0/250.0, 122.0/255.0),
				4.0f));
	std::unique_ptr<Box> b4(new Box(min, max, "Box 4", red));
	REQUIRE(b4->getMin() == max);
	REQUIRE(b4->getMax() == min);
	REQUIRE(b4->area() == 48);
	REQUIRE(b4->volume() == 12);
	REQUIRE(b4->getName() == "Box 4");
	std::cout<<*b4<<"\n";
}

TEST_CASE("intersect_ray_box", "[intersect]"){
  std::shared_ptr<Material> red(new Material());
  Box box{glm::vec3{2,2,2}, glm::vec3{10,10,10}, "Kai_Uwe", red};

  Ray ray1{glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}};
  Ray ray2{glm::vec3{0.0f,0.0f,0.0f}, glm::vec3{0.0f, -1.0f, 0.0f}};

  HitPoint hit = box.intersect(ray1);
  HitPoint nohit = box.intersect(ray2); 

  REQUIRE(hit.intersected == true);
  REQUIRE(hit.name == "Kai_Uwe");
  REQUIRE(nohit.intersected == false);
  REQUIRE(nohit.name == "");
}

TEST_CASE("intersect_ray_sphere", "[intersect]"){
	// Ray
	glm::vec3 ray_origin(0.0, 0.0, 0.0);
	// Ray direction needs to be normalized v = glm::normalize(vector)
	glm::vec3 ray_direction(0.0, 0.0, 1.0);
	// Sphere
	glm::vec3 sphere_center(0.0, 0.0, 5.0);
	float sphere_radius(1.0);

	float distance(0.0);

	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction, sphere_center, pow(sphere_radius, 2), distance);

	REQUIRE(distance == Approx(4.0));

	// hit the sphere in the center
	std::shared_ptr<Material> red(
			new Material("Red", Color(1.0, 160.0/250.0, 122.0/255.0),
				Color(1.0, 160.0/250.0, 122.0/255.0), Color(1.0, 160.0/250.0, 122.0/255.0),
				4.0f));
	std::unique_ptr<Sphere> s1(new Sphere(sphere_center, sphere_radius, "Sphere 1", red));
	std::unique_ptr<Ray> r1(new Ray());
	r1->origin = ray_origin;
	r1->direction = ray_direction;
	std::unique_ptr<HitPoint> h1(new HitPoint(s1->intersect(*r1)));
	REQUIRE(h1->name == "Sphere 1");
	REQUIRE(h1->intersected == true);
	REQUIRE(h1->distance == Approx(4));

	// hit the sphere right on the edge
	sphere_center = glm::vec3(0, 1.0, 5.0);
	std::unique_ptr<Sphere> s2(new Sphere(sphere_center, sphere_radius, "Sphere 2", red));
	std::unique_ptr<HitPoint> h2(new HitPoint(s2->intersect(*r1)));
	REQUIRE(h2->intersected == true);
	REQUIRE(h2->distance == Approx(5));

	// hit the sphere somehwere in the middle
	sphere_center = glm::vec3(0.5, 0.5, 5.0);
	std::unique_ptr<Sphere> s3(new Sphere(sphere_center, sphere_radius, "Sphere 3", red));
	std::unique_ptr<HitPoint> h3(new HitPoint(s3->intersect(*r1)));
	REQUIRE(h3->intersected == true);
	REQUIRE(h3->distance == Approx(4.29289));

	sphere_center = glm::vec3(1.0, 1.0, 5.0);
	std::unique_ptr<Sphere> s4(new Sphere(sphere_center, sphere_radius, "Sphere 4", red));
	std::unique_ptr<HitPoint> h4(new HitPoint(s4->intersect(*r1)));
	REQUIRE(h4->intersected == false);
}


TEST_CASE("SDFloader & find functions", "[SDFloader]"){
	std::string filepath = "/home/eric/Programmiersprachen_Uebungen/raytracer-collab/programmiersprachen-raytracer/files/scene.txt";
	Scene scene = sdfloader(filepath);

	// test if materials are there
	REQUIRE(scene.find_material("orange") == nullptr);
	REQUIRE(scene.find_material("red") != nullptr);
	REQUIRE(scene.find_material("green") != nullptr);
	REQUIRE(scene.find_material("blue") != nullptr);

	// test sphere from txt file
	REQUIRE(scene.find_shape("MegaSphere") == nullptr);
	REQUIRE(scene.find_shape("Sphere1") != nullptr);
	REQUIRE(scene.find_shape("Sphere1")->area() == Approx(12.56637));
	REQUIRE(scene.find_shape("Sphere1")->volume() == Approx(4.18879));
	REQUIRE(scene.find_shape("Sphere1")->getName() == "Sphere1");
	REQUIRE(scene.find_shape("Sphere1")->getMaterialName() == "red");

	REQUIRE(scene.find_shape("Box1")->area() == 48);
	REQUIRE(scene.find_shape("Box1")->volume() == 12);
	REQUIRE(scene.find_shape("Box1")->getName() == "Box1");
	REQUIRE(scene.find_shape("Box1")->getMaterialName() == "green");
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
