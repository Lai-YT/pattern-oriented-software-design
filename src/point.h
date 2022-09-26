#pragma once

#include <cmath>

class Point
{
private:
    const double _x;
    const double _y;

public:
    Point(double x, double y) {}
    ~Point() {}

    double x() const {}

    double y() const {}

    bool operator==(const Point &pt) const {}

    std::string info() const {}
};
