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
        auto* center = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto* on_circle =
            new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        DeleteLater_(center);
        DeleteLater_(on_circle);
        builder_.buildCircle(center, on_circle);
        SkipTripleCloseParenthesis_();
      } else if (token == "Triangle") {
        auto vertices = std::set<Point, std::function<bool(Point, Point)>>{
            {
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
            },
            [](const Point& p1, const Point& p2) -> bool {
              return p1.info() < p2.info();
            }};
        auto pointers_to_vertex = std::vector<const Point*>{};
        for (auto&& p : vertices) {
          pointers_to_vertex.push_back(new Point{p});
        }
        assert(pointers_to_vertex.size() == 3);
        for (const Point* p : pointers_to_vertex) {
          DeleteLater_(p);
        }
        builder_.buildTriangle(pointers_to_vertex.at(0),
                               pointers_to_vertex.at(1),
                               pointers_to_vertex.at(2));
        SkipTripleCloseParenthesis_();
      } else if (token == "Rectangle") {
        auto vertices = std::set<Point, std::function<bool(Point, Point)>>{
            {
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
                Point{scanner_.nextDouble(), scanner_.nextDouble()},
            },
            [](const Point& p1, const Point& p2) -> bool {
              return p1.info() < p2.info();
            }};
        auto pointers_to_vertex = std::vector<const Point*>{};
        for (auto&& p : vertices) {
          pointers_to_vertex.push_back(new Point{p});
        }
        assert(pointers_to_vertex.size() == 3);
        for (const Point* p : pointers_to_vertex) {
          DeleteLater_(p);
        }
        builder_.buildRectangle(pointers_to_vertex.at(0),
                                pointers_to_vertex.at(1),
                                pointers_to_vertex.at(2));
        SkipTripleCloseParenthesis_();
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

  void SkipTripleCloseParenthesis_() {
    scanner_.next();
    scanner_.next();
    scanner_.next();
  }
};

#endif /* end of include guard: SRC_BUILDER_SHAPE_PARSER_H_ */
