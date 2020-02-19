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
}

void interpolateModels(const std::vector<InputValue> &sourceValues,
                       std::vector<float> &properties, float time) {
  for (int i = 0; i < sourceValues.size(); ++i) {
    auto &sourceValue = sourceValues[i];
    auto value = sourceValue.initialValue;
    for (const auto &interpolator : sourceValue.animations) {
      auto interpolatedValue = interpolator.interpolate(time);
      value =
          composeValue(value, sourceValue.updateOperator, interpolatedValue);
    }
    properties[i] = value;
  }
}

}  // namespace DataOriented
