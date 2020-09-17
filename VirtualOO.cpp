#include "VirtualOO.hpp"

namespace OO::Virtual {

std::unique_ptr<Model> Text::makeCopy() const {
  auto copy = std::make_unique<Text>();
  copy->text = text;
  copy->x = x;
  copy->y = y;
  copy->red = red;
  copy->green = green;
  copy->blue = blue;
  copy->scale = scale;
  copy->opacity = opacity;

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
  printf("Virtual: Unknown property: %d\n", static_cast<int>(property));
  exit(1);
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

  printf("Virtual: Unknown property: %d\n", static_cast<int>(property));
  exit(1);
}

std::unique_ptr<Model> Image::makeCopy() const {
  auto copy = std::make_unique<Image>();
  copy->imageSource = imageSource;
  copy->x = x;
  copy->y = y;
  copy->scale = scale;
  copy->opacity = opacity;

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
      printf("Virtual: Unknown property: %d\n", static_cast<int>(property));
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
      printf("Virtual: Unknown property: %d\n", static_cast<int>(property));
      exit(1);
  }
}

std::vector<std::unique_ptr<Model>> interpolateModels(
    const std::vector<std::unique_ptr<Model>> &inputs, float time) {
  auto output = std::vector<std::unique_ptr<Model>>(inputs.size());
  for (int i = 0; i < inputs.size(); ++i) {
    auto &model = inputs[i];
    output[i] = model->makeCopy();
    auto &copy = output[i];
    for (auto &animation : model->animations) {
      auto value = animation.interpolator.interpolate(time);
      copy->updateValue(animation.propertyToAnimate, value);
    }
  }

  return output;
}

}  // namespace OO::Virtual
