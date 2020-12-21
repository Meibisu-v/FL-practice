#include "EarleyParser.h"
#include "Situation.h"
#include <iostream>
#include <list>
#include <set>

void Earley_parser::read_rules(const std::vector<Grammar_rule> &rules) {
  input_rules.emplace_back('$', "S");

  for (const auto &i : rules) {
    input_rules.push_back(i);
  }
}

bool Earley_parser::check_word(const std::string &input_word) {
  std::vector<std::vector<Situation>> D(input_word.size() + 1, std::vector<Situation>(0));
  D[0].emplace_back(&input_rules.front(), 0, 0);

  for (size_t i = 0; i <= input_word.size(); ++i) {
    scan(D, i, input_word);
    bool is_changed = true;
    while (is_changed) {
      is_changed = false;
      predict(D, i, is_changed);
      complete(D, i, is_changed);
    }
  }

  for (auto &i : D.back()) {
    if (i.rule == &input_rules.front() && i.dot_position == 1 && i.start == 0) {
      return true;
    }
  }

  return false;
}

void Earley_parser::scan(std::vector<std::vector<Situation>> &D,
                         size_t current_position, const std::string &word) {
  if (current_position == 0) {
    return;
  }
  for (auto i : D[current_position - 1]) {
    if (i.rule->right_part[i.dot_position] == word[current_position - 1]) {
      ++i.dot_position;
      D[current_position].emplace_back(i);
    }
  }
}

bool can_add(std::vector<Situation> &D, const Situation &situation, bool &is_changed) {
  for (auto &j : D) {
    if (j == situation) {
      return  false;
    }
  }   
  D.push_back(situation);
  is_changed = true;
  return true;
}

void Earley_parser::complete(std::vector<std::vector<Situation>> &D,
                             size_t current_position, bool &is_changed) {
  std::list<Situation> to_add;
  for (const auto &part_rule : D[current_position]) {
    if (part_rule.dot_position == part_rule.rule->right_part.size()) {
      for (const auto &full_rule : D[part_rule.start]) {
        if (full_rule.rule->right_part[full_rule.dot_position] == part_rule.rule->left_part) {
          to_add.emplace_back(full_rule.rule, full_rule.dot_position + 1, full_rule.start);
        }
      }
    }
  }
  for (const auto &i : to_add) {
    can_add(D[current_position], i, is_changed);
  }
}


void Earley_parser::predict(std::vector<std::vector<Situation>> &D,
                            size_t current_position, bool &is_changed) {
  std::list<Situation> to_add;
  for (const auto &i : D[current_position]) {
    for (auto &j : input_rules) {
      if (j.left_part == i.rule->right_part[i.dot_position]) {
        to_add.emplace_back(&j, 0, current_position);
      }
    }
  }
  for (const auto &i : to_add) {
    can_add(D[current_position], i, is_changed);
  }
}
