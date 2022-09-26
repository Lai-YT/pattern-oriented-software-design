#pragma once

#include "shape.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/bfs_compound_iterator.h"

#include <list>

class CompoundShape : public Shape
{
private:
    std::list<Shape*> _shapes;
public:
    ~CompoundShape() {}

    double area() const override {}

    double perimeter() const override {}

    std::string info() const override {}

    Iterator* createDFSIterator() override {}

    Iterator* createBFSIterator() override {}

    void addShape(Shape* shape) override {}

    void deleteShape(Shape* shape) override {}
};