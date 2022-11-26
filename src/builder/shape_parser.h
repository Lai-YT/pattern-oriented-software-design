#ifndef SRC_BUILDER_SHAPE_PARSER_H_
#define SRC_BUILDER_SHAPE_PARSER_H_

#include <cassert>
#include <functional>
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

  ~ShapeParser() {
    for (auto&& p : points_to_delete_) {
      delete p;
    }
  }

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

  /* This is to extend the life time of the points,
   * but they are still deleted with the parser. */
  std::vector<const Point*> points_to_delete_{};

  void ParseCircle_() {
    auto* center = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
    auto* on_circle = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
    DeleteLater_(center);
    DeleteLater_(on_circle);
    builder_.buildCircle(center, on_circle);
    SkipTripleCloseParenthesis_();
  }

  void ParseTriangle_() {
    std::array<const Point*, 3> vertices =
        ExtractThreeUnDuplicatedVerticesFromNextFourPoints_();
    builder_.buildTriangle(vertices.at(0), vertices.at(1), vertices.at(2));
    SkipTripleCloseParenthesis_();
  }

  void ParseRectangle_() {
    std::array<const Point*, 3> vertices =
        ExtractThreeUnDuplicatedVerticesFromNextFourPoints_();
    builder_.buildRectangle(vertices.at(0), vertices.at(1), vertices.at(2));
    SkipTripleCloseParenthesis_();
  }

  /* The 3 un-duplicated vertices will be deleted later. */
  std::array<const Point*, 3>
  ExtractThreeUnDuplicatedVerticesFromNextFourPoints_() {
    auto points_info_less_than = [](const Point& p1, const Point& p2) -> bool {
      return p1.info() < p2.info();
    };
    /* Since two of them are common points, put them into a set to eliminate the
     * common point. */
    auto vertices = std::set<Point, decltype(points_info_less_than)>{
        {
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
        },
        points_info_less_than};
    assert(vertices.size() == 3);

    /* Allocate them on the heap so can extend their life-time. */
    auto pointers_of_vertices = std::array<const Point*, 3>{};
    int i = 0;
    for (auto&& p : vertices) {
      pointers_of_vertices.at(i) = new Point{p};
      ++i;
    }
    for (const Point* p : pointers_of_vertices) {
      DeleteLater_(p);
    }
    return pointers_of_vertices;
  }

  void DeleteLater_(const Point* const to_delete) {
    points_to_delete_.push_back(to_delete);
  }

  void SkipTripleCloseParenthesis_() {
    scanner_.next();
    scanner_.next();
    scanner_.next();
  }
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_PARSER_H_ */
