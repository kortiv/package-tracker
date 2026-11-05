#pragma once

#include "interface_adapters/answer_view_model.h"
#include "use_cases/answer_output_boundary.h"

#include <optional>

namespace interface_adapters {

class AnswerPresenter final : public use_cases::AnswerOutputBoundary {
public:
    void present(const use_cases::AnswerOutputData& output_data) override {
        latest_view_model_ = AnswerViewModel{
            output_data.answer,
            output_data.human_escalation,
            output_data.escalation_reason};
    }

    const std::optional<AnswerViewModel>& latest_view_model() const {
        return latest_view_model_;
    }

private:
    std::optional<AnswerViewModel> latest_view_model_;
};

} // namespace interface_adapters
