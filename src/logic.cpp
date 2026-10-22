#include "logic.hpp"

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace tasks {
[[nodiscard]] bool save_tasks(const std::vector<std::string>& vec) {
  std::ofstream file{"tasks.txt", std::ios::trunc};

  if (!file) return false;

  for (const std::string& curr_task : vec) {
    file << curr_task << '\n';
  }

  file.close();

  if (!file) return false;

  return true;
}

[[nodiscard]] std::optional<std::vector<std::string>> load_tasks() {
  try {
    if (!fs::exists("tasks.txt")) {
      return std::vector<std::string>{};
    }
  } catch ([[maybe_unused]] const fs::filesystem_error& e) {
    return std::nullopt;
  }

  std::ifstream file{"tasks.txt"};

  if (!file) {
    return std::nullopt;
  }

  std::vector<std::string> tmp{};

  std::string task{};
  while (std::getline(file, task)) {
    tmp.push_back(task);
  }

  if (file.bad()) {
    return std::nullopt;
  }

  return tmp;
}
}  // namespace tasks