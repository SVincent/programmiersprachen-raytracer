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

void Renderer::render()
{
  camera mainCamera;
  //float distance = (width_/2) / tan( mainCamera.fov_ * M_PI / 360);
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Ray thisRay = mainCamera.shootRay(x, y);
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
  //float distance = (width_/2) / tan( mainCamera.fov_ * M_PI / 360);

  for (int y=0; y < height_; ++y){
    for (int x=0; x < width_; ++x){
      Pixel p(x,y);
      Ray thisRay = mainCamera.shootRay(x, y, 100);
      Ray ray(glm::vec3(x,y,0),glm::vec3(0,0,1));
      //std::cout << "shoot ray through " << x << ", " << y << std::endl;
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

void Renderer::render3(){
  Color backgroundcolor = Color(0.0,0.0,0.0);
  float t;
  for (int y=0; y < height_; ++y){
    for (int x=0; x < width_; ++x){
      Pixel p(x,y);
      p.color = backgroundcolor;
      const Ray ray = scene_.mainCam_.shootRay(x,y,-1);
      //const Ray ray(glm::vec3(x,y,0),glm::vec3(0,0,1));
      for (auto& shape: scene_.shapes_){
        //Color tempColor = shape->getMaterial()->getColor();
        Color objectColor = shape->getMaterial()->getColor();
        for (auto& light: scene_.lights_){
          Hit hit = shape->intersect(ray);
          if (hit.hit_){
            glm::vec3 pi = ray.origin + glm::vec3{(ray.direction.x *t),(ray.direction.y * t),(ray.direction.z *t)};
            glm::vec3 l = light->position_ - pi;
            glm::vec3 N = shape->getNormalized(pi); 
            float dt = glm::dot(glm::normalize(l), glm::normalize(N));
            //Hit hit = shape->intersect(ray);

            //p.color = (shape->getMaterial()->getColor() + light->color_ *dt);
            /*
            p.color.r += (objectColor.r * light->color_.r) * dt;
            p.color.g += (objectColor.g * light->color_.g) * dt;
            p.color.b += (objectColor.b * light->color_.b) * dt;
            */

            p.color = rayTrace(ray);// * dt;
            
            /*
            Color ambientLight = calcShade(ray, hit, dt);
            Color diffuseLight = calcDiffuseColor(light, hit, lightray);
            Color specularLight = calcSpecularColor(light, hit, lightray, ray);

            p.color = ambientLight + diffuseLight + specularLight;
            */
          }
        }
        //p.color = calcToneMapping(p.color);
        write(p);
      }
    }
  }
  ppm_.save(filename_);
}

Color Renderer::rayTrace(Ray const& ray){ 
  Color backgroundcolor = Color(1.0, 0.0, 0.0);
  Hit closestHit;
  Hit tempHit;
  std::shared_ptr<Shape> closestObject = nullptr;

  for(auto& shape : scene_.shapes_){
    tempHit = shape->intersect(ray);
    if (tempHit.distance_ < closestHit.distance_){
      closestHit = tempHit;
      closestHit.normalizedVec_ =  shape->getNormalized(tempHit.intersectionPoint_); 
    }
    closestObject = shape;
  }
  
  if (closestHit.hit_){
    //return closestHit.shape_->getMaterial()->getColor();
    return calcShade(ray, closestHit);
  }
  
  if (closestHit.shape_ != nullptr) { 
    return calcShade(ray, closestHit);
    //return Color(0.0,1.0,0.0);
  }
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
  
  /*
  if (depth >= 1){
    // calculate reflection
    Color reflectCoeff = hit.shape_->getMaterial()->specularcoefficient_;
    Color reflectColor = calcReflection(hit, ray, depth);

    ambientColor += reflectColor * reflectCoeff;
  }
  */
  return ambientColor;
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
  }
  return closest;
}


// Slides 11, 12
Color Renderer::calcDiffuseColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay){
  Color returnColor;
  glm::vec3 normDir = glm::normalize(lightRay.direction);
  glm::vec3 normHit = glm::normalize(hit.normalizedVec_);
  float temp = glm::dot(normHit, normDir);

  if (temp > 0.0)
    returnColor = (hit.shape_->getMaterial()->diffusecoefficient_)*temp;
  else
    returnColor = (hit.shape_->getMaterial()->diffusecoefficient_) * 0.0;
 
  return returnColor;
}

// Slide 14
Color Renderer::calcSpecularColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay, Ray const& ray){
  Color returnColor;
  glm::vec3 reflectVec;
  // reflectVec = glm::normalize(lightRay.direction - 2.0* glm::dot(hit.normalizedVec_,lightRay.direction)*hit.normalizedVec_ );
  reflectVec = glm::normalize(glm::reflect(-(lightRay.direction), hit.normalizedVec_));
  
  float temp;
  float ifTemp = glm::dot(reflectVec, glm::normalize(-(ray.direction)));

  if (ifTemp > 0){
    temp = ifTemp;
  }
  else
    temp = 0.0;

  float squareTemp = pow(temp, hit.shape_->getMaterial()->reflexivity_);
  returnColor = (hit.shape_->getMaterial()->diffusecoefficient_) * squareTemp;

  return returnColor; 
}

Color Renderer::calcReflection(Hit const& hit, Ray const& ray){
  Color reflectColor;
  glm::vec3 reflectVec = glm::normalize(glm::reflect(ray.direction, hit.normalizedVec_));

  Ray tempRay(((0.01f * reflectVec) + hit.intersectionPoint_),reflectVec);
  reflectColor = rayTrace(tempRay);
  return reflectColor;
}

Color Renderer::calcPointLight(std::shared_ptr<Light> const& light, Ray const& ray, Hit const& hit){
  Color lightColor;
  /*
  glm::vec3 pi = ray.origin + glm::vec3{(ray.direction.x *t),(ray.direction.y * t),(ray.direction.z *t)};
  glm::vec3 l = light->position_ - pi;
  glm::vec3 N = shape->getNormalized(pi); 
  float dt = glm::dot(glm::normalize(l), glm::normalize(N));
            */
  glm::vec3 lightDir = glm::normalize((light->position_)-(hit.intersectionPoint_));
  float dt = glm::dot(lightDir, hit.normalizedVec_);

  Ray tempRay(hit.intersectionPoint_ + (0.01f * hit.normalizedVec_), lightDir);

  Hit shadowHit;
  shadowHit = calcClosestHit(tempRay);
  if (shadowHit.hit_){
    lightColor = light->color_ *(calcSpecularColor(light,hit, tempRay, ray) + calcDiffuseColor(light, hit, tempRay));      
    return lightColor;
  }
  else{
    return lightColor;
  }
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
