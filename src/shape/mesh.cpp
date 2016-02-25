#include "shape/mesh.hpp"
#include "core/ray.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

int Mesh::indexCnt = 0;

Mesh::Mesh(const Point &a, const Point &b, const Point &c) :
    a(a), b(b), c(c), e1(a-c), e2(b-c), nn(false), uv(false)
{
    n = Normal((b - a).cross(c - b).normalize());
    area = getArea();
    index = ++indexCnt;
}

Mesh::Mesh(const Point &a, const Point &b, const Point &c,
           const Normal &na, const Normal &nb, const Normal &nc) :
    a(a), b(b), c(c), na(na),
    nb(nb), nc(nc), e1(a-c), e2(b-c), nn(true), uv(false)
{
    n = Normal((b - a).cross(c - b).normalize());
    area = getArea();
    index = ++indexCnt;
}

Mesh::Mesh(const tuple<const Point &, const Point &, const Point &> &p) :
    Mesh(std::get<0>(p), std::get<1>(p), std::get<2>(p))
{
    // pass
}

Mesh::Mesh(const tuple<const Point &, const Point &, const Point &> &p,
           const tuple<const Normal &, const Normal &, const Normal &> &n) : 
    Mesh(std::get<0>(p), std::get<1>(p), std::get<2>(p),
         std::get<0>(n), std::get<1>(n), std::get<2>(n))
{
}

BBox Mesh::getBBox() const
{
    return BBox(a).merge(BBox(b)).merge(BBox(c));
}

// if is == null, it is the shading ray
bool Mesh::intersect(const Ray &ray, Intersection *is, real epsilon) const
{
    // If we are calculating the shading ray and the current ray comming into a
    // surface, we ignore it
    // if (!is && ray.d.dot(n) > 0)
    //     return false;
    Vector s  = ray.o - c;
    Vector s1 = ray.d.cross(e2);
    Vector s2 = s.cross(e1);

    real deno = s1.dot(e1);
    if (deno == 0)
        return false;
    deno = 1.f / deno;

    const float FLOAT_RELATIVE = 4e-5f;
    real u = s1.dot(s) * deno;
    if (u < -FLOAT_RELATIVE)
        return false;
    real v = s2.dot(ray.d) * deno;
    if (v < -FLOAT_RELATIVE || u + v > 1 + FLOAT_RELATIVE)
        return false;
    real t = s2.dot(e2) * deno;
    if (t < epsilon || t > ray.maxT)
        return false;

    if (is) {
        ray.maxT = t;

        is->u = u;
        is->v = v;
        is->t = t;
        is->epsilon = t * 2e-4f;
        is->ray = &ray;
        is->shape = this;
    }
    return true;
}

void Mesh::fillIntersection(Intersection *is) const
{
    is->p  = uvToPoint(is->u, is->v);
    is->sn = uvToNormal(is->u, is->v);
    is->nn = n;
    if (uv) {
        tuple<real, real> mapUV = uvToUV(is->u, is->v);
        is->mapU = std::get<0>(mapUV);
        is->mapV = std::get<1>(mapUV);
    }
}

Point Mesh::uvToPoint(real u, real v) const
{
    real w = 1.f - u - v;
    return Point(Vector(a) * u + Vector(b) * v + Vector(c) * w);
}

Normal Mesh::uvToNormal(real u, real v) const
{
    if (!nn)
        return n;
    real w = 1.f - u - v;
    return (Normal(na) * u + Normal(nb) * v + Normal(nc) * w).normalize();
}

tuple<real, real> Mesh::uvToUV(real a, real b) const
{
    real c = 1 - a - b;
    return make_tuple(a*ua + b*ub + c*uc, a*va + b*vb + c*vc);
}

real Mesh::getArea() const
{
    real ab = a.distance(b);
    real bc = b.distance(c);
    real ca = c.distance(a);
    real pp = (ab + bc + ca) / 2.f;
    return sqrt(pp * (pp - ab) * (pp - bc) * (pp - ca));
}

string Mesh::toString() const
{
    return a.toString() + " " + b.toString() + " " + c.toString();
}

VSRAY_NAMESPACE_END
