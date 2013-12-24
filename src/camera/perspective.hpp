#pragma once

#include "core/camera.hpp"

class PerspCamera:Camera {
public:
    Float width;
    Float height;
    Float depth;

    PerspCamera(
            const Point &from,
            const Point &to,
            const Point &up,
            Float width_,
            Float height_,
            Float depth_
    );

private:
    void modifyRayDOF(const Sample, Ray *ray)
}
