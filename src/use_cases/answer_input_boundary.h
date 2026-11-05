#pragma once

#include "use_cases/answer_input_data.h"

namespace use_cases {

class AnswerInputBoundary {
public:
    virtual ~AnswerInputBoundary() = default;

    virtual void execute(const AnswerInputData& input_data) = 0;
};

} // namespace use_cases
