#include "core/mesh.hpp"
#include "core/ray.hpp"
#include "core/intersection.hpp"

#include "core/float.hpp"

VSRAY_NAMESPACE_BEGIN

Mesh::Mesh(const Point &a, const Point &b, const Point &c) :
    a(a), b(b), c(c), nn(false)
{
    n = Normal((b - a).cross(c - b).normalize());
    area = getArea();
}

Mesh::Mesh(const Point &a, const Point &b, const Point &c,
           const Normal &na, const Normal &nb, const Normal &nc) :
    a(a), b(b), c(c), na(na), nb(nb), nc(nc), nn(true)
{
    n = Normal((b - a).cross(c - b).normalize());
    area = getArea();
}

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

    Float u = s1.dot(s) * deno;
    if (!float_ge0(u))
        return false;
    Float v = s2.dot(ray.d) * deno;
    if (!float_ge0(v) || !float_le(u + v, 1))
        return false;
    Float t = s2.dot(e2) * deno;
    if (float_le0(t) || t > ray.maxT)
        return false;

    if (is) {
        ray.maxT = t;

        is->u = u;
        is->v = v;
        is->t = t;
        is->ray = &ray;
        is->mesh = this;
    }
    return true;
}

void Mesh::fillIntersection(Intersection *is)
{
    is->nn = n;
    is->p  = uvToPoint(is->u, is->v);
    is->sn = uvToNormal(is->u, is->v);
}

Point Mesh::uvToPoint(Float u, Float v)
{
    Float w = 1 - u - v;
    return Point(Vector(a) * u + Vector(b) * v + Vector(c) * w);
}

Normal Mesh::uvToNormal(Float u, Float v)
{
    if (!nn)
        return n;
    Float w = 1 - u - v;
    return (Normal(na) * u + Normal(nb) * v + Normal(nc) * w).normalize();
}

Float Mesh::pdf(const Point &obj, Vector *wi, Float u, Float v)
{
    Point p = uvToPoint(u, v);
    *wi = (p - obj).normalize();
    if (n.dot(*wi) <= 0.f)
        return 0.f;

    Float pdf = obj.distance2(p) / (uvToNormal(u, v).dot(*wi) * area);
    return abs(pdf);
}

Float Mesh::getArea()
{
    Float ab = a.distance(b);
    Float bc = b.distance(c);
    Float ca = c.distance(a);
    Float pp = (ab + bc + ca) / 2.f;
    return sqrt(pp * (pp - ab) * (pp - bc) * (pp - ca));
}

VSRAY_NAMESPACE_END
