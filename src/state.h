#ifndef STATE_H_
#define STATE_H_

#include "def.h"

float potValue[POT_COUNT] = { 0, 0, 0 };

float frequency = 600.0f;
float morph = 0.0f;
unsigned int wavetablePos = 0;

// 90ms kick duration
// uint sampleCountDuration = 90 * SAMPLE_PER_MS;
unsigned int sampleCountDuration = 300 * SAMPLE_PER_MS;
unsigned int sampleCount = -1; // set it to max uint value so it will not trigger the kick at the beginning

// REMOVE clicking from beginning
// float envelopAmp[ENVELOP_STEPS][2] = { { 0.0f, 0.0f }, { 1.0f, 0.01f }, { 0.0f, 1.0f }, { 0.0f, 1.0f }, { 0.0f, 1.0f } };
float envelopAmp[ENVELOP_STEPS][2] = { { 0.0f, 0.0f }, { 1.0f, 0.01f }, { 0.3f, 0.4f }, { 0.0f, 1.0f }, { 0.0f, 1.0f } };
float envelopFreq[ENVELOP_STEPS][2] = { { 1.0f, 0.0f }, { 0.26f, 0.03f }, { 0.24f, 0.35f }, { 0.22f, 0.4f }, { 0.0f, 1.0f } };

unsigned int envelopAmpIndex = 0;
unsigned int envelopFreqIndex = 0;

#endif