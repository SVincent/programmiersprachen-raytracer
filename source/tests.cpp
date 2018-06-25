#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "../framework/shape.hpp"
#include "../framework/sphere.hpp"
#include "../framework/Box.hpp"

#include <glm/glm.hpp>

using namespace std;

//Task 5.2
TEST_CASE("Sphere tests","Task 5.2") {
  glm::vec3 center{0.0,0.0,0.0};
  float radius0{1.0f};
  float radius1{2.5f};

  Sphere sphere0{};
  Sphere sphere1{center,radius0};
  Sphere sphere2{glm::vec3{1.0,1.0,1.0}, radius1};

  REQUIRE(sphere0.area() == 0.0);
  REQUIRE(sphere0.volume() == 0.0);

  REQUIRE(sphere1.area() == Approx(12.5663706144));
  REQUIRE(sphere1.volume() == Approx(4.18879020479));

  REQUIRE(sphere2.area() == Approx(78.5398163397));
  REQUIRE(sphere2.volume() == Approx(65.4498469498));
}

TEST_CASE("Box tests","Task 5.2") {
  glm::vec3 minimum0{0.0,0.0,0.0};
  glm::vec3 minimum1{1.0,1.0,1.0};
  glm::vec3 maximum0{1.5,1.0,1.0};
  glm::vec3 maximum1{2.0,2.0,2.0};

  Box box0{};
  Box box1{minimum0,maximum0};
  Box box2{minimum0,maximum1};
  Box box3{minimum1,maximum0};
  Box box4{minimum1,maximum1};

  REQUIRE(box0.area() == 0.0);
  REQUIRE(box0.volume() == 0.0);

  REQUIRE(box1.area() == 8.0);
  REQUIRE(box1.volume() == 1.5);

  REQUIRE(box2.area() == 24.0);
  REQUIRE(box2.volume() == 8.0);

  REQUIRE(box3.area() == 0.0);
  REQUIRE(box3.volume() == 0.0);

  REQUIRE(box4.area() == 6.0);
  REQUIRE(box4.volume() == 1.0);
}

//Task 5.5
TEST_CASE("print test", "task 5.5") {
  Sphere sphere0{glm::vec3{1.0,1.0,1.0}, 2.0f};
	cout << sphere0;
	Box box0({0.0f,0.5f,1.0f}, {1.0f,1.0f,2.0f}, "Some box",{0.0f,0.0f,0.0f});
	cout << box0;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
