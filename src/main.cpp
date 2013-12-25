#include "core/intersection.hpp"
#include "core/film.hpp"
#include "core/matrix.hpp"
#include "core/ray.hpp"
#include "core/sample.hpp"
#include "core/shape.hpp"
#include "core/spectrum.hpp"
#include "core/transform.hpp"
#include "core/vsray.hpp"
#include "camera/orthographic.hpp"
#include "camera/perspective.hpp"
#include "filter/gaussian.hpp"
#include "sampler/stratified.hpp"

#include <iostream>

using namespace vsray;

int main()
{
    puts("hello world");
    Matrix4x4 m(99, 4, 1, 2,
                -1, 0, -1, 2,
                0, 0, 1, 0,
                1, 1, 1, 1);
    printf("%s\n", m.inverse().toString().c_str());
    printf("%3f\n===========\n", m.det());

    Point p(10, 9, 8), p2(0, 0, 10);
    auto tr = Transform::lookAt(Point(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0));
    auto tr2 = Transform::lookAt(Point(5, 0, 0), Vector(-1, 0, 0), Vector(0, 1, 0));
    pdash();

    pobj(tr2);
    pobj(tr2.inverse());
    pobj(tr2.inverse()(Point(0, 0, 0)));
    pobj(tr2.inverse()(p));
    pdash();

    pdash();

    Ray ray(Point(0, 0, 0), Vector(10, 0, 0));
    Ray ray2(Point(0, 0, 0), Vector(-10, 0, 0));
    Mesh mesh(Point(10, 5, 0), Point(10, -5, -5), Point(10, -6, 7));
    Intersection is;
    assert(!mesh.intersect(ray2, &is));
    assert(mesh.intersect(ray, &is));
    printf("[u v t]: %.5f %.5f %.5f\n", is.u, is.v, is.t);
    pobj(mesh.uvToPoint(is.u, is.v));
    pobj(ray(is.t));

    pdash();

    OrthoCamera oca(Point(0, 100, 0), Vector(0, -1, 0), Vector(0, 0, 1), 100, 100);
    StratifiedSampler sampler(800, 600, 0, 800, 0, 600, 0, false);
    Sample samples[200];
    Film film(800, 600, new GaussianFilter());

    int n;
    while (sampler.genSamples(samples, &n))
        for (int i = 0; i < n; ++i) {
            Ray ray;
            oca.genRay(samples[i], &ray);
            film.addSample(samples[i], Spectrum(.5f, .5f, .5f));
        }

    film.saveToDisk("hello.png");
    pdash();

    return 0;
}
