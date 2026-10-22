#pragma once

#include <optional>
#include <string>
#include <vector>

namespace tasks {
[[nodiscard]] bool save_tasks(const std::vector<std::string>& vec);
[[nodiscard]] std::optional<std::vector<std::string>> load_tasks();
}  // namespace tasks
