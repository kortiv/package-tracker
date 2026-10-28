#pragma once

// Dependency Rule: Interface adapters may depend on inner layers, but inner
// layers must not depend on this adapter or presentation details.

#include "interface_adapters/track_package_view_model.h"
#include "use_cases/track_package_output_boundary.h"

#include <optional>

namespace interface_adapters {

class TrackPackagePresenter final : public use_cases::TrackPackageOutputBoundary {
public:
    void present(const use_cases::TrackPackageOutputData& output_data) override {
        latest_view_model_ = TrackPackageViewModel{
            output_data.tracking_number,
            output_data.status};
    }

    const std::optional<TrackPackageViewModel>& latest_view_model() const {
        return latest_view_model_;
    }

private:
    std::optional<TrackPackageViewModel> latest_view_model_;
};

} // namespace interface_adapters
