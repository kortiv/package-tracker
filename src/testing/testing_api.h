#pragma once

// Testing support is an outer composition layer. It may depend on interface
// adapters and use cases, but production code must not depend on this layer.

#include "entities/package.h"
#include "testing/fake_package_gateway.h"
#include "testing/fake_model_adapter.h"
#include "use_cases/answer_input_boundary.h"
#include "use_cases/answer_input_data.h"
#include "use_cases/answer_interactor.h"
#include "use_cases/answer_output_boundary.h"
#include "use_cases/answer_output_data.h"
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

    class AnswerOutputCapture final : public use_cases::AnswerOutputBoundary {
    public:
        void present(const use_cases::AnswerOutputData& output_data) override {
            response_ = output_data;
        }

        const use_cases::AnswerOutputData& response() const {
            return *response_;
        }

    private:
        std::optional<use_cases::AnswerOutputData> response_;
    };

public:
    TestingApi()
        : interactor_(gateway_, output_capture_),
          input_boundary_(interactor_),
          answer_interactor_(model_adapter_, answer_output_capture_),
          answer_input_boundary_(answer_interactor_) {}

    void reset() {
        gateway_.clear();
        output_capture_ = OutputCapture{};
        answer_output_capture_ = AnswerOutputCapture{};
    }

    void seed(const entities::Package& package) {
        gateway_.seed(package);
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

    void use_model_scenario(FakeModelAdapter::Scenario scenario) {
        model_adapter_.use_scenario(scenario);
    }

    use_cases::AnswerOutputData answer(std::string prompt) {
        answer_input_boundary_.execute(use_cases::AnswerInputData{
            std::move(prompt)});
        return answer_output_capture_.response();
    }

private:
    FakePackageGateway gateway_;
    OutputCapture output_capture_;
    use_cases::TrackPackageInteractor interactor_;
    use_cases::TrackPackageInputBoundary& input_boundary_;
    FakeModelAdapter model_adapter_;
    AnswerOutputCapture answer_output_capture_;
    use_cases::AnswerInteractor answer_interactor_;
    use_cases::AnswerInputBoundary& answer_input_boundary_;
};

} // namespace testing
