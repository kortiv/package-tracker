#pragma once

#include <string>

namespace use_cases {

struct AnswerOutputData {
    std::string answer;
    bool requires_human_review = false;
    std::string escalation_reason;
};

} // namespace use_cases
