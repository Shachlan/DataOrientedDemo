#pragma once

#include <vector>

#include "Enums.hpp"
#include "Interpolator.hpp"

namespace OO {

struct Animation {
  LinearInterpolator interpolator;
  std::vector<Property> propertiesToAnimate;
};

}  // namespace OO
