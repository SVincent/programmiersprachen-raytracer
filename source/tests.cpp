#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "../framework/shape.hpp"
#include "../framework/sphere.hpp"
#include "../framework/Box.hpp"

#include <glm/glm.hpp>

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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
