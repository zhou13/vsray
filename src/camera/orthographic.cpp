#pragma once

#include "camera/orthographic.hpp"

OrthoCamera::OrthoCamera(
        const Point &from,
        const Point &to,
        const Point &up, 
        Float width_,
        Float height_,
        Float lensRadius_ = 0.f,
        Float focalDistance_ = 0.f)
    : Camera(from, to, up, lensRadius_, focalDistance_),
      width(width_), height(height_)
{
    // pass
}

void OrthoCamera::genRay(const Sample &sample, Ray *ray)
{
    Float x = (sample.imageX - 0.5f) * width;
    Float y = (sample.imageY - 0.5f) * height;
    ray->o = cameraToWorld(o + Vector(x * width, y * height, 0));
    ray->d = cameraToWorld(Vector(0, 0, 1));
}
