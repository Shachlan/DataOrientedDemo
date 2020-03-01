#include "DataOriented.hpp"
#include "StaticOO.hpp"
#include "StaticWithSpan.hpp"
#include "VirtualOO.hpp"

namespace Tedious {

/// Populates the given objects with models and animations.
void makeModels(std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
                std::vector<OO::Static::Model> &staticModels,
                OO::StaticWithSpan::Input &staticWithSpanInput,
                DataOriented::Input &dataOrientedInput, int numberOfModels,
                int numberOfAnimationsPerModel);

/// Verifies that all of the models across the different implementations are the
/// same.
void verifyInitialModels(
    const std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
    const std::vector<OO::Static::Model> &staticModels,
    const std::vector<OO::StaticWithSpan::Model> &staticWithSpanModels,
    const std::vector<DataOriented::InputValue> &dataOrientedInputs);

/// Verifies that all of the models across the different implementations have
/// been interpolated in the same way.
void verifyModels(
    const std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
    const std::vector<OO::Static::Model> &staticModels,
    const std::vector<OO::StaticWithSpan::Model> &staticWithSpanModels,
    const std::vector<DataOriented::Model> &dataOrientedModels);

}  // namespace Tedious
