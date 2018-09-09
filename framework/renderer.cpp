// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(Scene scene, unsigned w, unsigned h, std::string const& file)
  : scene_(scene)
  , width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

Color Renderer::rayTrace(Ray const& ray){
  Color backgroundcolor = Color(0.0, 1.0, 0.0);
  Hit closestHit;
  Hit tempHit;
  std::shared_ptr<Shape> closestObject = nullptr;

  for(auto& shape : scene_.shapes_){
    tempHit = shape->intersect(ray);
    if (tempHit.distance_ < closestHit.distance_){
      closestHit = tempHit;
    }
    closestObject = shape;
  }
  for (int i = 0; i < scene_.shapes_.size();i++){
    Hit hit = scene_.shapes_[i]->intersect(ray);
    if (hit.distance_ < closestHit.distance_) {
      //std::cout << "hit with distance: " << hit.distance_ << std::endl;
      closestHit = hit;
      closestObject = scene_.shapes_[i];
    }
  }
  if (closestHit.hit_){
    std::cout << "HIT" << std::endl;
    return closestObject->getMaterial()->getColor();
    //return Color(1.0,0.0,0.0);
  }
  if (closestObject != nullptr) {
    std::cout << "Hit with color red" << std::endl;
    return Color(1.0,0.0,0.0);
    //return shade(closestObject, ray, closestHit);
  } else {
    std::cout << "NO HIT" << std::endl;
    return backgroundcolor; //default backgroundcolor
  }
}

Color Renderer::shade(std::shared_ptr<Shape> Object, Ray const& ray, Hit hit) {
  return Color(1.0, 0.0, 0.0);
}


void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;
  camera mainCamera;
  float distance = (width_/2) / tan( mainCamera.fov_ * M_PI / 360);

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Ray thisRay = mainCamera.shootRay(x, y, distance);
      //std::cout << "shoot ray through " << x << ", " << y << std::endl;
      Pixel p(x,y);
      Color c {1,0,0};
      c = rayTrace(thisRay);
      p.color = c;

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render2(){
  camera mainCamera;
  float distance = (width_/2) / tan( mainCamera.fov_ * M_PI / 360);

  for (int y=0; y < height_; ++y){
    for (int x=0; x < width_; ++x){
      Pixel p(x,y);
      Ray thisRay = mainCamera.shootRay(x, y, distance);
      Ray ray(glm::vec3(x,y,0),glm::vec3(0,0,1));
      //shared_ptr<Shape> shape = scene_.shapes_[0];
      std::cout << "shoot ray through " << x << ", " << y << std::endl;
      for (auto& shape : scene_.shapes_){
      if (shape->intersectBool(ray)){
        //std::cout << "intersected " << shape->getName() << " with material: " << shape->getMaterial()->getMaterialName() << " and color: " << shape->getMaterial()->getColor() << std::endl;
        Color c = rayTrace(ray);
        //Color c = shape->getMaterial()->getColor();
        p.color = c;
      }
      write(p);
    }}
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
