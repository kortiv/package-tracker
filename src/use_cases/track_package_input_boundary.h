#pragma once

// Dependency Rule: Use cases may depend on entities, but must not depend on
// interface adapters, frameworks, drivers, databases, or web libraries.

#include "use_cases/track_package_input_data.h"

namespace use_cases {

class TrackPackageInputBoundary {
public:
    virtual ~TrackPackageInputBoundary() = default;

    virtual void execute(const TrackPackageInputData& input_data) = 0;
};

} // namespace use_cases
