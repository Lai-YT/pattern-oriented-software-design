#ifndef SRC_BUILDER_SHAPE_PARSER_H_
#define SRC_BUILDER_SHAPE_PARSER_H_

#include <string>
#include <vector>

#include "../circle.h"
#include "../point.h"
#include "../shape.h"
#include "../two_dimensional_vector.h"
#include "./scanner.h"
#include "./shape_builder.h"

class ShapeParser {
 public:
  ShapeParser(const std::string& input) : scanner_{input} {}

  ~ShapeParser() {
    for (auto&& p : points_to_delete_) {
      delete p;
    }
  }

  void parse() {
    while (!scanner_.isDone()) {
      auto token = std::string{scanner_.next()};
      if (token == "Circle") {
        auto* center = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto* on_circle =
            new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        DeleteLater_(center);
        DeleteLater_(on_circle);
        builder_.buildCircle(center, on_circle);
        scanner_.next(); /* ) */
        scanner_.next(); /* ) */
        scanner_.next(); /* ) */
      }
    }
  }

  std::vector<Shape*> getResult() {
    return builder_.getResult();
  }

 private:
  Scanner scanner_;
  ShapeBuilder builder_{};

  /* This is to extend the life time of the points,
   * but they are still deleted with the parser. */
  std::vector<const Point*> points_to_delete_{};

  void DeleteLater_(const Point* const to_delete) {
    points_to_delete_.push_back(to_delete);
  }
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_PARSER_H_ */
