#pragma once

// Dependency Rule: Use cases may depend on entities, but must not depend on
// interface adapters, frameworks, drivers, databases, or web libraries.

#include "use_cases/track_package_output_data.h"

namespace use_cases {

class TrackPackageOutputBoundary {
public:
    virtual ~TrackPackageOutputBoundary() = default;

    virtual void present(const TrackPackageOutputData& output_data) = 0;
};

} // namespace use_cases
