#include "parser/object.hpp"
#include "core/light.hpp"
#include "shape/mesh.hpp"
#include "shape/meshset.hpp"
#include "primitive/kdtree.hpp"
#include "primitive/material.hpp"
#include "material/stupid.hpp"

VSRAY_NAMESPACE_BEGIN

const size_t KDTREE_THRESHOLD = 6;

ObjectParser::~ObjectParser()
{
    for (auto p: internal)
        delete p;
    for (auto p: primitives)
        delete p;
    for (auto p: lights)
        delete p;
    for (auto p: material)
        delete p;
}

void ObjectParser::loadFile(string filename)
{
    std::string err = tinyobj::LoadObj(shapes, filename.c_str());
    if (!err.empty()) {
        std::cerr << err << std::endl;
        exit(1);
    }

    for (size_t i = 0; i < shapes.size(); i++) {
        handleShape(shapes[i]);
    }
}

void ObjectParser::handleShape(const tinyobj::shape_t &s)
{
    vector<Point> points;
    vector<Normal> normals;

    assert(s.mesh.positions.size() % 3 == 0);
    assert(s.mesh.normals.size() == s.mesh.positions.size() ||
           s.mesh.normals.size() == 0);

    for (size_t v = 0; v < s.mesh.positions.size() / 3; v++) {
        points.push_back(Point(s.mesh.positions[3*v+0],
                               s.mesh.positions[3*v+1],
                               s.mesh.positions[3*v+2]));
        if (s.mesh.normals.size() != 0)
            normals.push_back(Normal(s.mesh.normals[3*v+0],
                                     s.mesh.normals[3*v+1],
                                     s.mesh.normals[3*v+2]));
    }
    assert(s.mesh.indices.size() % 3 == 0);

    Meshset *meshset = new Meshset();
    for (size_t f = 0; f < s.mesh.indices.size() / 3; f++) {
        Mesh *mesh;
        if (s.mesh.normals.size() != 0) {
            mesh = pool.construct(
                    make_tuple(points[s.mesh.indices[3*f+0]],
                               points[s.mesh.indices[3*f+1]],
                               points[s.mesh.indices[3*f+2]]),
                    make_tuple(normals[s.mesh.indices[3*f+0]],
                               normals[s.mesh.indices[3*f+1]],
                               normals[s.mesh.indices[3*f+2]]));
        } else {
            mesh = pool.construct(
                    make_tuple(points[s.mesh.indices[3*f+0]],
                               points[s.mesh.indices[3*f+1]],
                               points[s.mesh.indices[3*f+2]]));
        }
        meshset->addMesh(mesh);
    }

    Primitive *now = meshset;
    internal.push_back(meshset);
    if (meshset->size() > KDTREE_THRESHOLD) {
        auto kdtree = new KdTree(meshset);
        kdtree->initialize();
        now = kdtree;
    }

    StupidMaterial *stupid;
    if (!isZero(s.material.diffuse))
        stupid = new StupidMaterial(Spectrum(s.material.diffuse));
    else
        stupid = new StupidMaterial(Spectrum(1.f));
    material.push_back(stupid);

    now = new MaterialPrimitive(now, stupid);
    primitives.push_back(now);
}

void ObjectParser::getLights(vector<Light *> &lights_)
{
    for (auto light: lights)
        lights_.push_back(light);
}

Primitive *ObjectParser::getPrimitives()
{
    Agglomerate *agg = new Agglomerate();
    for (auto primitive: primitives) {
        agg->addPrimitive(primitive);
    }
    return agg;
}

bool ObjectParser::isZero(const float *f)
{
    return f[0] == 0.f && f[1] == 0.f && f[2] == 0.f;
}

Camera *ObjectParser::getCamera()
{
    return nullptr;
    // do nothing
}

VSRAY_NAMESPACE_END
