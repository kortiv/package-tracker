// Dependency Rule: Frameworks and drivers are the outermost layer. They may
// depend on all inner layers and compose concrete implementations.

#include "interface_adapters/in_memory_package_gateway.h"
#include "interface_adapters/track_package_controller.h"
#include "interface_adapters/track_package_presenter.h"
#include "use_cases/track_package_interactor.h"

#include <cstdlib>
#include <iostream>

int main() {
    interface_adapters::InMemoryPackageGateway gateway;
    interface_adapters::TrackPackagePresenter presenter;
    use_cases::TrackPackageInteractor interactor(gateway, presenter);
    interface_adapters::TrackPackageController controller(interactor);

    controller.track_package("PKG-12345", "Registered");

    const auto& view_model = presenter.latest_view_model();
    if (!view_model.has_value()) {
        std::cerr << "No tracking data available\n";
        return EXIT_FAILURE;
    }

    std::cout << "Tracking number: " << view_model->tracking_number << '\n';
    std::cout << "Status: " << view_model->status << '\n';

    return EXIT_SUCCESS;
}
