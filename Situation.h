#pragma once
#include <string>

struct Grammar_rule {
  char left_part;
  std::string right_part;
  Grammar_rule() = default;
  Grammar_rule(char lhs, const std::string& rhs): left_part(lhs), right_part(rhs) {}
};

class Situation {
public:
  Grammar_rule* rule;
  size_t dot_position;
  size_t start;

  Situation() = default;
  Situation(Grammar_rule* rule, int dot_position, size_t start): 
            rule(rule), dot_position(dot_position), start(start) {}

  bool operator==(const Situation& other) const {
    return rule == other.rule && dot_position == other.dot_position && start == other.start;
  }
};
