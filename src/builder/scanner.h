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
    auto word = std::string{};
    SkipWhiteSpace_();
    do {
      word.clear();
      char c = input_.at(pos_);
      if (IsToken_(std::string{c})) {
        word = c;
        ++pos_;
        break;
      }
      while (!isDone() && !IsWhiteSpace_(c) && !IsToken_(std::string{c}) &&
             !IsToken_(word)) {
        word += input_.at(pos_);
        c = input_.at(++pos_);
        std::cout << word + '\n';
      }
    } while (!IsToken_(word) && !isDone());
    SkipWhiteSpace_();
    return IsToken_(word) ? word : "";
  }

  double nextDouble() {
    SkipWhiteSpace_();
    std::string double_ = "";
    while (!std::isdigit(input_.at(pos_)) && input_.at(pos_) != '+' &&
           input_.at(pos_) != '-') {
      ++pos_;
    }
    if (input_.at(pos_) == '+' || input_.at(pos_) == '-') {
      double_ += input_.at(pos_++);
    }
    std::cout << double_ + '\n';
    if (std::isdigit(input_.at(pos_))) {
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
    std::cout << double_ + '\n';
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

  bool IsToken_(const std::string& candidate) const {
    return TOKENS_.find(candidate) != TOKENS_.cend();
  }
};

const std::unordered_set<std::string> Scanner::TOKENS_ = {
    "Circle", "Rectangle", "Triangle", "CompoundShape", "Vector", "(", ")", ",",
};

#endif /* end of include guard: SRC_BUILDER_SCANNER_H_ */
