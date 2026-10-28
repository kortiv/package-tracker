#pragma once

// Dependency Rule: Use cases may depend on entities, but must not depend on
// interface adapters, frameworks, drivers, databases, or web libraries.

#include "use_cases/package_gateway.h"
#include "use_cases/track_package_input_boundary.h"
#include "use_cases/track_package_output_boundary.h"

#include <stdexcept>
#include <string>
#include <utility>

namespace use_cases {

class TrackPackageInteractor final : public TrackPackageInputBoundary {
public:
    TrackPackageInteractor(
        PackageGateway& gateway,
        TrackPackageOutputBoundary& output_boundary)
        : gateway_(gateway),
          output_boundary_(output_boundary) {}

    void execute(const TrackPackageInputData& input_data) override {
        if (input_data.tracking_number.empty()) {
            throw std::invalid_argument("Tracking number cannot be empty");
        }

        auto package = gateway_.find_by_tracking_number(input_data.tracking_number);

        if (!package.has_value()) {
            const std::string status = input_data.initial_status.value_or("Registered");
            package = entities::Package(input_data.tracking_number, status);
            gateway_.save(*package);
        }

        output_boundary_.present(TrackPackageOutputData{
            package->tracking_number(),
            package->status()});
    }

private:
    PackageGateway& gateway_;
    TrackPackageOutputBoundary& output_boundary_;
};

} // namespace use_cases
