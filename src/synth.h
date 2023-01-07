#ifndef SYNTH_H_
#define SYNTH_H_

#include <stdint.h>

#include "def.h"
#include "wavetable.h"

float frequency = 600.0f;

// 90ms kick duration
// uint sampleCountDuration = 90 * SAMPLE_PER_MS;
unsigned int sampleCountDuration = 300 * SAMPLE_PER_MS;
unsigned int sampleCount = -1; // set it to max uint value so it will not trigger the kick at the beginning

#define ENVELOP_STEPS 5

// REMOVE clicking from beginning
// float envelopAmp[ENVELOP_STEPS][2] = { { 0.0f, 0.0f }, { 1.0f, 0.01f }, { 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 1.0f } };
float envelopAmp[ENVELOP_STEPS][2] = { { 0.0f, 0.0f }, { 1.0f, 0.01f }, { 0.3f, 0.4f }, { 0.0f, 1.0f }, { 0.0f, 1.0f } };
float envelopFreq[ENVELOP_STEPS][2] = { { 1.0f, 0.0f }, { 0.26f, 0.03f }, { 0.24f, 0.35f }, { 0.22f, 0.4f }, { 0.0f, 1.0f } };

unsigned int envelopAmpIndex = 0;
unsigned int envelopFreqIndex = 0;

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
float sampleStep = 1.0f;

float IRAM_ATTR getSample()
{
    if (sampleCount < sampleCountDuration) {
        float envFreq = envelop(envelopFreq, &envelopFreqIndex);
        float envAmp = envelop(envelopAmp, &envelopAmpIndex);

        sampleStep = WAVETABLE_SIZE * (frequency * envFreq) / SAMPLE_RATE;

        sampleIndex += sampleStep;
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

int counterRT = 0;
void rotaryChanged(int8_t direction)
{
    counterRT += direction;
    APP_LOG("rotaryChanged: %d\n", counterRT);
}

void rotaryPressed()
{
    APP_LOG("rotaryPressed\n");
}

#define POT_COUNT 3

uint8_t potValue[POT_COUNT] = { 0, 0, 0 };
void updatePot(uint8_t potIndex, float value)
{
    uint8_t val = roundf(value * 100.0f);
    if (potIndex < POT_COUNT && val != potValue[potIndex]) {
        // APP_LOG("Pot %d value changed: %d\n", potIndex, potValue[potIndex]);
        potValue[potIndex] = val;
    }
}

#endif