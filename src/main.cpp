#include "camera/orthographic.hpp"
#include "camera/perspective.hpp"
#include "core/film.hpp"
#include "core/intersection.hpp"
#include "core/matrix.hpp"
#include "core/ray.hpp"
#include "core/render.hpp"
#include "core/sample.hpp"
#include "core/scene.hpp"
#include "core/spectrum.hpp"
#include "core/transform.hpp"
#include "core/vsray.hpp"
#include "filter/gaussian.hpp"
#include "filter/triangle.hpp"
#include "integrator/direct.hpp"
#include "light/area.hpp"
#include "light/point.hpp"
#include "material/stupid.hpp"
#include "parser/object.hpp"
#include "primitive/agglomerate.hpp"
#include "primitive/material.hpp"
#include "primitive/kdtree.hpp"
#include "primitive/transform.hpp"
#include "sampler/stratified.hpp"
#include "shape/mesh.hpp"
#include "shape/meshset.hpp"
#include "shape/polygon.hpp"
#include "shape/uvsphere.hpp"

#include <iostream>

using namespace vsray;

int main()
{
    // puts("hello world");
    // Matrix4x4 m(99, 4, 1, 2,
    //             -1, 0, -1, 2,
    //             0, 0, 1, 0,
    //             1, 1, 1, 1);
    // printf("%s\n", m.inverse().toString().c_str());
    // printf("%3f\n===========\n", m.det());

    // Point p(10, 9, 8), p2(0, 0, 10);
    // auto tr = Transform::lookAt(Point(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0));
    // auto tr2 = Transform::lookAt(Point(5, 0, 0), Vector(-1, 0, 0), Vector(0, 1, 0));
    // pdash();

    // pobj(tr2);
    // pobj(tr2.inverse());
    // pobj(tr2.inverse()(Point(0, 0, 0)));
    // pobj(tr2.inverse()(p));
    // pdash();

    // pdash();

    // Ray ray(Point(0, 0, 0), Vector(10, 0, 0));
    // Ray ray2(Point(0, 0, 0), Vector(-10, 0, 0));
    // Mesh mesh(Point(10, 5, 0), Point(10, -5, -5), Point(10, -6, 7));
    // Intersection is;
    // assert(!mesh.intersect(ray2, &is, 0.f));
    // assert(mesh.intersect(ray, &is, 0.f));
    // printf("[u v t]: %.5f %.5f %.5f\n", is.u, is.v, is.t);
    // pobj(mesh.uvToPoint(is.u, is.v));
    // pobj(ray(is.t));

    // pdash();

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

    // PerspCamera oca2(Point(0, 0, 1000), Vector(0, 0, -1), Vector(0, 1, 0), 20, 20, 1000);
    // StratifiedSampler sampler2(800, 800, 1, 1, 0, false);
    // Film film2(800, 800, new TriangleFilter(1), "sphere.png");

    object_pool<Mesh> pool;
    // vector<Point> vec;
    // vec.push_back(Point(-20, -20, 0));
    // vec.push_back(Point(+20, -20, 0));
    // vec.push_back(Point(+20, +20, 0));
    // vec.push_back(Point(-20, +20, 0));

    // Polygon poly(vec, &pool);
    // UVSphere uvsphere(Point(0, 0, 8), 5, 8, 40, true, &pool);

    // StupidMaterial smat;
    // MaterialPrimitive matpt1(&poly, &smat);
    // MaterialPrimitive matpt2(&uvsphere, &smat);

    // Agglomerate agg;
    // agg.addPrimitive(&matpt1);
    // agg.addPrimitive(&matpt2);

    // Scene scene(&agg, &oca2);

    // vector<Point> vec2;
    // vec2.push_back(Point(-1, -1, 20));
    // vec2.push_back(Point(-1, +1, 20));
    // vec2.push_back(Point(+1, +1, 20));
    // vec2.push_back(Point(+1, -1, 20));
    // Polygon poly2(vec2, &pool);

    // AreaLight areaLight(&poly2, Spectrum(50.f));
    // PointLight pointLight(Point(0, 0, 20), 80);

    // scene.addLight(&pointLight);

    // DirectIntegrator di(&scene, false);
    // Render render(&scene, &film2, &sampler2, &di, 100);
    // di.setRender(&render);
    // render.run();

    StratifiedSampler sampler3(1024, 768, 64, 1, 0, true);
    Film film3(1024, 768, new TriangleFilter(1.5f), "bunny-DOF.png");

    ObjectParser objp;
    // objp.loadFile("scene/bunny.obj");
    objp.loadFile("scene/bunny-1000-smooth.obj");
    auto prim = objp.getPrimitives();
    objp.addBottomPanel(8.f, 32.f);

    Agglomerate agg;
    for (int i = -4; i <= 4; ++i)
        if (i != 0) {
            auto tp = new TransformPrimitive(
                    prim, Transform::translate(Vector(0, 3.1f * real(i), 0)));
            agg.addPrimitive(tp);
        }
    agg.addPrimitive(objp.getPrimitives());

    Point man = Point(7, -25.f, 3);
    Transform tr = Transform::rotateZ(0.f);
    PerspCamera oca3(
            Transform::lookAt(
                    tr(man),
                    tr(Vector(-.45f, 1.f, -0.25f).normalize()),
                    Vector(0.f, 0.f, 1)
            ),
            10.f, 7.f, 12.f, 0.2f ,24.f);
    Scene scene2(&agg, &oca3);

    // vector<Point> vec3 = {
    //     Point(-30, -20, +20),
    //     Point(+30, -20, +20),
    //     Point(+30, -20, -15),
    //     Point(-30, -20, -15)
    // };
    // Polygon poly3(vec3, &pool);
    // AreaLight areaLight3(&poly3, 2.0f);
    // scene2.addLight(&areaLight3);
    scene2.addLight(new PointLight(man, 1000));
    scene2.addLight(new PointLight(Point(0, 0, 10), 200));
    scene2.addLight(new PointLight(Point(0, 10, 10), 200));
    scene2.addLight(new PointLight(Point(-10, 0, 10), 200));
    scene2.addLight(new PointLight(Point(0, 5, 10), 100));

    DirectIntegrator di2(&scene2, false);
    Render render2(&scene2, &film3, &sampler3, &di2);
    di2.setRender(&render2);
    // render2.run();

    real minF = 8.f;
    real maxF = 42.f;

    int count = 30*10;
    for (int i = 0; i < count; ++i) {
        char buf[50];
        snprintf(buf, 50, "movie/dof%03d.png", i);
        oca3.setFocalDistance(minF + (maxF-minF) / (real)count * (real)i);
        film3.setFilename(string(buf));
        film3.clear();

        render2.run();
    }

    return 0;
}
