#pragma once

#include <string>
#include "shape.h"
#include "two_dimensional_vector.h"
#include "./iterator/null_iterator.h"

class Triangle : public Shape
{
private:
    TwoDimensionalVector *_v1;
    TwoDimensionalVector *_v2;

public:
    Triangle(TwoDimensionalVector *v1, TwoDimensionalVector *v2) {}
    ~Triangle() {}

    double area() const override {}

    Iterator* createDFSIterator() override {}

    Iterator* createBFSIterator() override {}
};