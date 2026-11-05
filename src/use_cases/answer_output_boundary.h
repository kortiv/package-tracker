#pragma once

#include "use_cases/answer_output_data.h"

namespace use_cases {

class AnswerOutputBoundary {
public:
    virtual ~AnswerOutputBoundary() = default;

    virtual void present(const AnswerOutputData& output_data) = 0;
};

} // namespace use_cases
