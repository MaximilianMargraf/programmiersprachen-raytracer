#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

// task 5.2
TEST_CASE ("Test sphere class", "[Sphere]"){
	// test default constructor
	std::unique_ptr<Sphere> s1(new Sphere());
	REQUIRE(s1->getRadius() == 1);
	REQUIRE(s1->getCenter() == glm::vec3(0.0, 0.0, 0.0));
	REQUIRE(s1->area() == Approx(12.56637));
	REQUIRE(s1->volume() == Approx(4.18879));
	REQUIRE(s1->getName() == "");
	REQUIRE(s1->getColor() == Color(0.0, 0.0, 0.0));

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
	std::unique_ptr<Color> red(new Color(1.0, 160.0/250.0, 122.0/255.0));
	std::unique_ptr<Sphere> s4(new Sphere(vect, rad, "Sphere 4", *red));
	REQUIRE(s4->getRadius() == 0);
	REQUIRE(s4->getCenter() == vect);
	REQUIRE(s4->area() == Approx(0));
	REQUIRE(s4->volume() == Approx(0));
	REQUIRE(s4->getName() == "Sphere 4");
	REQUIRE(s4->getColor() == *red);
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
	REQUIRE(b1->getColor() == Color(0.0, 0.0, 0.0));

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
	std::unique_ptr<Color> red(new Color(1.0, 160.0/250.0, 122.0/255.0));
	std::unique_ptr<Box> b4(new Box(min, max, "Box 4", *red));
	REQUIRE(b4->getMin() == max);
	REQUIRE(b4->getMax() == min);
	REQUIRE(b4->area() == 48);
	REQUIRE(b4->volume() == 12);
	REQUIRE(b4->getName() == "Box 4");
	REQUIRE(b4->getColor() == *red);

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
