#include "DataOriented.hpp"
#include "StaticOO.hpp"
#include "StaticWithSpan.hpp"
#include "VirtualOO.hpp"

namespace Tedious {

inline constexpr auto kNumberOfModels = 2;
inline constexpr auto kNumberOfAnimationsPerModel = 10;
inline constexpr auto kTotalNumberOfAnimations =
    kNumberOfModels * kNumberOfAnimationsPerModel;

void makeModels(std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
                std::vector<OO::Static::Model> &staticModels,
                OO::StaticWithSpan::Input &staticWithSpanInput,
                DataOriented::Input &dataOrientedInput);

void verifyInitialModels(
    const std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
    const std::vector<OO::Static::Model> &staticModels,
    const std::vector<OO::StaticWithSpan::Model> &staticWithSpanModels,
    const std::vector<DataOriented::InputValue> &dataOrientedInputs);

void verifyModels(
    const std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
    const std::vector<OO::Static::Model> &staticModels,
    const std::vector<OO::StaticWithSpan::Model> &staticWithSpanModels,
    const std::vector<DataOriented::Model> &dataOrientedModels);

}  // namespace Tedious
