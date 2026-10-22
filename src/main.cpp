#include <cstddef>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "logic.hpp"

int main() {
  std::string command{};
  std::optional<std::vector<std::string> > tasks = tasks::load_tasks();

  if (!tasks) {
    std::cerr << "Failed to load the tasks.\n";
    return 1;
  }

  std::vector<std::string> list_tasks = std::move(tasks.value());

  while (true) {
    std::cout << "Enter a command: " << std::flush;

    if (!std::getline(std::cin, command)) break;

    if (command == "add") {
      std::string task{};
      std::cout << "Task description: " << std::flush;

      if (!std::getline(std::cin, task)) break;

      std::vector<std::string> tmp = list_tasks;

      tmp.push_back(task);

      if (!tasks::save_tasks(tmp)) {
        std::cerr << "Failed to add the task.\n";
        continue;
      }

      list_tasks = std::move(tmp);

      std::cout << "Task added!\n";
    } else if (command == "quit" || command == "q") {
      std::cout << "\nExiting...\n";
      break;
    } else if (command == "list") {
      if (list_tasks.empty()) {
        std::cout << "Still no tasks...\n";
        continue;
      }

      for (std::size_t i = 0; i < list_tasks.size(); ++i)
        std::cout << (i + 1) << ". " << list_tasks[i] << '\n';

      std::cout << '\n';
    } else if (command == "remove") {
      int request{};

      std::cout << "Task number to remove: " << std::flush;
      if (!(std::cin >> request)) {
        if (std::cin.eof()) {
          std::cout << '\n';
          return 0;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << '\n';
        continue;
      }

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (!(request >= 1 &&
            static_cast<std::size_t>(request) <= list_tasks.size())) {
        std::cout << "Invalid task, try again.\n";
        continue;
      }

      std::vector<std::string> tmp = list_tasks;

      tmp.erase(tmp.begin() + (request - 1));
      if (!tasks::save_tasks(tmp)) {
        std::cerr << "Failed to save the task.\n";
        continue;
      }

      list_tasks = std::move(tmp);
      std::cout << "Task removed!\n";
    } else {
      std::cout << "Invalid choice, try again.\n";
    }
  }

  return 0;
}
