#include <cassert>
#include <chrono>
#include <cstdlib>

#include "StaticOO.hpp"
#include "VirtualOO.hpp"

namespace {
static constexpr auto kNumberOfModels = 1000;
static constexpr auto kNumberOfAnimationsPerModel = 1000;

const std::vector<std::string> kStrings = {"foo", "bar", "baz",
                                           "some other string"};

auto makeInterpolator() {
  return LinearInterpolator{(float)(rand() % 256 - 256), (float)(rand() % 256)};
}

auto makeAnimations(std::vector<Property> properties) {
  auto animations = std::vector<OO::Animation>();
  auto remainingAnimations = kNumberOfAnimationsPerModel;
  for (size_t j = 0; j < properties.size(); ++j) {
    auto property = properties[j];
    if (remainingAnimations == 0) {
      return animations;
    }
    auto currentAnimations = j == properties.size() - 1
                                 ? remainingAnimations
                                 : rand() % remainingAnimations;
    remainingAnimations -= currentAnimations;
    for (int i = 0; i < currentAnimations; ++i) {
      auto animation = OO::Animation{makeInterpolator(), {property}};
      animations.emplace_back(animation);
    }
  }
  return animations;
}

std::unique_ptr<OO::Virtual::Model> makeModel() {
  if (rand() % 2 == 0) {
    auto model = std::make_unique<OO::Virtual::Text>();
    model->text = kStrings[rand() % kStrings.size()];
    model->x = rand() % 100;
    model->y = rand() % 100;
    model->red = rand() % 256;
    model->green = rand() % 256;
    model->blue = rand() % 256;
    model->scale = rand() % 100;
    model->opacity = rand() % 100;
    model->animations = makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity});
    return model;
  } else {
    auto model = std::make_unique<OO::Virtual::Image>();
    model->imageSource = kStrings[rand() % kStrings.size()];
    model->x = rand() % 100;
    model->y = rand() % 100;
    model->scale = rand() % 100;
    model->opacity = rand() % 100;
    model->animations = makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity});
    return model;
  }
}

void testBunched() {
  auto inputs =
      std::vector<std::unique_ptr<OO::Virtual::Model>>(kNumberOfModels);
  for (int i = 0; i < kNumberOfModels; ++i) {
    inputs[i] = makeModel();
    for (int j = 0; j < kNumberOfAnimationsPerModel; ++j) {
    }
  }

  auto start = std::chrono::high_resolution_clock::now();
  auto interpolatedModels = OO::Virtual::interpolateModels(inputs, 2);
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = (finish - start);
  printf("size of result: %lu took time: %f", interpolatedModels.size(), elapsed.count());
}

void testInterleaved() {}

}  // namespace

int main(int argc, char *argv[]) {
  testBunched();

  testInterleaved();
}
