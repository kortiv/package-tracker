#pragma once

// Dependency Rule: Use cases may depend on entities and boundary data, but
// must not depend on interface adapters, frameworks, drivers, or web libraries.

#include <string>

namespace use_cases {

struct ModelRequest {
    std::string prompt;
};

struct ModelResponse {
    std::string answer;
    bool policy_violation = false;
};

class ModelGateway {
public:
    virtual ~ModelGateway() = default;

    virtual ModelResponse complete(const ModelRequest& request) = 0;
};

} // namespace use_cases
