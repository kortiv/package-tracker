#include "testing/testing_api.h"

#include <cassert>
#include <stdexcept>

void existing_package_keeps_its_persisted_status() {
    testing::TestingApi api;
    api.seed("PKG-400", "Delivered");

    const auto response = api.track_package("PKG-400", "In Transit");

    assert(response.status == "Delivered");
}

void empty_tracking_number_is_rejected() {
    testing::TestingApi api;

    bool rejected = false;
    try {
        api.track_package("");
    } catch (const std::invalid_argument&) {
        rejected = true;
    }

    assert(rejected);
}

void valid_model_output_is_returned_as_an_answer() {
    testing::TestingApi api;

    const auto response = api.answer("What is the package status?");

    assert(response.answer == "Good answer");
    assert(!response.requires_human_review);
}

void malformed_model_output_is_off_ramped_to_a_human() {
    testing::TestingApi api;
    api.use_model_scenario(
        testing::FakeModelAdapter::Scenario::malformed_answer);

    const auto response = api.answer("Summarize the shipment.");

    assert(response.requires_human_review);
    assert(response.escalation_reason == "Model response was malformed");
}

void policy_violating_model_output_is_off_ramped_to_a_human() {
    testing::TestingApi api;
    api.use_model_scenario(
        testing::FakeModelAdapter::Scenario::policy_violating_answer);

    const auto response = api.answer("Handle this request.");

    assert(response.requires_human_review);
    assert(response.escalation_reason == "Model response violated policy");
}

void empty_prompt_is_rejected() {
    testing::TestingApi api;

    bool rejected = false;
    try {
        api.answer("");
    } catch (const std::invalid_argument&) {
        rejected = true;
    }

    assert(rejected);
}

int main() {
    existing_package_keeps_its_persisted_status();
    empty_tracking_number_is_rejected();
    valid_model_output_is_returned_as_an_answer();
    malformed_model_output_is_off_ramped_to_a_human();
    policy_violating_model_output_is_off_ramped_to_a_human();
    empty_prompt_is_rejected();
}
