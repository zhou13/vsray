#include "shape/polygon.hpp"
#include "core/mesh.hpp"

VSRAY_NAMESPACE_BEGIN

Polygon::Polygon(const vector<Point> &vec, object_pool<Mesh> *pool)
{
    assert(vec.size() > 2);

    for (int i = 1; i < (int)vec.size()-1; ++i)
        addMesh(pool->construct(vec[0], vec[i], vec[i+1]));
}

VSRAY_NAMESPACE_END
