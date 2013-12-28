#include "camera/orthographic.hpp"
#include "camera/perspective.hpp"
#include "core/film.hpp"
#include "core/intersection.hpp"
#include "core/matrix.hpp"
#include "core/ray.hpp"
#include "core/render.hpp"
#include "core/sample.hpp"
#include "core/scene.hpp"
#include "core/shape.hpp"
#include "core/spectrum.hpp"
#include "core/transform.hpp"
#include "core/vsray.hpp"
#include "filter/gaussian.hpp"
#include "integrator/direct.hpp"
#include "light/area.hpp"
#include "material/stupid.hpp"
#include "primitive/adapter.hpp"
#include "primitive/material.hpp"
#include "sampler/stratified.hpp"
#include "shape/polygon.hpp"

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

    // OrthoCamera oca(Point(0, 100, 0), Vector(0, -1, 0), Vector(0, 0, 1), 100, 100);
    // StratifiedSampler sampler(800, 600, 1, 0, 0, false);
    // sampler.initialize(0, 800, 0, 600);
    // Sample samples[200];
    // Film film(800, 600, new GaussianFilter());

    // int n;
    // for (;;) {
    //     bool b = sampler.genSamples(samples, &n);
    //     for (int i = 0; i < n; ++i) {
    //         Ray ray;
    //         // pobj(samples[i]);
    //         oca.genRay(samples[i], &ray);
    //         film.addSample(samples[i], Spectrum(.1f, .1f, .1f));
    //     }
    //     if (!b)
    //         break;
    // }

    // fflush(stdout);
    // film.saveToDisk("hello.png");

    // pdash();
    // pdash();

    OrthoCamera oca2(Point(0, 0, 10), Vector(0, 0, -1), Vector(0, 1, 0), 15, 15);
    StratifiedSampler sampler2(800, 800, 1, 4, 0, false);
    Film film2(800, 800, new GaussianFilter(1));

    object_pool<Mesh> pool;
    vector<Point> vec;
    vec.push_back(Point(-10, -10, 0));
    vec.push_back(Point(+10, -10, 0));
    vec.push_back(Point(+10, +10, 0));
    vec.push_back(Point(-10, +10, 0));

    Polygon poly(vec, &pool);
    AdapterPrimitive adpt(&poly);
    StupidMaterial smat;
    MaterialPrimitive matpt(&adpt, &smat);
    Scene scene(&matpt, &oca2);

    vector<Point> vec2;
    vec2.push_back(Point(-10, -10, 10));
    vec2.push_back(Point(-10, +10, 10));
    vec2.push_back(Point(+10, +10, 10));
    vec2.push_back(Point(+10, -10, 10));
    Polygon poly2(vec2, &pool);

    AreaLight areaLight(&poly2, Spectrum(100.f));

    scene.addLight(&areaLight);

    DirectIntegrator di(&scene, false);
    Render render(&scene, &film2, &sampler2, &di);
    di.setRender(&render);
    render.run();
    film2.saveToDisk("whitepaper.png");

    pdash();
    pdash();

    return 0;
}
