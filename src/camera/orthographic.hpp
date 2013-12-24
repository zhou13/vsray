#pragma once

#include "core/camera.hpp"

class OrthoCamera:Camera {
    Float width;
    Float height;

    OrthoCamera(
            const Point &from,
            const Point &to,
            const Point &up,
            Float width_,
            Float height_
    );
}
