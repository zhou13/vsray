#include "sampler/stratified.hpp"
#include "core/random.hpp"
#include "core/sample.hpp"

VSRAY_NAMESPACE_BEGIN

const int MAX_SAMPLES = 100;

Float StratifiedSampler::offset()
{
    if (stratified)
        return nextRandomFloat();
    return 0;
}

void StratifiedSampler::genStratified1D(Float *f, int n)
{
    Float gap = 1.f / (Float)n;
    for (int i = 0; i < n; ++i)
        f[i] = ((Float)i + offset()) * gap;
    for (int i = 0; i < n; ++i)
        std::swap(f[i], f[nextRandomInt(n)]);
}

StratifiedSampler::StratifiedSampler(
        int imageWidth, int imageHeight,
        int x0, int x1, int y0, int y1, // x0 <= x < x1
        int samplesPerPixel, int nLight, bool stratified) :
    imageWidth(width), imageHeight(height),
    x0(x0), x1(x1), y0(y0), y1(y1), width(x1-x0), height(y1-y0),
    samplesPerPixel(samplesPerPixel), nLight(nLight), stratified(stratified)
{
    numSamplesLeft = numSamples = width * height * samplesPerPixel;
    imageX = new Float[numSamples];
    imageY = new Float[numSamples];
    lensU  = new Float[numSamples];
    lensV  = new Float[numSamples];

    int i = 0;
    for (int x = x0; x < x1; ++x)
        for (int y = y0; y < y1; ++y)
            for (int z = 0; z < samplesPerPixel; ++z) {
                imageX[i] = 1.f / (Float)imageWidth  * ((Float)x + offset());
                imageY[i] = 1.f / (Float)imageHeight * ((Float)y + offset());
                ++i;
            }

    int n = (int)sqrt(width * height);
    for (int x = 0; x < n; ++x)
        for (int y = 0; y < n; ++y)
            for (int z = 0; z < samplesPerPixel; ++z) {
                --i;
                lensU[i]  = 1.f / (Float)n * ((Float)x + offset());
                lensV[i]  = 1.f / (Float)n * ((Float)y + offset());
            }
    while (i > 0) {
        --i;
        lensU[i] = nextRandomFloat();
        lensV[i] = nextRandomFloat();
    }

    for (i = 0; i < numSamples; ++i) {
        int j = nextRandomInt(0, numSamples);
        std::swap(lensU[i], lensU[j]);
        std::swap(lensV[i], lensV[j]);
    }
}

StratifiedSampler::~StratifiedSampler()
{
    delete[] imageX;
    delete[] imageY;
    delete[] lensU;
    delete[] lensV;
}

bool StratifiedSampler::genSamples(Sample *samples, int *n)
{
    *n = 0;
    while (numSamplesLeft > 0 && *n < MAX_SAMPLES) {
        int i = --numSamplesLeft;

        samples[*n].imageX = imageX[i];
        samples[*n].imageY = imageY[i];
        samples[*n].lensU = lensU[i];
        samples[*n].lensV = lensV[i];

        samples[*n].nLight = nLight;
        genStratified1D(samples[*n].lightU, nLight);
        genStratified1D(samples[*n].lightV, nLight);
        genStratified1D(samples[*n].bxdfU, nLight);
        genStratified1D(samples[*n].bxdfV, nLight);
        genStratified1D(samples[*n].bxdfI, nLight);

        *n += 1;
    }

    return numSamplesLeft > 0;
}

int StratifiedSampler::getSamplesCount()
{
    return std::min(MAX_SAMPLES, numSamples * samplesPerPixel);
}

int StratifiedSampler::roundSize(int size)
{
    return size;
}

VSRAY_NAMESPACE_END
