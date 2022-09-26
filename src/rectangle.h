#pragma once

#include <string>
#include "shape.h"
#include "two_dimensional_vector.h"
#include "./iterator/null_iterator.h"

class Rectangle : public Shape
{
private:
    TwoDimensionalVector *_lengthVec;
    TwoDimensionalVector *_widthVec;

public:
    Rectangle(TwoDimensionalVector *lengthVec, TwoDimensionalVector *widthVec) {}
    ~Rectangle() {}

    double length() const {}

    double width() const {}

    double area() const override {}

    Iterator* createDFSIterator() override {}

    Iterator* createBFSIterator() override {}
};