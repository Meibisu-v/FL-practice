#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "EarleyParser.h"

TEST(OnlyOneALetter, a) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "a");

  parser->read_rules(rules);
  std::string str = "a";
  EXPECT_EQ(parser->check_word(str), 1);
  str = "b";
  EXPECT_EQ(parser->check_word(str), 0);
  str = "aaa";
  EXPECT_EQ(parser->check_word(str), 0);
  str = "";
  EXPECT_EQ(parser->check_word(str), 0);
}

TEST(OnlyALetters, ALotOfA) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "T");
  rules.emplace_back('T', "aT");
  rules.emplace_back('T', "");

  parser->read_rules(rules);

  std::string str = "aaaaaaaaaaaaaaaaaaaaaaaaa";
  EXPECT_EQ(parser->check_word(str), 1);

  str = "";
  EXPECT_EQ(parser->check_word(str), 1);

  str = "a";
  EXPECT_EQ(parser->check_word(str), 1);

  str = "aaaaaaaaba";
  EXPECT_EQ(parser->check_word(str), 0);
}

TEST(CorrectBracketSequence, Correct) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "");
  rules.emplace_back('A', "(A)A");

  parser->read_rules(rules);
  std::string str = "(()()())()()()((((()))))";
  EXPECT_EQ(parser->check_word(str), 1);

  str = "(()()())()()()((((())))))";
  EXPECT_EQ(parser->check_word(str), 0);

  str = "";
  EXPECT_EQ(parser->check_word(str), 1);

  str = "()";
  EXPECT_EQ(parser->check_word(str), 1);
}

TEST(TwoCorrectBracketSequence, SmallCorrect) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "");
  rules.emplace_back('A', "(A)A");
  rules.emplace_back('A', "aAbA");

  parser->read_rules(rules);

  std::string str = "(ab)";
  EXPECT_EQ(parser->check_word(str), 1);
 
  str = "(a)b";
  EXPECT_EQ(parser->check_word(str), 0);
 
  str = "(aabbab()(ab))()(((a()()b)))";
  EXPECT_EQ(parser->check_word(str), 1);
}

TEST(TwoCorrectBracketSequence, Wrong) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "");
  rules.emplace_back('A', "(A)A");
  rules.emplace_back('A', "aAbA");

  parser->read_rules(rules);
  std::string str = "(aabbab()(ab))(a)(b((a()()b)))";
  EXPECT_EQ(parser->check_word(str), 0);
}

TEST(Palindromes, Correct) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "aAa");
  rules.emplace_back('A', "a");
  rules.emplace_back('A', "bAb");
  rules.emplace_back('A', "b");
  rules.emplace_back('A', "cAc");
  rules.emplace_back('A', "c");
  rules.emplace_back('A', "");


  parser->read_rules(rules);
  std::string str = "aabbcbbaa";
  EXPECT_EQ(parser->check_word(str), 1); 
  
  str = "aabbccbbbaa";
  EXPECT_EQ(parser->check_word(str), 0);
 
  str = "aabbdcdbbaa";
  EXPECT_EQ(parser->check_word(str), 0);
 
  str = "aabbccbbaa";
  EXPECT_EQ(parser->check_word(str), 1);
 
  str = "";
  EXPECT_EQ(parser->check_word(str), 1);
}

TEST(ArithmeticExpressions, One) {
  auto parser = new Earley_parser();

  std::vector<Grammar_rule> rules;
  rules.emplace_back('S', "A");
  rules.emplace_back('A', "(A)");
  rules.emplace_back('A', "A*A");
  rules.emplace_back('A', "A+A");
  rules.emplace_back('A', "a");
  rules.emplace_back('A', "1");
  rules.emplace_back('A', "0");


  parser->read_rules(rules);
  std::string str = "1";
  EXPECT_EQ(parser->check_word(str), 1);
  
  str = "a*a*a+1*a+0*(a+a)";
  EXPECT_EQ(parser->check_word(str), 1);

  str = "a*a*a+1*a+0*(aaa+a)";
  EXPECT_EQ(parser->check_word(str), 0);
}