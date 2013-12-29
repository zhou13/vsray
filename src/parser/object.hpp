#include "core/parser.hpp"
#include "core/geometry.hpp"
#include "parser/tinyobjloader/tiny_obj_loader.hpp"
#include "shape/mesh.hpp"

VSRAY_NAMESPACE_BEGIN

class Light;
class Primitive;
class Material;

class ObjectParser : public Parser {
public:
    virtual void loadFile(string filename);
    virtual void getLights(vector<Light *> &lights);
    virtual Primitive *getPrimitives();
    virtual Camera *getCamera();
    virtual ~ObjectParser();

private:
    vector<tinyobj::shape_t> shapes;

    vector<Primitive *> primitives;
    vector<Light *> lights;
    vector<Material *> material;
    vector<Primitive *> internal;

    object_pool<Mesh> pool;

    void handleShape(const tinyobj::shape_t &s);
    bool isZero(const float *f);
};

VSRAY_NAMESPACE_END
