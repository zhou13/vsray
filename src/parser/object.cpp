#include "parser/object.hpp"
#include "core/light.hpp"
#include "shape/mesh.hpp"
#include "shape/meshset.hpp"
#include "primitive/kdtree.hpp"
#include "primitive/material.hpp"
#include "material/stupid.hpp"
#include "shape/polygon.hpp"
#include "texture/constant.hpp"
#include "texture/image.hpp"
#include "texture/stratified3D.hpp"
#include "texture/potted3D.hpp"

#include <boost/filesystem.hpp>

VSRAY_NAMESPACE_BEGIN

const size_t KDTREE_THRESHOLD = 6u;

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
    pathname = filename.substr(0, filename.find_last_of("\\/") + 1);
    std::string err = tinyobj::LoadObj(
            shapes, filename.c_str(), pathname.c_str());
    if (!err.empty()) {
        std::cerr << err << std::endl;
        exit(1);
    }

    lowest = +INFINITY;
    for (size_t i = 0; i < shapes.size(); i++) {
        handleShape(shapes[i]);
    }
}

void ObjectParser::addBottomPanel(real width, real height)
{
    width  /= 2.f;
    height /= 2.f;
    vector<Point> vec = {
        Point(-width, -height, lowest),
        Point(+width, -height, lowest),
        Point(+width, +height, lowest),
        Point(-width, +height, lowest),
    };
    auto matt = new StupidMaterial(make_shared<ConstantTexture<Spectrum>>(1.f));
    material.push_back(matt);
    auto poly = new Polygon(vec, &pool);
    internal.push_back(poly);
    auto prim = new MaterialPrimitive(poly, matt);
    primitives.push_back(prim);
}


void ObjectParser::handleShape(const tinyobj::shape_t &s)
{
    vector<Point> points;
    vector<Normal> normals;
    vector<tuple<real, real>> texMap;

    assert(s.mesh.positions.size() % 3 == 0);
    assert(s.mesh.normals.size() == s.mesh.positions.size() ||
           s.mesh.normals.size() == 0);

    for (size_t v = 0; v < s.mesh.positions.size() / 3; v++) {
        points.push_back(Point(
                        -s.mesh.positions[3*v+0],
                        -s.mesh.positions[3*v+2],
                        +s.mesh.positions[3*v+1]
        ));
        if (s.mesh.positions[3*v+1] < lowest)
            lowest = s.mesh.positions[3*v+1];
        if (s.mesh.normals.size() != 0)
            normals.push_back(Normal(
                            -s.mesh.normals[3*v+0],
                            -s.mesh.normals[3*v+2],
                            +s.mesh.normals[3*v+1]
            ));
        if (s.mesh.texcoords.size() > 0) {
            texMap.push_back(
                    make_tuple(
                            tile(s.mesh.texcoords[2*v+0], 1.f),
                            tile(s.mesh.texcoords[2*v+1], 1.f)
                    )
            );
        }
    }
    assert(s.mesh.indices.size() % 3 == 0);

    Meshset *meshset = new Meshset();
    for (size_t f = 0; f < s.mesh.indices.size() / 3; f++) {
        Mesh *mesh;
        if (points[s.mesh.indices[3*f+0]] == points[s.mesh.indices[3*f+1]] ||
            points[s.mesh.indices[3*f+1]] == points[s.mesh.indices[3*f+2]] ||
            points[s.mesh.indices[3*f+2]] == points[s.mesh.indices[3*f+0]])
            continue;
        if (s.mesh.normals.size() > 0) {
            assert(s.mesh.normals.size() % 3 == 0);
            mesh = pool.construct(
                    make_tuple(points[s.mesh.indices[3*f+0]],
                               points[s.mesh.indices[3*f+1]],
                               points[s.mesh.indices[3*f+2]]),
                    make_tuple(normals[s.mesh.indices[3*f+0]],
                               normals[s.mesh.indices[3*f+1]],
                               normals[s.mesh.indices[3*f+2]]));
        } else {
            // assert(false);
            mesh = pool.construct(
                    make_tuple(points[s.mesh.indices[3*f+0]],
                               points[s.mesh.indices[3*f+1]],
                               points[s.mesh.indices[3*f+2]]));
        }
        if (s.mesh.texcoords.size() > 0) {
            mesh->ua = std::get<0>(texMap[s.mesh.indices[3*f+0]]);
            mesh->va = std::get<1>(texMap[s.mesh.indices[3*f+0]]);
            mesh->ub = std::get<0>(texMap[s.mesh.indices[3*f+1]]);
            mesh->vb = std::get<1>(texMap[s.mesh.indices[3*f+1]]);
            mesh->uc = std::get<0>(texMap[s.mesh.indices[3*f+2]]);
            mesh->vc = std::get<1>(texMap[s.mesh.indices[3*f+2]]);
            mesh->uv = true;
        }

        meshset->addMesh(mesh);
    }

    Primitive *now = meshset;
    internal.push_back(meshset);
    if (meshset->size() > KDTREE_THRESHOLD) {
        puts("initialize KDtree");
        auto kdtree = new KdTree(*meshset);
        kdtree->initialize();
        // kdtree->printTree(0, 0);
        now = kdtree;
    }

    StupidMaterial *stupid;
    Spectrum color = Spectrum(s.material.diffuse);
    if (isZero(s.material.diffuse))
        color = Spectrum(1.f);
    string materialPath = pathname + s.material.diffuse_texname;
    if (s.mesh.texcoords.size() > 0 &&
        !s.material.diffuse_texname.empty() &&
        boost::filesystem::exists(materialPath))
    {
        printf(">>> Loading %s\n", materialPath.c_str());
        fflush(stdout);
        auto texture = make_shared<ImageTexture>(materialPath);
        stupid = new StupidMaterial(texture);
    } else
        stupid = new StupidMaterial(make_shared<ConstantTexture<Spectrum>>(color));
    // stupid = new StupidMaterial(make_shared<ConstantTexture<Spectrum>>(Spectrum(
    //                         255.f / 255.f, 160.f / 255.f, 160.f / 255.f)));
    // stupid = new StupidMaterial(make_shared<Potted3DTexture<Spectrum>>(
    //                 0.4f, 20,
    //                 Spectrum(1.f, .8f, .8f),
    //                 Spectrum(1.f, .65f, .65f)));
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
