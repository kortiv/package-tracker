#pragma once

// Testing support provides deterministic gateway implementations. Production
// code must not depend on this layer.

#include "use_cases/model_gateway.h"

#include <array>
#include <cstddef>
#include <string>
#include <utility>

namespace testing {

class FakeModelAdapter final : public use_cases::ModelGateway {
public:
    enum class Scenario {
        good_answer,
        malformed_answer,
        policy_violating_answer
    };

    FakeModelAdapter() {
        responses_[index(Scenario::good_answer)] =
            use_cases::ModelResponse{"{\"answer\":\"Good answer\"}", false};
        responses_[index(Scenario::malformed_answer)] =
            use_cases::ModelResponse{"not a valid model response", false};
        responses_[index(Scenario::policy_violating_answer)] =
            use_cases::ModelResponse{"{\"answer\":\"Policy-violating answer\"}", true};
    }

    void use_scenario(Scenario scenario) {
        scenario_ = scenario;
    }

    void script(Scenario scenario, use_cases::ModelResponse response) {
        responses_[index(scenario)] = std::move(response);
    }

    use_cases::ModelResponse complete(
        const use_cases::ModelRequest& request) override {
        last_request_ = request;
        return responses_[index(scenario_)];
    }

    const use_cases::ModelRequest& last_request() const {
        return last_request_;
    }

private:
    static constexpr std::size_t index(Scenario scenario) {
        return static_cast<std::size_t>(scenario);
    }

    std::array<use_cases::ModelResponse, 3> responses_;
    Scenario scenario_ = Scenario::good_answer;
    use_cases::ModelRequest last_request_;
};

} // namespace testing
