// Dependency Rule: Interface adapters may depend on inner layers, but inner
// layers must not depend on this adapter or its persistence implementation.

#include "interface_adapters/in_memory_package_gateway.h"

namespace interface_adapters {

void InMemoryPackageGateway::save(const entities::Package& package) {
    packages_.insert_or_assign(package.tracking_number(), package);
}

std::optional<entities::Package>
InMemoryPackageGateway::find_by_tracking_number(
    const std::string& tracking_number) const {
    const auto it = packages_.find(tracking_number);

    if (it == packages_.end()) {
        return std::nullopt;
    }

    return it->second;
}

} // namespace interface_adapters
