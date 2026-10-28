#pragma once

// Dependency Rule: Use cases may depend on entities, but must not depend on
// interface adapters, frameworks, drivers, databases, or web libraries.

#include <string>

namespace use_cases {

struct TrackPackageOutputData {
    std::string tracking_number;
    std::string status;
};

} // namespace use_cases
