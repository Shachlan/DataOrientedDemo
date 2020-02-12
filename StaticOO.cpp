#include "StaticOO.hpp"

namespace OO::Static {
Text Text::makeCopy() const {
  auto copy = Text();
  copy.text = text;
  copy.x = x;
  copy.y = y;
  copy.red = red;
  copy.green = green;
  copy.blue = blue;
  copy.scale = scale;
  copy.opacity = opacity;

  return copy;
}

float &Text::propertyToUpdate(Property property) {
  switch (property) {
    case Property::X:
      return x;
    case Property::Y:
      return y;
    case Property::Red:
      return red;
    case Property::Green:
      return green;
    case Property::Blue:
      return blue;
    case Property::Scale:
      return scale;
    case Property::Opacity:
      return opacity;
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

Image Image::makeCopy() const {
  auto copy = Image();
  copy.imageSource = imageSource;
  copy.x = x;
  copy.y = y;
  copy.scale = scale;
  copy.opacity = opacity;

  return copy;
}

float &Image::propertyToUpdate(Property property) {
  switch (property) {
    case Property::X:
      return x;
    case Property::Y:
      return y;
    case Property::Scale:
      return scale;
    case Property::Opacity:
      return opacity;
    default:
      exit(1);
  }
}

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

std::vector<Model> interpolateModels(const std::vector<Model> &inputs,
                                     float time) {
  auto output = std::vector<Model>(inputs.size());
  for (int i = 0; i < inputs.size(); ++i) {
    auto &model = inputs[i];
    std::visit(
        [&](auto &model) {
          output[i] = Model(model.makeCopy());
          auto &copy = output[i];
          for (auto &animation : model.animations) {
            auto value = animation.interpolator.interpolate(time);
            for (auto &property : animation.propertiesToAnimate) {
              updateValue(copy, property, value);
            }
          }
        },
        model);
  }

  return output;
}

void updateValue(Model &model, Property property, float value) {
  std::visit(
      [&](auto &model) {
        auto op = model.updateOperatorForProperty(property);
        auto &currentValue = model.propertyToUpdate(property);
        currentValue = composeValue(currentValue, op, value);
      },
      model);
}

}  // namespace OO::Static
