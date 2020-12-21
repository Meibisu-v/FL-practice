#include "Situation.h"
#include <vector>
#include <list>

class Earley_parser {
private:
  std::vector<Grammar_rule> input_rules;

  void scan(std::vector<std::vector<Situation>> &D, size_t current_position, 
            const std::string &word);
  void complete(std::vector<std::vector<Situation>> &D, size_t current_position,
                bool &is_changed);
  void predict(std::vector<std::vector<Situation>> &D, size_t current_position,
                bool &is_changed);
public:
  Earley_parser() = default;
  void read_rules(const std::vector<Grammar_rule> &rules);
  bool check_word(const std::string &word);
};
