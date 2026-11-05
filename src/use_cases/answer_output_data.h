#pragma once

#include <string>

namespace use_cases {

struct AnswerOutputData {
    std::string answer;
    bool human_escalation = false;
    std::string escalation_reason;
};

} // namespace use_cases
