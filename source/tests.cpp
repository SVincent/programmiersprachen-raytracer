#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "../framework/shape.hpp"
#include "../framework/sphere.hpp"
#include "../framework/Box.hpp"
#include "../framework/color.hpp"
#include "../framework/sdfreader.hpp"
#include "../framework/scene.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <glm/glm.hpp>

using namespace std;
/*
//Task 5.2
TEST_CASE("Sphere tests","Task 5.2") {
  glm::vec3 center{0.0,0.0,0.0};
  float radius0{1.0f};
  float radius1{2.5f};

  Sphere sphere0{};
  Sphere sphere1{center,radius0};
  Sphere sphere2{glm::vec3{1.0,1.0,1.0}, radius1};

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

//Task 5.6
TEST_CASE("intersect_ray_sphere","[intersect]") {
  // Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};//1
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
  Ray ray{};
  auto v = glm::normalize(ray_direction);
  // Sphere
  glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
  float sphere_radius{1.0f};
  Sphere sphere0{sphere_center, sphere_radius};
  Sphere sphere1{glm::vec3{1.0,1.0,1.0}, 2.0f};

  //intersectRaySphere
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
    ray_origin, v,
    sphere_center,
    sphere_radius*sphere_radius, // squared radius !!!
    distance);
  REQUIRE(distance == Approx(4.0f));

  //intersect
  REQUIRE(sphere0.intersect(ray, distance) == false);
  REQUIRE(sphere1.intersect(ray, distance) == true);
}

TEST_CASE("box_intersect","[intersect]"){
  // Box
  glm::vec3 minimum1{-1.0,-1.0,-1.0};
  glm::vec3 maximum1{-2.0,-2.0,-2.0};
  Box box1{minimum1,maximum1};

  // Ray (Standard constructor)
  // glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  // glm::vec3 ray_direction{0.0f, 0.0f, -1.0f};
  Ray ray1{};
  float distance= 0.0f;

  REQUIRE(box1.intersect(ray1,distance) == false);
}

TEST_CASE("read_sdf"){
  //sdfReader sdf;
  //Scene s{};
  //s = sdf.readSdf("/home/jannis/Programmiersprachen/programmiersprachen-raytracer/materials.sdf");
}
/*
TEST_CASE("intersect"){
  Sphere sp({3.0, 3.0, -6.0},2.0);
  Ray ray{};
  float c = 1.0f;
  //sp.intersect(ray, c);
  REQUIRE(sp.intersect(ray,c) == true);
}


TEST_CASE("translate & intersect") {
  //General variables
  Ray ray1{};
  float distance = 1.0f;
  glm::vec3 translateVec{5.5f,5.5f,5.5f};

  //Box
  glm::vec3 minimum1{-1.0,-1.0,-1.0};
  glm::vec3 maximum1{1.0,1.0,1.0};
  Box box1{minimum1,maximum1};

  REQUIRE(box1.intersect(ray1,distance) == true);

  Ray ray2{};
  box1.translate(translateVec);
  ray2 = box1.transform(ray2);

  REQUIRE(box1.intersect(ray1,distance) == true);
  REQUIRE(box1.intersect(ray2,distance) == false);

  //Sphere
  glm::vec3 center{0.0,0.0,0.0};
  Sphere sphere1{center, 1.0f};

  REQUIRE(sphere1.intersect(ray1,distance) == true);

  sphere1.translate(translateVec);
  ray2 = sphere1.transform(ray2);

  REQUIRE(box1.intersect(ray1,distance) == true);
  REQUIRE(box1.intersect(ray2,distance) == false);



}

TEST_CASE("rotate & intersect") {
  //General variables
  Ray ray1{};
  float distance = 1.0f;
  glm::vec3 rotateVec{1.5f,1.5f,1.5f};

  //Box
  glm::vec3 minimum1{-1.0,-1.0,-1.0};
  glm::vec3 maximum1{2.0,2.0,2.0};
  Box box1{minimum1,maximum1};

  REQUIRE(box1.intersect(ray1,distance) == true);

  Ray ray2{};
  box1.rotate(rotateVec);
  ray2 = box1.transform(ray2);

  REQUIRE(box1.intersect(ray1,distance) == true);
  REQUIRE(box1.intersect(ray2,distance) == false);

  //Sphere
  glm::vec3 center{0.0,0.0,0.0};
  Sphere sphere1{center, 1.0f};

  REQUIRE(sphere1.intersect(ray1,distance) == true);

  sphere1.rotate(rotateVec);
  ray2 = sphere1.transform(ray2);

  REQUIRE(box1.intersect(ray1,distance) == true);
  REQUIRE(box1.intersect(ray2,distance) == false);

}

TEST_CASE("scale & intersect") {
  //General variables
  Ray ray1{};
  float distance = 1.0f;
  glm::vec3 scaleVec{1.5f,1.5f,1.5f};

  //Box
  glm::vec3 minimum1{-1.0,-1.0,-1.0};
  glm::vec3 maximum1{2.0,2.0,2.0};
  Box box1{minimum1,maximum1};

  REQUIRE(box1.intersect(ray1,distance) == true);

  Ray ray2{};
  box1.scale(scaleVec);
  ray2 = box1.transform(ray2);

  REQUIRE(box1.intersect(ray1,distance) == true);
  REQUIRE(box1.intersect(ray2,distance) == false);

  //Sphere
  glm::vec3 center{0.0,0.0,0.0};
  Sphere sphere1{center, 1.0f};

  REQUIRE(sphere1.intersect(ray1,distance) == true);

  sphere1.scale(scaleVec);
  ray2 = sphere1.transform(ray2);

  REQUIRE(box1.intersect(ray1,distance) == true);
  REQUIRE(box1.intersect(ray2,distance) == false);
}*/



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
