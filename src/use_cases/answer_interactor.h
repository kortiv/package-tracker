#pragma once

#include "use_cases/answer_input_boundary.h"
#include "use_cases/answer_output_boundary.h"
#include "use_cases/model_gateway.h"

#include <optional>
#include <stdexcept>
#include <string>

namespace use_cases {

class AnswerInteractor final : public AnswerInputBoundary {
private:
    class ModelResponseParser {
    public:
        static std::optional<std::string> parse(const std::string& response) {
            if (!is_well_formed(response)) {
                return std::nullopt;
            }

            return response.substr(11, response.size() - 13);
        }

    private:
        static bool is_well_formed(const std::string& answer) {
            return answer.size() >= 11 &&
                   answer.front() == '{' &&
                   answer.back() == '}' &&
                   answer.rfind("{\"answer\":\"", 0) == 0 &&
                   answer.substr(answer.size() - 2) == "\"}";
        }
    };

public:
    AnswerInteractor(
        ModelGateway& model_gateway,
        AnswerOutputBoundary& output_boundary)
        : model_gateway_(model_gateway),
          output_boundary_(output_boundary) {}

    void execute(const AnswerInputData& input_data) override {
        if (input_data.prompt.empty()) {
            throw std::invalid_argument("Prompt cannot be empty");
        }

        const ModelResponse response =
            model_gateway_.complete(ModelRequest{input_data.prompt});

        if (response.policy_violation) {
            output_boundary_.present(AnswerOutputData{
                {},
                true,
                "Model response violated policy"});
            return;
        }

        const auto answer = ModelResponseParser::parse(response.answer);
        if (!answer.has_value()) {
            output_boundary_.present(AnswerOutputData{
                {},
                true,
                "Model response was malformed"});
            return;
        }

        output_boundary_.present(AnswerOutputData{
            *answer,
            false,
            {}});
    }

private:
    ModelGateway& model_gateway_;
    AnswerOutputBoundary& output_boundary_;
};

} // namespace use_cases
