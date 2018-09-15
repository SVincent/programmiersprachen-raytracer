// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "scene.hpp"
#include "Hit.hpp"
#include "shape.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include <cmath>
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer(Scene scene, unsigned w, unsigned h, std::string const& file);

  void render();

  Color rayTrace(Ray const& ray, int depth);
  Hit calcClosestHit(Ray const& ray); 
  
  Color calcToneMapping(Color const& color);

  Color calcShade(Ray const& ray, Hit const & hit, int depth);
  Color calcPointLight(std::shared_ptr<Light> const& light, Ray const& ray, Hit const& hit);
  Color calcDiffuseColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay);
  Color calcSpecularColor(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& lightRay, Ray const& ray);
  Color calcReflection(Hit const& hit, Ray const& ray, int depth);

  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP
