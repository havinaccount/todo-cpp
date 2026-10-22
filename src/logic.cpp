#include "logic.hpp"

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
namespace fs = std::filesystem;

namespace tasks {
[[nodiscard]] bool save_tasks(const std::vector<std::string>& vec) {
  std::ofstream file{"tasks.txt", std::ios::app};

  if (!file) {
    std::cerr << "Error: could not open tasks.txt.\n";
    return false;
  }

  for (const std::string& curr_task : vec) {
    file << curr_task << '\n';
  }

  return true;
}

[[nodiscard]] std::vector<std::string> load_tasks() {
  try {
    if (!fs::exists("tasks.txt")) {
      return {};
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << '\n';
    return {};
  }

  std::ifstream file{"tasks.txt"};

  if (!file) {
    std::cerr << "Error: could not open tasks.txt.\n";
    return {};
  }

  std::vector<std::string> tmp{};

  std::string task{};
  while (std::getline(file, task)) {
    tmp.push_back(task);
  }

  if (file.bad()) {
    std::cerr << "Error: failed to read tasks.txt.\n";
    return {};
  }

  return tmp;
}
}  // namespace tasks