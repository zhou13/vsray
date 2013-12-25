#include "core/film.hpp"
#include "core/filter.hpp"
#include "core/sample.hpp"

#include <opencv2/core/core.hpp>

using namespace cv;

VSRAY_NAMESPACE_BEGIN

Film::Film(int width, int height, Filter *filter) :
    filter(filter), width(width), height(height)
{
    image = new Pixel[width * height];
    filter->getRange(&dx, &dy);
}

Film::~Film()
{
    delete image;
    delete filter;
}

void Film::addSample(const Sample &sample, Spectrum sp)
{
    Float x = width * sample.imageX;
    Float y = height * sample.imageY;

    int i0 = (int)std::max(ceil(y-dy), 0.f);
    int j0 = (int)std::max(ceil(x-dx), 0.f);
    int i1 = (int)std::min(floor(y-dy), (Float)height);
    int j1 = (int)std::min(floor(x-dx), (Float)width);

    for (int i = i0; i <= i1; ++i)
        for (int j = j0; j <= j1; ++j) {
            Float weight = (*filter)(Float(j) - x, Float(i) - y);
            image[i * width + j].color += sp * weight;
            image[i * width + j].weight += weight;
        }
}

void Film::saveToDisk(string filename)
{
    Mat mat(
}

VSRAY_NAMESPACE_END
