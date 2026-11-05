#include "testing/testing_api.h"

#include <cassert>
#include <stdexcept>

int main() {
    testing::TestingApi api;

    api.seed("PKG-200", "Delivered");
    const auto existing = api.track_package("PKG-200", "In Transit");
    assert(existing.tracking_number == "PKG-200");
    assert(existing.status == "Delivered");

    api.reset();
    const auto created = api.track_package("PKG-201", "In Transit");
    assert(created.tracking_number == "PKG-201");
    assert(created.status == "In Transit");

    bool threw = false;
    try {
        api.track_package("");
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    return 0;
}
