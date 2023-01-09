#ifndef DISTORTION_H_
#define DISTORTION_H_

#define PI 3.1415926535897932384626433832795
#define WAVESHAPE_SIZE 4097

float amount = 50;
float range = 20.0;
int16_t lerpshift;
int16_t waveshape2[WAVESHAPE_SIZE];

void setDistortion(float _amount)
{
    amount = _amount;
    if (amount > 0) {
        float deg = PI / 180;
        for (u_int16_t i = 0; i < WAVESHAPE_SIZE; i++) {
            float x = (float)i * 2.0 / (float)WAVESHAPE_SIZE - 1.0;
            float waveshape = (3 + amount) * x * range * deg / (PI + amount * abs(x));
            waveshape2[i] = 32767 * waveshape;
        }
    }

    // set lerpshift to the number of bits to shift while interpolating
    // to cover the entire waveshape over a uint16_t input range
    int index = WAVESHAPE_SIZE - 1;
    lerpshift = 16;
    while (index >>= 1)
        --lerpshift;
}

void setRange(float _range)
{
    range = _range;
    setDistortion(amount);
}

float distortion(float in)
{
// return in;

    uint16_t x = in * 32768 + 32768;
    uint16_t xa = x >> lerpshift;
    int16_t ya = waveshape2[xa];
    int16_t yb = waveshape2[xa + 1];
    x = ya + ((yb - ya) * (x - (xa << lerpshift)) >> lerpshift);

    return x / 32768.0f;
}

void initDistortion()
{
    setDistortion(amount);
}

#endif