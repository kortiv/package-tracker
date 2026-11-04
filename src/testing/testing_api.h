#pragma once

// Testing support is an outer composition layer. It may depend on interface
// adapters and use cases, but production code must not depend on this layer.

#include "entities/package.h"
#include "interface_adapters/in_memory_package_gateway.h"
#include "use_cases/track_package_input_boundary.h"
#include "use_cases/track_package_input_data.h"
#include "use_cases/track_package_interactor.h"
#include "use_cases/track_package_output_boundary.h"
#include "use_cases/track_package_output_data.h"

#include <optional>
#include <string>
#include <utility>

namespace testing {

class TestingApi {
private:
    class OutputCapture final : public use_cases::TrackPackageOutputBoundary {
    public:
        void present(const use_cases::TrackPackageOutputData& output_data) override {
            response_ = output_data;
        }

        const use_cases::TrackPackageOutputData& response() const {
            return *response_;
        }

    private:
        std::optional<use_cases::TrackPackageOutputData> response_;
    };

public:
    TestingApi()
        : interactor_(gateway_, output_capture_),
          input_boundary_(interactor_) {}

    void reset() {
        gateway_.clear();
        output_capture_ = OutputCapture{};
    }

    void seed(const entities::Package& package) {
        gateway_.save(package);
    }

    void seed(std::string tracking_number, std::string status) {
        seed(entities::Package(
            std::move(tracking_number),
            std::move(status)));
    }

    use_cases::TrackPackageOutputData track_package(
        std::string tracking_number,
        std::optional<std::string> initial_status = std::nullopt) {
        input_boundary_.execute(use_cases::TrackPackageInputData{
            std::move(tracking_number),
            std::move(initial_status)});
        return output_capture_.response();
    }

private:
    interface_adapters::InMemoryPackageGateway gateway_;
    OutputCapture output_capture_;
    use_cases::TrackPackageInteractor interactor_;
    use_cases::TrackPackageInputBoundary& input_boundary_;
};

} // namespace testing
