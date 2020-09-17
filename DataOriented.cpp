#include "DataOriented.hpp"

namespace DataOriented {

UpdateOperator Image::updateOperatorForProperty(Property property) {
  switch (property) {
    case Property::X:
      return UpdateOperator::Add;
    case Property::Y:
      return UpdateOperator::Add;
    case Property::Scale:
      return UpdateOperator::Replace;
    case Property::Opacity:
      return UpdateOperator::Replace;
    default:
      printf("DOD: unknown property in %d\n", static_cast<int>(property));
      exit(1);
  }
}

size_t Image::indexOfProperty(Property property) {
  switch (property) {
    case Property::X:
      return 0;
    case Property::Y:
      return 1;
    case Property::Scale:
      return 2;
    case Property::Opacity:
      return 3;
    default:
      printf("DOD: unknown property in %d\n", static_cast<int>(property));
      exit(1);
  }
}

UpdateOperator Text::updateOperatorForProperty(Property property) {
  switch (property) {
    case Property::X:
      return UpdateOperator::Add;
    case Property::Y:
      return UpdateOperator::Add;
    case Property::Red:
      return UpdateOperator::Multiply;
    case Property::Green:
      return UpdateOperator::Multiply;
    case Property::Blue:
      return UpdateOperator::Multiply;
    case Property::Scale:
      return UpdateOperator::Multiply;
    case Property::Opacity:
      return UpdateOperator::Replace;
  }
  printf("DOD: unknown property in %d\n", static_cast<int>(property));
  exit(1);
}

size_t Text::indexOfProperty(Property property) {
  return (size_t)property;
}

void interpolateModels(const std::vector<InputValue> &sourceValues, std::vector<float> &properties,
                       float time) {
  for (int i = 0; i < sourceValues.size(); ++i) {
    auto &sourceValue = sourceValues[i];
    auto value = sourceValue.initialValue;
    for (const auto &interpolator : sourceValue.animations) {
      auto interpolatedValue = interpolator.interpolate(time);
      value = composeValue(value, sourceValue.updateOperator, interpolatedValue);
    }
    properties[i] = value;
  }
}

}  // namespace DataOriented
