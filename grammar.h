const size_t alphabet_size = 26;

struct Rule {
  bool is_terminal;
  size_t rule_number;
  friend bool operator<(const Rule& first, const Rule& second) {
    if (first.is_terminal < second.is_terminal)
      return true;
    else if (first.is_terminal == second.is_terminal)
      return first.rule_number < second.rule_number;
    return false;
  }
};

class Grammar {
 public:
  explicit Grammar(const std::vector<std::string> &rules) {
    for (auto &str: rules) {
      std::vector<Rule> rule;
      if (str[5] == '0') {
        std::pair<size_t, std::vector<Rule>> p = {size_t(str[0] - 'A'), rule};
        rules_.insert(p);
        ++number_of_rules;
      }
      for (size_t i = 5; i < str.size(); ++i) {
        if (str[i] >= 'a')
          rule.push_back({true, size_t(str[i] - 'a')});
        else
          rule.push_back({false, size_t(str[i] - 'A')});
      }
      std::pair<size_t, std::vector<Rule>> p = {size_t(str[0] - 'A'), rule};
      rules_.insert(p);
      ++number_of_rules;
    }
    MakeHomskyForm();
  }

  void Print() {
    for (auto &rule: rules_) {
      std::cout << char('A' + rule.first) << " -> ";
      for (auto &symbol: rule.second) {
        if (symbol.is_terminal)
          std::cout << char('a' + symbol.rule_number);
        else
          std::cout << char('A' + symbol.rule_number);
      }
      std::cout << '\n';
    }
  }

  bool CheckWord(const std::string &word) {
    if (word.empty())
      return consist_empty_word;
    std::vector<std::vector<std::vector<bool>>>
        table(number_of_rules, std::vector<std::vector<bool>>(word.size() + 1, std::vector<bool>(word.size() + 1, false)));
    for (size_t i = 0; i < word.size(); ++i) {
      for (auto &rule: rules_) {
        if (rule.second.empty()) {
          table[rule.first][i][0] = true;
        } else if (rule.second[0].is_terminal && word[i] == char(rule.second[0].rule_number + 'a')) {
          table[rule.first][i][1] = true;
        }
      }
    }
    for (size_t length = 2; length <= word.size(); ++length) {
      for (size_t start = 0; start <= word.size() - length; ++start) {
        for (size_t part = 0; part <= length; ++part) {
          for (auto &rule: rules_) {
            if (rule.second.size() == 2) {
              if (table[rule.second[0].rule_number][start][part]
                  && table[rule.second[1].rule_number][start + part][length - part])
                table[rule.first][start][length] = true;
            }
          }
        }
      }
    }
//    for (size_t i = 0; i < table.size(); ++i) {
//      std::cout << char('A' + i) << '\n';
//      for (size_t j = 0; j <= word.size(); ++j) {
//        for (size_t k = 0; k <= word.size(); ++k) {
//          std::cout << table[i][j][k] << ' ';
//        }
//        std::cout << '\n';
//      }
//      std::cout << '\n';
//    }
    return table[0][0][word.size()];
  }

  void MakeHomskyForm() {
    EraseTerminalsFromLongRules();
    DeleteLongRules();
    DeleteEmptyRules();
    DeleteChainRules();
  }

  void EraseTerminalsFromLongRules() {
    for (auto &rule: rules_) {
      if (rule.second.size() > 1) {
        for (auto &symbol: rule.second) {
          if (symbol.is_terminal) {
            std::pair<size_t, std::vector<Rule>> p = {rules_.size(), {symbol}};
            rules_.insert(p);
            symbol.is_terminal = false;
            symbol.rule_number = rules_.size() - 1;
            ++number_of_rules;
          }
        }
      }
    }
  }

  void DeleteLongRules() {
    for (auto &rule: rules_) {
      if (rule.second.size() > 2) {
        size_t sz = rule.second.size() - 2;
        for (size_t i = 0; i < sz; ++i) {
          auto first = rule.second.back();
          rule.second.pop_back();
          auto second = rule.second.back();
          rule.second.pop_back();
          std::pair<size_t, std::vector<Rule>> p = {rules_.size(), {second, first}};
          rule.second.push_back({false, rules_.size()});
          rules_.insert(p);
          ++number_of_rules;
        }
      }
    }
  }

  void DeleteEmptyRules() {
    std::set<size_t> epsilon_rules;
    for (auto &rule: rules_) {
      if (rule.second.empty())
        epsilon_rules.insert(rule.first);
    }
    size_t prev_size = epsilon_rules.size();
    while (true) {
      for (auto &rule: rules_) {
        bool is_epsilon = true;
        for (auto &symbol: rule.second) {
          if (symbol.is_terminal || epsilon_rules.count(symbol.rule_number) == 0) {
            is_epsilon = false;
          }
        }
        if (is_epsilon) {
          epsilon_rules.insert(rule.first);
        }
      }
      if (epsilon_rules.size() == prev_size) {
        break;
      }
    }
    for (auto& rule: rules_) {
      if (rule.second.size() == 2) {
        if (epsilon_rules.count(rule.second[0].rule_number) == 1) {
          rules_.insert(std::pair<size_t, std::vector<Rule>>({rule.first, {rule.second[1]}}));
        }
        if (epsilon_rules.count(rule.second[1].rule_number) == 1) {
          rules_.insert(std::pair<size_t, std::vector<Rule>>({rule.first, {rule.second[0]}}));
        }
      }
    }
    for (auto it = rules_.begin(); it != rules_.end(); ++it) {
      if (it->second.empty()) {
        if (it->first == 0) {
          consist_empty_word = true;
        }
        rules_.erase(it);
      }
    }
  }

  void DeleteChainRules() {
    std::queue<std::pair<size_t , std::vector<Rule>>> chain_rules;
    std::set<std::pair<size_t , std::vector<Rule>>> used_rules;
    for (auto& rule: rules_) {
      if (rule.second.size() == 1 && !rule.second[0].is_terminal)
        chain_rules.push(rule);
    }
    while (!chain_rules.empty()) {
      auto cur = chain_rules.front();
      for (auto& rule: rules_) {
        if (rule.first == cur.second[0].rule_number) {
          std::pair<size_t, std::vector<Rule>> p = {cur.first, rule.second};
          if (used_rules.count(p) == 0) {
            used_rules.insert(p);
            rules_.insert(p);
            if (rule.second.size() == 1 && !rule.second[0].is_terminal)
              chain_rules.push(p);
          }
        }
      }
      chain_rules.pop();
    }
    std::set<std::pair<size_t , std::vector<Rule>>> rules;
    for (auto& rule: rules_) {
      if (rule.second.size() != 1 || rule.second[0].is_terminal)
        rules.insert(rule);
    }
    rules_.clear();
    for (auto& rule: rules)
      rules_.insert(rule);
  }

  bool consist_empty_word = false;
  size_t number_of_rules = 0;
  std::multimap<size_t, std::vector<Rule>> rules_;
};

//
// Created by daniil on 12.01.20.
//

#ifndef UNTITLED36_GRAMMAR_H
#define UNTITLED36_GRAMMAR_H

#endif //UNTITLED36_GRAMMAR_H
