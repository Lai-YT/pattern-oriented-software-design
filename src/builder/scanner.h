#ifndef SRC_BUILDER_SCANNER_H_
#define SRC_BUILDER_SCANNER_H_

#include <cctype>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_set>

class Scanner {
 public:
  Scanner(const std::string& input) : input_{input} {}

  std::string next() {
    std::string token = NextRegexMatch_(REGEX_FOR_TOKENS_);
    if (token == "") {
      throw ScanIsDoneException{"no more tokens"};
    }
    SkipWhiteSpace_();
    return token;
  }

  double nextDouble() {
    std::string double_ = NextRegexMatch_(REGEX_FOR_FLOATING_POINT_NUMBERS_);
    if (double_ == "") {
      throw ScanIsDoneException{"no more doubles"};
    }
    SkipWhiteSpace_();
    return std::stod(double_);
  }

  bool isDone() const {
    return pos_ >= input_.size();
  }

  class ScanIsDoneException : public std::runtime_error {
    using std::runtime_error::runtime_error;
  };

 private:
  static const std::unordered_set<std::string> TOKENS_;
  static const std::regex REGEX_FOR_TOKENS_;
  static const std::regex REGEX_FOR_FLOATING_POINT_NUMBERS_;

  std::string input_;
  std::string::size_type pos_ = 0;

  std::string NextRegexMatch_(const std::regex& re) {
    if (isDone()) {
      throw ScanIsDoneException{"no more content to scan through"};
    }

    auto match = std::smatch{};
    std::regex_search(input_.cbegin() + pos_, input_.cend(), match, re);
    pos_ += match.position() + match.length();
    return match.str();
  }

  void SkipWhiteSpace_() {
    while (!isDone() && IsWhiteSpace_(input_.at(pos_))) {
      ++pos_;
    }
  }

  bool IsWhiteSpace_(const char c) const {
    return c == ' ' || c == '\n';
  }
};

const std::unordered_set<std::string> Scanner::TOKENS_ = {
    "Circle", "Rectangle", "Triangle", "CompoundShape", "Vector", "(", ")", ",",
};

const std::regex Scanner::REGEX_FOR_TOKENS_{
    R"(\b(Circle|Rectangle|Triangle|CompoundShape|Vector)\b|[(),])"};

const std::regex Scanner::REGEX_FOR_FLOATING_POINT_NUMBERS_{
    R"([-+]?(?:\d+(?:\.\d*)?|\.\d+))"};

#endif /* end of include guard: SRC_BUILDER_SCANNER_H_ */
