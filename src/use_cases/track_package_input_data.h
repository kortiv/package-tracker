#pragma once

// Dependency Rule: Use cases may depend on entities, but must not depend on
// interface adapters, frameworks, drivers, databases, or web libraries.

#include <optional>
#include <string>

namespace use_cases {

struct TrackPackageInputData {
    std::string tracking_number;
    std::optional<std::string> initial_status;
};

} // namespace use_cases
