#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "shape.hpp"
#include "sphere.hpp"

// task 4.2
TEST_CASE ("Test sphere class", "[Sphere]"){
	// test default constructor
	std::unique_ptr<Sphere> s1(new Sphere());
	REQUIRE(s1->getRadius() == 1);
	REQUIRE(s1->getCenter() == glm::vec3(0.0, 0.0, 0.0));

	// test value constructor
	glm::vec3 vect = glm::vec3(3.0, 3.0, 4.0);
	float rad = 5;
	std::unique_ptr<Sphere> s2(new Sphere(vect, rad));
	REQUIRE(s2->getRadius() == 5);
	REQUIRE(s2->getCenter() == glm::vec3(3.0, 3.0, 4.0));

	// test smaller 0 as radius
	rad = -4.09;
	std::unique_ptr<Sphere> s3(new Sphere(vect, rad));
	REQUIRE(s3->getRadius() == 0);
	REQUIRE(s3->getCenter() == glm::vec3(3.0, 3.0, 4.0));
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
