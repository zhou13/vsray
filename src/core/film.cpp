#include "core/film.hpp"
#include "core/filter.hpp"
#include "core/sample.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <mutex>

VSRAY_NAMESPACE_BEGIN

Film::Film(int width, int height, Filter *filter) :
    width(width), height(height), filter(filter)
{
    image = new Pixel[width * height];
    dx = dy = filter->size;
}

Film::~Film()
{
    delete[] image;
    delete filter;
}

Float Film::clamp(Float v, Float min, Float max)
{
    if (v > max)
        return max;
    if (v < min)
        return min;
    return v;
}

static std::mutex filmMutex;

void Film::addSample(const Sample &sample, Spectrum sp)
{
    std::unique_lock<std::mutex> lock(filmMutex);

    Float x = (Float)width  * sample.imageX;
    Float y = (Float)height * sample.imageY;

    int i0 = (int)std::max(ceil(y-dy), 0.f);
    int j0 = (int)std::max(ceil(x-dx), 0.f);
    int i1 = (int)std::min(floor(y+dy), (Float)height - 0.5f);
    int j1 = (int)std::min(floor(x+dx), (Float)width - 0.5f);

    for (int i = i0; i <= i1; ++i)
        for (int j = j0; j <= j1; ++j) {
            Float weight = (*filter)(Float(j) - x, Float(i) - y);
            image[i * width + j].color += sp * weight;
            image[i * width + j].weight += weight;
        }
}

void Film::saveToDisk(string filename)
{
    std::unique_lock<std::mutex> lock(filmMutex);

    using namespace cv;

    Mat img(height, width, CV_8UC3, Scalar::all(0));

    uint8_t *m = (uint8_t *)(img.data);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int k = i * width + j;
            Float rgb[3];

            if (image[k].weight == 0.f) {
                rgb[0] = rgb[1] = rgb[2] = 0.f;
            } else {
                (image[k].color / image[k].weight).getRGB(rgb);
            }
            m[i * (int)img.step + j * 3 + 0] = (uint8_t)clamp(rgb[2] * 255, 0, 255);
            m[i * (int)img.step + j * 3 + 1] = (uint8_t)clamp(rgb[1] * 255, 0, 255);
            m[i * (int)img.step + j * 3 + 2] = (uint8_t)clamp(rgb[0] * 255, 0, 255);
        }

    imwrite(filename, img);
}

VSRAY_NAMESPACE_END
