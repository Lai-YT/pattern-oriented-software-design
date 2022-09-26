#pragma once

#include <string>
#include <cmath>
#include "two_dimensional_vector.h"
#include "shape.h"
#include "./iterator/null_iterator.h"

class Circle : public Shape
{
private:
    TwoDimensionalVector *_radiusVec;

public:
    Circle(TwoDimensionalVector *radiusVec) {}
    ~Circle() {}

    double radius() const {}

    double area() const override {}

    Iterator* createDFSIterator() override {}

    Iterator* createBFSIterator() override {}
};