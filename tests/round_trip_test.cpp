// Dependency Rule: Frameworks and drivers are the outermost layer. They may
// depend on all inner layers and compose concrete implementations for tests.

#include "interface_adapters/in_memory_package_gateway.h"
#include "interface_adapters/track_package_controller.h"
#include "interface_adapters/track_package_presenter.h"
#include "use_cases/track_package_interactor.h"

#include <cassert>
#include <stdexcept>
#include <string>

int main() {
    interface_adapters::InMemoryPackageGateway gateway;
    interface_adapters::TrackPackagePresenter presenter;
    use_cases::TrackPackageInteractor interactor(gateway, presenter);
    interface_adapters::TrackPackageController controller(interactor);

    controller.track_package("PKG-100", "In Transit");

    const auto first = presenter.latest_view_model();
    assert(first.has_value());
    assert(first->tracking_number == "PKG-100");
    assert(first->status == "In Transit");

    controller.track_package("PKG-100", "Delivered");

    const auto second = presenter.latest_view_model();
    assert(second.has_value());
    assert(second->tracking_number == "PKG-100");
    assert(second->status == "In Transit");

    bool threw = false;
    try {
        controller.track_package("");
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    return 0;
}
