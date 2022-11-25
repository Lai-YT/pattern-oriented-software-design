#ifndef SRC_BUILDER_SCANNER_H_
#define SRC_BUILDER_SCANNER_H_

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
      while (!isDone() && input_.at(pos_) != ' ' && input_.at(pos_) != '\n' &&
             !IsToken_(word)) {
        word += input_.at(pos_++);
      }
    } while (!IsToken_(word) && !isDone());
    SkipWhiteSpace_();
    return IsToken_(word) ? word : "";
  }

  double nextDouble() {
    SkipWhiteSpace_();
    std::string::size_type length = 0;
    double result = std::stod(input_.substr(pos_), &length);
    pos_ += length;
    SkipWhiteSpace_();
    return result;
  }

  bool isDone() const {
    return pos_ >= input_.size();
  }

 private:
  static const std::unordered_set<std::string> TOKENS_;

  std::string input_;
  std::string::size_type pos_ = 0;

  void SkipWhiteSpace_() {
    while (!isDone() && (input_.at(pos_) == ' ' || input_.at(pos_) == '\n')) {
      ++pos_;
    }
  }

  bool IsToken_(const std::string& candidate) const {
    return TOKENS_.find(candidate) != TOKENS_.cend();
  }
};

const std::unordered_set<std::string> Scanner::TOKENS_ = {
    "Circle", "Rectangle", "Triangle", "CompoundShape", "Vector", "(", ")", ",",
};

#endif /* end of include guard: SRC_BUILDER_SCANNER_H_ */
