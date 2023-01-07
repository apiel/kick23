#ifndef SYNTH_H_
#define SYNTH_H_

#include <stdint.h>

#include "def.h"
#include "rotary.h" // note necessary to be there, but just to avoid to include it in all main.h file for each board
#include "state.h"
#include "wavetable.h"

float IRAM_ATTR envelop(float (*envelop)[2], unsigned int* envelopIndex)
{
    if (envelopFreqIndex > ENVELOP_STEPS - 1) {
        return 0.0f;
    }

    float time = (float)sampleCount / (float)sampleCountDuration;
    if (time >= envelop[*envelopIndex + 1][1]) {
        (*envelopIndex)++;
    }
    float timeOffset = envelop[*envelopIndex + 1][1] - envelop[*envelopIndex][1];
    float timeRatio = (time - envelop[*envelopIndex][1]) / timeOffset;
    return (envelop[*envelopIndex + 1][0] - envelop[*envelopIndex][0]) * timeRatio + envelop[*envelopIndex][0];
}

float IRAM_ATTR envelop()
{
    return (float)sampleCount / (float)sampleCountDuration;
}

float sampleIndex = 0.0f;
float IRAM_ATTR getSample()
{
    if (sampleCount < sampleCountDuration) {
        float envFreq = envelop(envelopFreq, &envelopFreqIndex);
        float envAmp = envelop(envelopAmp, &envelopAmpIndex);

        sampleIndex += WAVETABLE_SIZE * (frequency * envFreq) / SAMPLE_RATE;
        while (sampleIndex >= WAVETABLE_SIZE) {
            sampleIndex -= WAVETABLE_SIZE;
        }
        sampleCount++;
        return wavetable[(uint16_t)sampleIndex] * envAmp;
    }
    return 0;
}

void triggerSound()
{
    sampleCount = 0;
    envelopAmpIndex = 0;
    envelopFreqIndex = 0;
}

void buttonPressed()
{
    // Here the button could do other function
    triggerSound();
}

void buttonReleased()
{
    // Here the button could do other function
}

void updatePot(uint8_t potIndex, float value)
{
    if (potIndex < POT_COUNT) {
        potValue[potIndex] = (int)roundf(value * 100.0f) * 0.01f;
    }
}

#endif