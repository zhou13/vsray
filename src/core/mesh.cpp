#include "core/mesh.hpp"
#include "core/ray.hpp"
#include "core/intersection.hpp"

#include "core/float.hpp"

VSRAY_NAMESPACE_BEGIN

BBox Mesh::getBBox()
{
    return BBox(a).merge(BBox(b)).merge(BBox(c));
}

bool Mesh::intersect(const Ray &ray, Intersection *is)
{
    Vector e1 = a - c;
    Vector e2 = b - c;
    Vector s  = ray.o - c;
    Vector s1 = ray.d.cross(e2);
    Vector s2 = s.cross(e1);

    Float deno = s1.dot(e1);
    if (deno == 0)
        return false;
    deno = 1.f / deno;

    Float uu = s1.dot(s) * deno;
    if (!float_ge0(uu))
        return false;
    Float vv = s2.dot(ray.d) * deno;
    if (!float_ge0(vv) || !float_le(uu + vv, 1))
        return false;
    Float tt = s2.dot(e2) * deno;
    if (float_le0(tt))
        return false;

    if (is) {
        is->u = uu;
        is->v = vv;
        is->t = tt;
        is->ray = &ray;
        is->mesh = this;
    }
    return true;
}

Point Mesh::uvToPoint(Float u, Float v)
{
    Float w = 1 - u - v;
    return Point(Vector(a) * u + Vector(b) * v + Vector(c) * w);
}

VSRAY_NAMESPACE_END
