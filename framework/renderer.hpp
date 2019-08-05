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

#include <cmath>
#include <glm/glm.hpp>
#include <string>

#include "color.hpp"
#include "hitpoint.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include "scene.hpp"

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(Scene const& scene);

  void render();
  void write(Pixel const&);
  Color raytrace(Ray const&) const;
  Color shade(HitPoint const&) const;

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_, cam;
  PpmWriter ppm_;
  Scene scene;
};

#endif // #ifndef BUW_RENDERER_HPP
