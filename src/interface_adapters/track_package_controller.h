#pragma once

// Dependency Rule: Interface adapters may depend on inner layers, but inner
// layers must not depend on this adapter or delivery mechanism details.

#include "use_cases/track_package_input_boundary.h"
#include "use_cases/track_package_input_data.h"

#include <optional>
#include <string>
#include <utility>

namespace interface_adapters {

class TrackPackageController {
public:
    explicit TrackPackageController(use_cases::TrackPackageInputBoundary& input_boundary)
        : input_boundary_(input_boundary) {}

    void track_package(
        std::string tracking_number,
        std::optional<std::string> initial_status = std::nullopt) const {
        input_boundary_.execute(use_cases::TrackPackageInputData{
            std::move(tracking_number),
            std::move(initial_status)});
    }

private:
    use_cases::TrackPackageInputBoundary& input_boundary_;
};

} // namespace interface_adapters
