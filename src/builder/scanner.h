#ifndef SRC_BUILDER_SCANNER_H_
#define SRC_BUILDER_SCANNER_H_

#include <cctype>
#include <stdexcept>
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
    SkipWhiteSpace_();

    std::string double_ = "";
    while (!std::isdigit(input_.at(pos_)) && !IsSign_(input_.at(pos_))) {
      ++pos_;
    }
    if (IsSign_(input_.at(pos_))) {
      double_ += input_.at(pos_++);
    }
    if (std::isdigit(input_.at(pos_))) {
      /* a floating-point number has 3 parts:
       * integer part, decimal point and fractional part */
      while (std::isdigit(input_.at(pos_))) {
        double_ += input_.at(pos_++);
      }
      if (input_.at(pos_) == '.') {
        double_ += input_.at(pos_++);
      }
      while (std::isdigit(input_.at(pos_))) {
        double_ += input_.at(pos_++);
      }
    }

    SkipWhiteSpace_();
    return std::stod(double_);
  }

  bool isDone() const {
    return pos_ >= input_.size();
  }

 private:
  static const std::unordered_set<std::string> TOKENS_;

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

#endif /* end of include guard: SRC_BUILDER_SCANNER_H_ */
