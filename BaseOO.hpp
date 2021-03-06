#pragma once

#include <vector>

#include "Enums.hpp"
#include "Interpolator.hpp"

namespace OO {

struct Animation {
  LinearInterpolator interpolator;
  Property propertyToAnimate;
};

}  // namespace OO
