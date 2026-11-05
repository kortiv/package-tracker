#pragma once

#include <string>

namespace interface_adapters {

struct AnswerViewModel {
    std::string answer;
    bool human_escalation = false;
    std::string escalation_reason;
};

} // namespace interface_adapters
