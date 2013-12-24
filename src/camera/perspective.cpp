#pragma once

#include "camera/perspective.hpp"

PerspCamera::PerspCamera(
        const Point &from,
        const Point &to,
        const Point &up, 
        Float width_,
        Float height_
        Float depth_,
        Float lensRadius_ = 0.f,
        Float focalDistance_ = 0.f)
    : Camera(from, to, up, lensRadius_, focalDistance_),
      width(width_), height(height_), depth(depth_)
{
    // pass
}

void PerspCamera::genRay(const Sample &sample, Ray *ray)
{
    Float x = (sample.imageX - 0.5f) * width;
    Float y = (sample.imageY - 0.5f) * height;

    ray->o = o;
    ray->d = Vector(x, y, depth);

    modifyRayDOF(sample, ray);

    ray->o = cameraToWorld(ray->o);
    ray->d = cameraToWorld(ray->d);
}

void PerspCamera::modifyRayDOF(const Sample, Ray *ray)
{
}
