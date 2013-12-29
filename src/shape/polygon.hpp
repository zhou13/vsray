#pragma once

#include "shape/meshset.hpp"

VSRAY_NAMESPACE_BEGIN

class Polygon : public Meshset {
public:
    Polygon(const vector<Point> &vec, object_pool<Mesh> *pool);
};

VSRAY_NAMESPACE_END
