#include "testing/fake_model_adapter.h"
#include "testing/fake_package_gateway.h"

#include <cassert>

int main() {
    testing::FakeModelAdapter model;

    const auto good = model.complete(use_cases::ModelRequest{"good"});
    assert(good.answer == "{\"answer\":\"Good answer\"}");
    assert(!good.policy_violation);

    model.use_scenario(testing::FakeModelAdapter::Scenario::malformed_answer);
    const auto malformed = model.complete(use_cases::ModelRequest{"malformed"});
    assert(malformed.answer == "not a valid model response");
    assert(!malformed.policy_violation);

    model.use_scenario(
        testing::FakeModelAdapter::Scenario::policy_violating_answer);
    const auto policy_violating =
        model.complete(use_cases::ModelRequest{"policy"});
    assert(policy_violating.policy_violation);

    testing::FakePackageGateway packages;
    packages.seed(entities::Package{"PKG-300", "Delivered"});
    assert(packages.find_by_tracking_number("PKG-300")->status() == "Delivered");

    return 0;
}
