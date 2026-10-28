#pragma once

// Dependency Rule: Interface adapters may depend on inner layers, but inner
// layers must not depend on this adapter or presentation details.

#include <string>

namespace interface_adapters {

struct TrackPackageViewModel {
    std::string tracking_number;
    std::string status;
};

} // namespace interface_adapters
