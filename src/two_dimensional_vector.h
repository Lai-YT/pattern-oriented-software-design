#pragma once

#include <cmath>
#include "point.h"

class TwoDimensionalVector
{
private:
    const Point *_a;
    const Point *_b;

public:
    TwoDimensionalVector(const Point *a, const Point *b) {}
    ~TwoDimensionalVector() {}

    const Point *a() const {}

    const Point *b() const {}

    double length() const {}

    double dot(const TwoDimensionalVector *vec) const {}

    double cross(const TwoDimensionalVector *vec) const {}

    std::string info() const {}
};