#pragma once

// Dependency Rule: Entities are the innermost layer and must not depend on
// use cases, interface adapters, frameworks, drivers, or external libraries.

#include <string>
#include <utility>

namespace entities {

class Package {
public:
    Package(std::string tracking_number, std::string status)
        : tracking_number_(std::move(tracking_number)),
          status_(std::move(status)) {}

    const std::string& tracking_number() const {
        return tracking_number_;
    }

    const std::string& status() const {
        return status_;
    }

private:
    std::string tracking_number_;
    std::string status_;
};

} // namespace entities
