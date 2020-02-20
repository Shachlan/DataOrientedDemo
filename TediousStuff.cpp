#include "TediousStuff.hpp"

#include <cassert>

namespace {
inline int randomValue(int maxValue) { return rand() % maxValue; }

const std::vector<std::string> kStrings = {"foo", "bar", "baz",
                                           "some other string"};

auto makeInterpolator() {
  return LinearInterpolator{(float)(rand() % 256 - 256), (float)(rand() % 256)};
}
}  // namespace

namespace Tedious {

void makeModels(std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
                std::vector<OO::Static::Model> &staticModels,
                OO::StaticWithSpan::Input &staticWithSpanInput,
                DataOriented::Input &dataOrientedInput) {
  virtualModels.reserve(kNumberOfModels);
  staticModels.reserve(kNumberOfModels);
  staticWithSpanInput.models.reserve(kNumberOfModels);
  staticWithSpanInput.animations.reserve(kNumberOfAnimationsPerModel);
  dataOrientedInput.models.reserve(kNumberOfModels);
  dataOrientedInput.inputValues = std::vector<DataOriented::InputValue>();
  dataOrientedInput.inputValues.reserve(kNumberOfModels * 7);
  dataOrientedInput.interpolators.reserve(kNumberOfAnimationsPerModel);
  dataOrientedInput.interpolationResults =
      std::vector<float>(kNumberOfModels * 7);

  for (int i = 0; i < kNumberOfAnimationsPerModel; ++i) {
    dataOrientedInput.interpolators.push_back(makeInterpolator());
  }

  int totalSetProperties = 0;
  for (int i = 0; i < kNumberOfModels; ++i) {
    int numberOfProperties = 0;
    if (rand() % 2 == 0) {
      numberOfProperties = 7;
      auto virtualModel = std::make_unique<OO::Virtual::Text>();
      virtualModel->text = kStrings[rand() % kStrings.size()];
      virtualModel->x = rand() % 100;
      virtualModel->y = rand() % 100;
      virtualModel->red = rand() % 256;
      virtualModel->green = rand() % 256;
      virtualModel->blue = rand() % 256;
      virtualModel->scale = rand() % 100;
      virtualModel->opacity = rand() % 100;

      auto staticModel = OO::Static::Text();
      staticModel.text = virtualModel->text;
      staticModel.x = virtualModel->x;
      staticModel.y = virtualModel->y;
      staticModel.red = virtualModel->red;
      staticModel.green = virtualModel->green;
      staticModel.blue = virtualModel->blue;
      staticModel.scale = virtualModel->scale;
      staticModel.opacity = virtualModel->opacity;

      auto staticWithSpanModel = OO::StaticWithSpan::Text();
      staticWithSpanModel.text = virtualModel->text;
      staticWithSpanModel.x = virtualModel->x;
      staticWithSpanModel.y = virtualModel->y;
      staticWithSpanModel.red = virtualModel->red;
      staticWithSpanModel.green = virtualModel->green;
      staticWithSpanModel.blue = virtualModel->blue;
      staticWithSpanModel.scale = virtualModel->scale;
      staticWithSpanModel.opacity = virtualModel->opacity;

      dataOrientedInput.inputValues.push_back({virtualModel->x,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Add});
      dataOrientedInput.inputValues.push_back({virtualModel->y,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Add});
      dataOrientedInput.inputValues.push_back({virtualModel->red,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Multiply});
      dataOrientedInput.inputValues.push_back({virtualModel->green,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Multiply});
      dataOrientedInput.inputValues.push_back({virtualModel->blue,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Multiply});
      dataOrientedInput.inputValues.push_back({virtualModel->scale,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Multiply});
      dataOrientedInput.inputValues.push_back({virtualModel->opacity,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Replace});
      auto dataOrientedModel = DataOriented::Text(
          virtualModel->text,
          gsl::span(dataOrientedInput.interpolationResults.data() +
                        totalSetProperties,
                    numberOfProperties));

      virtualModels.emplace_back(virtualModel.release());
      staticModels.emplace_back(staticModel);
      staticWithSpanInput.models.emplace_back(staticWithSpanModel);
      dataOrientedInput.models.push_back(dataOrientedModel);
    } else {
      numberOfProperties = 4;
      auto virtualModel = std::make_unique<OO::Virtual::Image>();
      virtualModel->imageSource = kStrings[rand() % kStrings.size()];
      virtualModel->x = rand() % 100;
      virtualModel->y = rand() % 100;
      virtualModel->scale = rand() % 100;
      virtualModel->opacity = rand() % 100;

      auto staticModel = OO::Static::Image();
      staticModel.imageSource = virtualModel->imageSource;
      staticModel.x = virtualModel->x;
      staticModel.y = virtualModel->y;
      staticModel.scale = virtualModel->scale;
      staticModel.opacity = virtualModel->opacity;

      auto staticWithSpanModel = OO::StaticWithSpan::Image();
      staticWithSpanModel.imageSource = virtualModel->imageSource;
      staticWithSpanModel.x = virtualModel->x;
      staticWithSpanModel.y = virtualModel->y;
      staticWithSpanModel.scale = virtualModel->scale;
      staticWithSpanModel.opacity = virtualModel->opacity;

      dataOrientedInput.inputValues.push_back({virtualModel->x,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Add});
      dataOrientedInput.inputValues.push_back({virtualModel->y,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Add});
      dataOrientedInput.inputValues.push_back({virtualModel->scale,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Replace});
      dataOrientedInput.inputValues.push_back({virtualModel->opacity,
                                               gsl::span<LinearInterpolator>(),
                                               UpdateOperator::Replace});

      auto dataOrientedModel = DataOriented::Image(
          virtualModel->imageSource,
          gsl::span(dataOrientedInput.interpolationResults.data() +
                        totalSetProperties,
                    numberOfProperties));

      virtualModels.emplace_back(virtualModel.release());
      staticModels.emplace_back(staticModel);
      staticWithSpanInput.models.emplace_back(staticWithSpanModel);
      dataOrientedInput.models.push_back(dataOrientedModel);
    }

    totalSetProperties += numberOfProperties;
  }
}

void verifyInitialModels(
    const std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
    const std::vector<OO::Static::Model> &staticModels,
    const std::vector<OO::StaticWithSpan::Model> &staticWithSpanModels,
    const std::vector<DataOriented::InputValue> &dataOrientedInputs) {
  assert(virtualModels.size() == staticModels.size());
  assert(virtualModels.size() == staticWithSpanModels.size());

  size_t propertyCounter = 0;
  for (size_t i = 0; i < virtualModels.size(); ++i) {
    auto &staticModel = staticModels[i];
    auto &staticWithSpanModel = staticWithSpanModels[i];
    auto &virtualModel = virtualModels[i];

    if (std::holds_alternative<OO::Static::Text>(staticModel)) {
      auto vText = (OO::Virtual::Text *)virtualModel.get();
      auto sText = std::get<OO::Static::Text>(staticModel);
      auto swsText = std::get<OO::StaticWithSpan::Text>(staticWithSpanModel);

      assert(vText->x == sText.x);
      assert(vText->x == swsText.x);
      assert(vText->x == dataOrientedInputs[propertyCounter++].initialValue);
      assert(vText->y == sText.y);
      assert(vText->y == swsText.y);
      assert(vText->y == dataOrientedInputs[propertyCounter++].initialValue);
      assert(vText->red == sText.red);
      assert(vText->red == swsText.red);
      assert(vText->red == dataOrientedInputs[propertyCounter++].initialValue);
      assert(vText->green == sText.green);
      assert(vText->green == swsText.green);
      assert(vText->green ==
             dataOrientedInputs[propertyCounter++].initialValue);
      assert(vText->blue == sText.blue);
      assert(vText->blue == swsText.blue);
      assert(vText->blue == dataOrientedInputs[propertyCounter++].initialValue);
      assert(vText->scale == sText.scale);
      assert(vText->scale == swsText.scale);
      assert(vText->scale ==
             dataOrientedInputs[propertyCounter++].initialValue);
      assert(vText->opacity == sText.opacity);
      assert(vText->opacity == swsText.opacity);
      assert(vText->opacity ==
             dataOrientedInputs[propertyCounter++].initialValue);
    } else {
      auto vImage = (OO::Virtual::Image *)virtualModel.get();
      auto sImage = std::get<OO::Static::Image>(staticModel);
      auto swsImage = std::get<OO::StaticWithSpan::Image>(staticWithSpanModel);

      assert(vImage->x == sImage.x);
      assert(vImage->x == swsImage.x);
      assert(vImage->x == dataOrientedInputs[propertyCounter++].initialValue);
      assert(vImage->y == sImage.y);
      assert(vImage->y == swsImage.y);
      assert(vImage->y == dataOrientedInputs[propertyCounter++].initialValue);
      assert(vImage->scale == sImage.scale);
      assert(vImage->scale == swsImage.scale);
      assert(vImage->scale ==
             dataOrientedInputs[propertyCounter++].initialValue);
      assert(vImage->opacity == sImage.opacity);
      assert(vImage->opacity == swsImage.opacity);
      assert(vImage->opacity ==
             dataOrientedInputs[propertyCounter++].initialValue);
    }
  }
}

void verifyModels(
    const std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
    const std::vector<OO::Static::Model> &staticModels,
    const std::vector<OO::StaticWithSpan::Model> &staticWithSpanModels,
    const std::vector<float> &dataOrientedResults) {}

}  // namespace Tedious
