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
    float pos_y = (((float)height_) / -2);
    for (int x=0; x < width_; ++x){
      float pos_x = (((float)width_) / -2);
      Pixel p(x,y);
      glm::vec3 direction(-(scene_.mainCam_.xres_/2)+0.5+x,-(scene_.mainCam_.yres_/2)+0.5+y,-z);
      Ray ray = scene_.mainCam_.shootRay(direction);
      //Ray ray = scene_.mainCam_.shootRay(pos_x,pos_y, direction);
      //const Ray ray(glm::vec3(x,y,0),glm::vec3(0,0,-1));
      for (auto& shape: scene_.shapes_) {
        if (!hit.hit_) {
          hit = shape->intersect(ray);
        }
      }
      if (hit.hit_) {
        p.color = rayTrace(ray,3); 
      }
      p.color = calcToneMapping(p.color);
      write(p);
    }
  }
  if (hit.hit_) {
    cout << "x: " << hit.intersectionPoint_.x << " y: " << hit.intersectionPoint_.y << " z: " << hit.intersectionPoint_.z << endl;
  }
  ppm_.save(filename_);
}

Color Renderer::rayTrace(Ray const& ray, int depth){ 
  Color backgroundcolor = Color(0.25, 0.25, 0.25);
  Hit closestHit;
  Hit tempHit;
  //std::shared_ptr<Shape> closestObject = nullptr;

  for(auto& shape : scene_.shapes_){
    tempHit = shape->intersect(ray);
    if (tempHit.distance_ < closestHit.distance_){
      closestHit = tempHit;
    }
    //closestObject = shape;
  }
  
  if (closestHit.hit_){
    if (std::isinf(closestHit.distance_)){
      cout << "rayTrace: something went wrong with hit" << endl;
    }
    //cout << "x: " << closestHit.intersectionPoint_.x << " y: " << closestHit.intersectionPoint_.y << " z: " << closestHit.intersectionPoint_.z << endl;
    return calcShade(ray, closestHit, depth);
  }
  else {
    return backgroundcolor;
  }
}


Color Renderer::calcShade( Ray const& ray, Hit const& hit, int depth) {
  // calculate ambient, slide 13
  Color combinedColor = (scene_.ambientLightCol_ * hit.shape_->getMaterial()->ambientcoefficient_);
  for (auto& light: scene_.lights_){
    combinedColor += calcPointLight(light,ray, hit);
  }
     if (std::isinf(hit.distance_)){
      cout << "calcShade: something went wrong with hit" << endl;
    }
  if (depth>0 && hit.shape_->getMaterial()->reflexivity_ != 0.0) {
    combinedColor += calcReflection(hit, ray, depth-1);
  }
  return combinedColor;
}

Color Renderer::calcPointLight(std::shared_ptr<Light> const& light, Ray const& ray, Hit const& hit){
  Color lightColor;

  glm::vec3 lightDir = glm::normalize((light->position_)-(hit.intersectionPoint_));
  float dt = glm::dot(lightDir, hit.normalVec_);

  Ray tempRay(hit.intersectionPoint_ + (0.01f * hit.normalVec_), lightDir);

  Hit closestHit;
  closestHit = calcClosestHit(tempRay);
  if (!closestHit.hit_){
    lightColor = light->color_ *(calcSpecularColor(light,hit, tempRay, ray) + calcDiffuseColor(light, hit, tempRay)*dt);   
    return lightColor;
  }
  return lightColor;
}

// Slides 11, 12
Color Renderer::calcDiffuseColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay){
  Color returnColor;
  glm::vec3 normDir = glm::normalize(lightRay.direction);
  glm::vec3 normHit = glm::normalize(hit.normalVec_);
  float temp = glm::dot(normHit, normDir);

  if (temp >= 0.0) {
    returnColor = (hit.shape_->getMaterial()->diffusecoefficient_*light->color_*light->brightness_*temp);
  }
  return returnColor;
}

// Slide 14
Color Renderer::calcSpecularColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay, Ray const& ray){
  Color returnColor;
  glm::vec3 reflectVec;

  reflectVec = glm::normalize(glm::reflect(-(lightRay.direction), hit.normalVec_));
  float temp = std::max(glm::dot(reflectVec, glm::normalize(-(ray.direction))),0.0f);
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
      //closest.hit_ = true;
  }
  return closest;
}

Color Renderer::calcReflection(Hit const& hit, Ray const& ray, int depth){
  Color reflectColor;
  glm::vec3 reflectVec = glm::normalize(glm::reflect(ray.direction, hit.normalVec_));

  Ray tempRay(((0.01f * reflectVec) + hit.intersectionPoint_),reflectVec);
    if (std::isnan(tempRay.origin.x)) {
      cout << "tempRay.x NaN spilling" << endl;
  }
  reflectColor = rayTrace(tempRay, depth);

  /*
  if (reflectColor.r != reflectColor.r) { //if rgb-values are NaN this returns true
    reflectColor.r = hit.shape_->getMaterial()->getColor().r;
  }
  if (reflectColor.g != reflectColor.g) { //if rgb-values are NaN this returns true
    reflectColor.g = hit.shape_->getMaterial()->getColor().g;
  }
  if (reflectColor.b != reflectColor.b) { //if rgb-values are NaN this returns true
    reflectColor.b = hit.shape_->getMaterial()->getColor().b;
  }*/
  //Color returnColor = (Color{1.0f,1.0f,1.0f}-hit.shape_->getMaterial()->specularcoefficient_) + (reflectColor*hit.shape_->getMaterial()->specularcoefficient_);
  //cout << "reflectColor before: r: " << reflectColor.r << " g: " << reflectColor.g << " b: " << reflectColor.b;
  reflectColor *= hit.shape_->getMaterial()->specularcoefficient_ *hit.shape_->getMaterial()->getColor();
  //cout << "reflectColor after: r: " << reflectColor.r << " g: " << reflectColor.g << " b: " << reflectColor.b << endl;

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
