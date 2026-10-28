#pragma once

// Dependency Rule: Interface adapters may depend on inner layers, but inner
// layers must not depend on this adapter or its persistence implementation.

#include "use_cases/package_gateway.h"

#include <string>
#include <unordered_map>

namespace interface_adapters {

class InMemoryPackageGateway final : public use_cases::PackageGateway {
public:
    void save(const entities::Package& package) override;

    std::optional<entities::Package> find_by_tracking_number(
        const std::string& tracking_number) const override;

private:
    std::unordered_map<std::string, entities::Package> packages_;
};

} // namespace interface_adapters
