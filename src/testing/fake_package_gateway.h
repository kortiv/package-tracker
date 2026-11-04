#pragma once

// Testing support provides deterministic gateway implementations. Production
// code must not depend on this layer.

#include "entities/package.h"
#include "use_cases/package_gateway.h"

#include <optional>
#include <string>
#include <unordered_map>

namespace testing {

class FakePackageGateway final : public use_cases::PackageGateway {
public:
    void clear() {
        packages_.clear();
    }

    void seed(const entities::Package& package) {
        save(package);
    }

    void save(const entities::Package& package) override {
        packages_.insert_or_assign(package.tracking_number(), package);
    }

    std::optional<entities::Package> find_by_tracking_number(
        const std::string& tracking_number) const override {
        const auto it = packages_.find(tracking_number);
        if (it == packages_.end()) {
            return std::nullopt;
        }

        return it->second;
    }

private:
    std::unordered_map<std::string, entities::Package> packages_;
};

} // namespace testing
