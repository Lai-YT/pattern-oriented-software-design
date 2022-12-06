#ifndef SRC_BUILDER_SHAPE_PARSER_H_
#define SRC_BUILDER_SHAPE_PARSER_H_

#include <cassert>
#include <set>
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

  void parse() {
    while (!scanner_.isDone()) {
      auto token = std::string{scanner_.next()};
      if (token == "Circle") {
        ParseCircle_();
      } else if (token == "Triangle") {
        ParseTriangle_();
      } else if (token == "Rectangle") {
        ParseRectangle_();
      } else if (token == "CompoundShape") {
        builder_.buildCompoundShape();
        scanner_.next(); /* skip open parenthesis */
      } else if (token == ")") {
        builder_.buildCompoundEnd();
      }
    }
  }

  std::vector<Shape*> getResult() {
    return builder_.getResult();
  }

 private:
  Scanner scanner_;
  ShapeBuilder builder_{};

  void ParseCircle_() {
    auto center = Point{scanner_.nextDouble(), scanner_.nextDouble()};
    auto on_circle = Point{scanner_.nextDouble(), scanner_.nextDouble()};
    builder_.buildCircle(center, on_circle);
    SkipTripleCloseParenthesis_();
  }

  void ParseTriangle_() {
    std::array<Point, 3> vertices =
        ExtractThreeUnDuplicatedVerticesFromNextFourPoints_();
    builder_.buildTriangle(vertices.at(0), vertices.at(1), vertices.at(2));
    SkipTripleCloseParenthesis_();
  }

  void ParseRectangle_() {
    std::array<Point, 3> vertices =
        ExtractThreeUnDuplicatedVerticesFromNextFourPoints_();
    builder_.buildRectangle(vertices.at(0), vertices.at(1), vertices.at(2));
    SkipTripleCloseParenthesis_();
  }

  std::array<Point, 3> ExtractThreeUnDuplicatedVerticesFromNextFourPoints_() {
    /* Since two of them are common points, put them into a set to eliminate the
     * common point. */
    auto vertices = std::set<Point>{{
        {scanner_.nextDouble(), scanner_.nextDouble()},
        {scanner_.nextDouble(), scanner_.nextDouble()},
        {scanner_.nextDouble(), scanner_.nextDouble()},
        {scanner_.nextDouble(), scanner_.nextDouble()},
    }};
    assert(vertices.size() == 3);

    auto DUMMY_POINT = Point{0, 0}; /* Point has no default ctor */
    auto pointers_of_vertices =
        std::array<Point, 3>{DUMMY_POINT, DUMMY_POINT, DUMMY_POINT};
    int i = 0;
    for (auto&& p : vertices) {
      pointers_of_vertices.at(i) = Point{p};
      ++i;
    }
    return pointers_of_vertices;
  }

  void SkipTripleCloseParenthesis_() {
    scanner_.next();
    scanner_.next();
    scanner_.next();
  }
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_PARSER_H_ */
