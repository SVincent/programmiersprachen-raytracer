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
  , color_buffer_(w*h, Color(0.0, 1.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(){
  Hit hit;
  int z = (scene_.mainCam_.xres_/2)/(tan(scene_.mainCam_.fov_/360*M_PI));
  for (int y=0; y < height_; ++y){
    for (int x=0; x < width_; ++x){
      Pixel p(x,y);
      glm::vec3 direction(-(scene_.mainCam_.xres_/2)+0.5+x,-(scene_.mainCam_.yres_/2)+0.5+y,-z);
      Ray ray = scene_.mainCam_.shootRay(direction);
      //const Ray ray(glm::vec3(x,y,0),glm::vec3(0,0,-1));
      p.color = rayTrace(ray); 
      for (auto& shape: scene_.shapes_) {
        if (!hit.hit_) {
          hit = shape->intersect(ray);
        }
      }
      //p.color = calcToneMapping(p.color);
      write(p);
    }
  }
  if (hit.hit_) {
    cout << "x: " << hit.intersectionPoint_.x << " y: " << hit.intersectionPoint_.y << " z: " << hit.intersectionPoint_.z << endl;
  }
  ppm_.save(filename_);
}

Color Renderer::rayTrace(Ray const& ray){ 
  Color backgroundcolor = Color(0.25, 0.25, 0.25);
  Hit closestHit;
  Hit tempHit;
  std::shared_ptr<Shape> closestObject = nullptr;

  for(auto& shape : scene_.shapes_){
    tempHit = shape->intersect(ray);
    if (tempHit.distance_ < closestHit.distance_){
      closestHit = tempHit;
      closestHit.normalVec_ =  shape->getNormalized(tempHit.intersectionPoint_); 
    }
    closestObject = shape;
  }
  
  if (closestHit.hit_){
    cout << "x: " << closestHit.intersectionPoint_.x << " y: " << closestHit.intersectionPoint_.y << " z: " << closestHit.intersectionPoint_.z << endl;
    return calcShade(ray, closestHit);
    //return Color(0.0,1.0,0.0);
  }
  /*
  if (closestHit.shape_ != nullptr) { 
    return Color(0.0,0.0,1.0);
  }*/
  else {
    return backgroundcolor; //default backgroundcolor
  }
}


Color Renderer::calcShade( Ray const& ray, Hit const& hit) {
  // calculate ambient, slide 13
  Color ambientColor = (scene_.ambientLightCol_ * hit.shape_->getMaterial()->ambientcoefficient_);
  
  for (auto& light: scene_.lights_){
    ambientColor += calcPointLight(light,ray, hit);
  }
  
  return ambientColor;
}

Color Renderer::calcPointLight(std::shared_ptr<Light> const& light, Ray const& ray, Hit const& hit){
  Color lightColor;

  glm::vec3 lightDir = glm::normalize((light->position_)-(hit.intersectionPoint_));
  float dt = glm::dot(lightDir, hit.normalVec_);

  Ray tempRay(hit.intersectionPoint_ + (0.01f * hit.normalVec_), lightDir);
  //Ray tempRay(hit.intersectionPoint_, lightDir);

  Hit closestHit;
  closestHit = calcClosestHit(tempRay);
  if (closestHit.hit_){
    lightColor = light->color_ *(calcSpecularColor(light,hit, tempRay, ray) + calcDiffuseColor(light, hit, tempRay)*dt);   
    return lightColor;
  }
  else if (!closestHit.hit_) {
    return lightColor;
  }
}

// Slides 11, 12
Color Renderer::calcDiffuseColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay){
  Color returnColor;
  glm::vec3 normDir = glm::normalize(lightRay.direction);
  glm::vec3 normHit = glm::normalize(hit.normalVec_);
  float temp = glm::dot(normHit, normDir);

  if (temp >= 0.0)
    returnColor = (hit.shape_->getMaterial()->diffusecoefficient_*light->color_*light->brightness_*temp);
  else
    returnColor = (hit.shape_->getMaterial()->diffusecoefficient_) * 0.0;
 
  return returnColor;
}

// Slide 14
Color Renderer::calcSpecularColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay, Ray const& ray){
  Color returnColor;
  glm::vec3 reflectVec;

  //changed ray direction for testing
  reflectVec = glm::normalize(glm::reflect(lightRay.direction, hit.normalVec_));
  
  float temp;
  float ifTemp = glm::dot(reflectVec, glm::normalize(ray.direction));

  if (ifTemp > 0){
    temp = ifTemp;
  }
  else {
    temp = 0.0;
  }

  float squareTemp = pow(temp, hit.shape_->getMaterial()->reflexivity_);
  returnColor = (hit.shape_->getMaterial()->specularcoefficient_ * squareTemp * light->color_ * light->brightness_);

  return returnColor; 
}

Color Renderer::calcToneMapping(Color const& color){
  Color returnColor;
  returnColor.r = (color.r/(color.r +1));
  returnColor.g = (color.g/(color.g +1));
  returnColor.b = (color.b/(color.b +1 ));
  return returnColor;
}


Hit Renderer::calcClosestHit(Ray const& ray){
  Hit temp;
  Hit closest;

  for (auto& shape: scene_.shapes_){
    temp = shape->intersect(ray);
    if (temp.distance_ < closest.distance_)
      closest = temp;
      closest.hit_ = true;
  }
  return closest;
}

Color Renderer::calcReflection(Hit const& hit, Ray const& ray){
  Color reflectColor;
  glm::vec3 reflectVec = glm::normalize(glm::reflect(ray.direction, hit.normalVec_));

  Ray tempRay(((0.01f * reflectVec) + hit.intersectionPoint_),reflectVec);
  reflectColor = rayTrace(tempRay);
  return reflectColor;
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
