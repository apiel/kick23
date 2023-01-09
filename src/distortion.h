#ifndef DISTORTION_H_
#define DISTORTION_H_

#define PI 3.1415926535897932384626433832795
#define WAVESHAPE_SIZE 4097

float amount = 0.0;
float range = 20.0;
int16_t lerpshift; // 4
int16_t distWaveshape[WAVESHAPE_SIZE];

void setDistortion(float _amount)
{
    amount = _amount;
    if (amount > 100.0) {
        amount = 100.0;
    }
    if (amount > 0.0) {
        float deg = PI / 180.0;
        for (u_int16_t i = 0; i < WAVESHAPE_SIZE; i++) {
            float x = (float)i * 2.0 / (float)WAVESHAPE_SIZE - 1.0;
            float waveshape = (3 + amount) * x * range * deg / (PI + amount * abs(x));
            distWaveshape[i] = 32767 * waveshape;
        }
    }
}

void setRange(float _range)
{
    range = _range;
    setDistortion(amount);
}

float distortion(float in)
{
    if (amount <= 0) {
        return in;
    }

    uint16_t x = in * 32768 + 32768;
    uint16_t xa = x >> lerpshift;
    int16_t ya = distWaveshape[xa];
    int16_t yb = distWaveshape[xa + 1];
    x = ya + ((yb - ya) * (x - (xa << lerpshift)) >> lerpshift);

    return x / 32768.0f;
}

void initDistortion()
{
    setDistortion(amount);

    int index = WAVESHAPE_SIZE - 1;
    lerpshift = 16;
    while (index >>= 1) {
        --lerpshift;
    }
}

#endif