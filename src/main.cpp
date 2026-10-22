// #include <cstdlib>
// #include <ios>
// #include <iostream>
// #include <limits>

// namespace {
// [[nodiscard]] constexpr bool isEven(const int& a) noexcept {
//   return a % 2 == 0;
// }
// [[nodiscard]] constexpr bool isPositive(const int& a) noexcept { return a >
// 0; } }  // namespace int main() {
//   int number{};

//   std::cout << "Enter an integer: ";

//   while (!(std::cin >> number)) {
//     if (std::cin.eof()) {
//       std::cout << '\n';
//       return 1;
//     }
//     std::cin.clear();
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     std::cout << "Invalid input. Enter an integer: ";
//   }

//   const long long magnitude{std::abs(static_cast<long long>(number))};

//   if (number == 0) {
//     std::cout << "Zero\n";
//   } else if (isPositive(number)) {
//     std::cout << "Positive\n";
//   } else {
//     std::cout << "Negative\n";
//   }

//   std::cout << (isEven(number) ? "Even\n" : "Odd\n");

//   std::cout << "Numbers: ";

//   for (long long i{1}; i <= magnitude; i++) {
//     std::cout << i << ' ';
//   }

//   std::cout << '\n';

//   std::cout << "Sum: " << magnitude * (magnitude + 1) / 2 << '\n';
//   return 0;
// }

// #include <iostream>
// #include <new>
//
// int main() {
//   int* ptr;
//
//   try {
//     ptr = new int{32};
//   } catch (const std::bad_alloc& s) {
//     std::cerr << "Allocation failed!\n";
//     return 1;
//   }
//
//   std::cout << "Hello, World!\n" << *ptr << '\n';
//
//   delete ptr;
//
//   if (ptr == nullptr) {
//     std::cout << "nullptr in ptr\n";
//   }
//
//   return 0;
// }

#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "logic.hpp"

int main() {
  std::string command{};
  std::vector<std::string> tasks = tasks::load_tasks();

  while (true) {
    std::cout << "Enter a command: ";

    if (!std::getline(std::cin, command)) {
      break;
    }

    if (command == "add") {
      std::string task{};
      std::cout << "Task description: ";

      if (!std::getline(std::cin, task)) break;

      tasks.push_back(task);
      if (!tasks::save_tasks(tasks)) {
	std::cout << "Failed to add the task.\n";
	continue;
      }
      std::cout << "Task added!\n";
    } else if (command == "quit" || command == "q") {
      std::cout << "\nExiting...\n";
      break;
    } else if (command == "list") {
      if (tasks.empty()) {
	std::cout << "Still no tasks...\n";
	continue;
      }

      for (std::size_t i = 0; i < tasks.size(); ++i) {
	std::cout << (i + 1) << ". " << tasks[i] << '\n';
      }
      std::cout << '\n';
    } else if (command == "remove") {
      int request{};

      std::cout << "Task number to remove: ";
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
	    static_cast<std::size_t>(request) <= tasks.size())) {
	std::cout << "Invalid task, try again.\n";
	continue;
      }

      tasks.erase(tasks.begin() + (request - 1));
      if (!tasks::save_tasks(tasks)) {
	std::cout << "Failed to save the task.\n";
	break;
      }
      std::cout << "Task removed!\n";
    } else {
      std::cout << "Invalid choice, try again.\n";
    }
  }

  return 0;
}