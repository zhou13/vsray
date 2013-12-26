#pragma once

#include "core/shape.hpp"

VSRAY_NAMESPACE_BEGIN

class Polygon : public Shape {
public:
    Polygon(const vector<Point> &vec);
};

VSRAY_NAMESPACE_END