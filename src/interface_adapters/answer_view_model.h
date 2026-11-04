#pragma once

#include <string>

namespace interface_adapters {

struct AnswerViewModel {
    std::string answer;
    bool requires_human_review = false;
    std::string escalation_reason;
};

} // namespace interface_adapters
