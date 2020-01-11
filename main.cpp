#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include "googletest/googletest/include/gtest/gtest.h"
#include "grammar.h"



int main() {
//  int n;
//  std::cin >> n;
//  std::vector<std::string> rules;
//  for (int i = 0; i < n; ++i) {
//    std::string s1, s2, s3;
//    std::cin >> s1 >> s2 >> s3;
//    rules.push_back(s1 + ' ' + s2 + ' ' + s3);
//  }
//  Grammar grammar(rules);
//  grammar.Print();
//  std::string word;
//  std::cin >> word;
//  if (grammar.CheckWord(word)) {
//    std::cout << "YES";
//  } else {
//    std::cout << "NO";
//  }
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}