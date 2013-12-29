#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Light;
class Primitive;
class Camera;

class Parser {
public:
    virtual void loadFile(string filename) = 0;
    virtual void getLights(vector<Light *> &lights) = 0;
    virtual Primitive *getPrimitives() = 0;
    virtual Camera *getCamera() = 0;
    virtual ~Parser() { }
};

VSRAY_NAMESPACE_END
