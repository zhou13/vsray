#include "shape/polygon.hpp"

VSRAY_NAMESPACE_BEGIN

Polygon::Polygon(const vector<Point> &vec)
{
    assert(vec.size() > 2);

    for (int i = 1; i < (int)vec.size()-1; ++i)
        meshes.push_back(pool.construct(vec[0], vec[i+1], vec[i]));
}

VSRAY_NAMESPACE_END
