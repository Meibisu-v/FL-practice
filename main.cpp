#include "EarleyParser.h"
#include <iostream>
#include <string>

int main() {
  Earley_parser* parser = new Earley_parser();
  std::vector<Grammar_rule> rule_list;

  while (true) {
    std::string left_part, right_part;
    std::cin >> left_part;
    std::getline(std::cin, right_part);
    if (left_part == "end") {
      break;
    }
    if (!right_part.empty()) {
      right_part = right_part.substr(1, right_part.size() - 1);
    }
    if (left_part.size() != 1 || left_part[0] < 'A' || left_part[0] > 'Z') {
      std::cout << "Incorrect input: invalid character on the left side of the rule!" << std::endl;
      return 0;
    }
    rule_list.emplace_back(left_part[0], right_part);
  }

  parser->read_rules(rule_list);
  while (true) {
    std::string str;
    getline(std::cin, str);
    if (str == "end") {
      break;
    }
    std::cout << parser->check_word(str) << '\n';
  }
  return 0;
}