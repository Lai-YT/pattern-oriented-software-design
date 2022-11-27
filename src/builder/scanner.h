#ifndef SRC_BUILDER_SCANNER_H_
#define SRC_BUILDER_SCANNER_H_

#include <cctype>
#include <regex>
#include <string>
#include <unordered_set>

class Scanner {
 public:
  Scanner(const std::string& input) : input_{input} {}

  std::string next() {
    SkipWhiteSpace_();

    auto word = std::string{};
    do {
      word.clear();
      char c = input_.at(pos_);
      /* single-character token */
      if (IsToken_(c)) {
        word = c;
        ++pos_;
        break;
      }
      /* normal-string token */
      while (!isDone() && !IsWhiteSpace_(input_.at(pos_)) &&
             !IsToken_(input_.at(pos_)) && !IsToken_(word)) {
        word += input_.at(pos_);
        ++pos_;
      }
    } while (!IsToken_(word) && !isDone());

    SkipWhiteSpace_();
    return IsToken_(word) ? word : "";
  }

  double nextDouble() {
    auto match = std::smatch{};
    std::regex_search(input_.cbegin() + pos_, input_.cend(), match,
                      REGEX_FOR_FLOATING_POINT_NUMBERS_);
    pos_ += match.position() + match.length();
    SkipWhiteSpace_();
    return std::stod(match.str());
  }

  bool isDone() const {
    return pos_ >= input_.size();
  }

 private:
  static const std::unordered_set<std::string> TOKENS_;
  static const std::regex REGEX_FOR_FLOATING_POINT_NUMBERS_;

  std::string input_;
  std::string::size_type pos_ = 0;

  void SkipWhiteSpace_() {
    while (!isDone() && IsWhiteSpace_(input_.at(pos_))) {
      ++pos_;
    }
  }

  bool IsWhiteSpace_(const char c) const {
    return c == ' ' || c == '\n';
  }

  bool IsSign_(const char c) const {
    return c == '+' || c == '-';
  }

  bool IsToken_(const std::string& candidate) const {
    return TOKENS_.find(candidate) != TOKENS_.cend();
  }

  bool IsToken_(const char c) const {
    return IsToken_(std::string{c});
  }
};

const std::unordered_set<std::string> Scanner::TOKENS_ = {
    "Circle", "Rectangle", "Triangle", "CompoundShape", "Vector", "(", ")", ",",
};

const std::regex Scanner::REGEX_FOR_FLOATING_POINT_NUMBERS_{
    R"([-+]?(?:\d+(?:\.\d*)?|\.\d+))"};

#endif /* end of include guard: SRC_BUILDER_SCANNER_H_ */
