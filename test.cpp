#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include "gtest/gtest.h"
#include "grammar.h"



TEST (TestGroup1, Test1) {
  std::vector<std::string> s = {"A -> Ab", "A -> a"};
   Grammar grammar(s);
   ASSERT_EQ(grammar.CheckWord("a"), true);
}

TEST (TestGroup1, Test2) {
  std::vector<std::string> s = {"A -> Ab", "A -> a"};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("abbbb"), true);
}

TEST (TestGroup1, Test3) {
  std::vector<std::string> s = {"A -> Ab", "A -> a"};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("aaaaab"), false);
}

TEST (TestGroup1, Test4) {
  std::vector<std::string> s = {"A -> Ab", "A -> a"};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("def"), false);
}

TEST (TestGroup1, Test5) {
  std::vector<std::string> s = {"A -> Ab", "A -> a"};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord(""), false);
}

TEST (TestGroup1, Test6) {
  std::vector<std::string> s = {"A -> aAb", "A -> c", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("aaaacbbbb"), true);
}

TEST (TestGroup1, Test7) {
  std::vector<std::string> s = {"A -> aAb", "A -> c", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("aaabbb"), true);
}

TEST (TestGroup1, Test8) {
  std::vector<std::string> s = {"A -> aAb", "A -> c", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("aaabbbb"), false);
}

TEST (TestGroup1, Test9) {
  std::vector<std::string> s = {"A -> aAb", "A -> c", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord(""), true);
}

TEST (TestGroup1, Test10) {
  std::vector<std::string> s = {"A -> aAbA", "A -> bAaA", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("baaababb"), true);
}

TEST (TestGroup1, Test11) {
  std::vector<std::string> s = {"A -> aAbA", "A -> bAaA", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("aaaabbb"), false);
}

TEST (TestGroup1, Test12) {
  std::vector<std::string> s = {"A -> aAbA", "A -> bAaA", "A -> "};
  Grammar grammar(s);
  ASSERT_EQ(grammar.CheckWord("cab"), false);
}

TEST(TestGroup2, Test1) {
  std::vector<std::string> s = {"A -> aAbA", "A -> bAaA", "A -> "};
  Grammar grammar(s);
  for (auto& rule: grammar.rules_) {
    ASSERT_EQ(bool(rule.second.size()), true);
  }
  ASSERT_EQ(grammar.consist_empty_word, true);
}

TEST(TestGroup2, Test2) {
  std::vector<std::string> s = {"A -> ABCD", "B -> ", "C -> ", "D -> e"};
  Grammar grammar(s);
  for (auto& rule: grammar.rules_) {
    ASSERT_EQ(rule.second.size() > 0, true);
  }
}

TEST(TestGroup2, Test3) {
  std::vector<std::string> s = {"A -> ABCD", "B -> ", "C -> ", "D -> e"};
  Grammar grammar(s);
  for (auto& rule: grammar.rules_) {
    ASSERT_EQ(rule.second.size() < 3, true);
  }
}

TEST(TestGroup2, Test4) {
  std::vector<std::string> s = {"A -> ABCDEF", "B -> EFGH", "C -> adadaf", "D -> esdfsagas"};
  Grammar grammar(s);
  for (auto& rule: grammar.rules_) {
    ASSERT_EQ(rule.second.size() < 3, true);
  }
}

TEST(TestGroup2, Test5) {
  std::vector<std::string> s = {"A -> AaeBCe", "B -> Efdsf", "C -> a", "D -> es"};
  Grammar grammar(s);
  for (auto& rule: grammar.rules_) {
    ASSERT_EQ(rule.second.size() != 1 || rule.second[0].is_terminal, true);
  }
}

TEST(TestGroup2, Test6) {
  std::vector<std::string> s = {"A -> AaeBCe", "B -> C", "C -> B", "D -> E", "E -> F", "F -> s"};
  Grammar grammar(s);
  for (auto& rule: grammar.rules_) {
    ASSERT_EQ(rule.second.size() != 1 || rule.second[0].is_terminal, true);
  }
}