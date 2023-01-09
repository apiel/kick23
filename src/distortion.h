#ifndef DISTORTION_H_
#define DISTORTION_H_

#define PI 3.1415926535897932384626433832795
#define WAVESHAPE_SIZE 4097

#include "state.h"

int16_t distLerpshift; // 4
int16_t distWaveshape[WAVESHAPE_SIZE];

void setDistortion(float _amount)
{
    distortionAmount = _amount;
    if (distortionAmount > 100.0) {
        distortionAmount = 100.0;
    } else if (distortionAmount < 0.0) {
        distortionAmount = 0.0;
    }
    float deg = PI / 180.0;
    for (u_int16_t i = 0; i < WAVESHAPE_SIZE; i++) {
        float x = (float)i * 2.0 / (float)WAVESHAPE_SIZE - 1.0;
        float waveshape = (3 + distortionAmount) * x * distortionRange * deg / (PI + distortionAmount * abs(x));
        distWaveshape[i] = 32767 * waveshape;
    }
}

void setDistortionRange(float _range)
{
    if (_range < 10.0) {
        _range = 10.0;
    } else if (_range > 120.0) {
        _range = 120.0;
    }

    distortionRange = _range;
    setDistortion(distortionAmount);
}

float distortion(float in)
{
    if (distortionAmount <= 0.0) {
        return in;
    }

    uint16_t x = in * 32768 + 32768;
    uint16_t xa = x >> distLerpshift;
    int16_t ya = distWaveshape[xa];
    int16_t yb = distWaveshape[xa + 1];
    x = ya + ((yb - ya) * (x - (xa << distLerpshift)) >> distLerpshift);

    return x / 32768.0f;
}

void initDistortion()
{
    setDistortion(distortionAmount);

    int index = WAVESHAPE_SIZE - 1;
    distLerpshift = 16;
    while (index >>= 1) {
        --distLerpshift;
    }
}

#endif