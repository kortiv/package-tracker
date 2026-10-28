#pragma once

// Dependency Rule: Use cases may depend on entities, but must not depend on
// interface adapters, frameworks, drivers, databases, or web libraries.

#include "entities/package.h"

#include <optional>
#include <string>

namespace use_cases {

class PackageGateway {
public:
    virtual ~PackageGateway() = default;

    virtual void save(const entities::Package& package) = 0;

    virtual std::optional<entities::Package> find_by_tracking_number(
        const std::string& tracking_number) const = 0;
};

} // namespace use_cases
