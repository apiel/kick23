#ifndef SEQUENCER_H_
#define SEQUENCER_H_

#include <stdint.h>

#include "def.h"
#include "state.h"

enum {
    STEP_MUTED,
    STEP_PLAYING,
    STEP_EVERY_PAIR,
    STEP_EVERY_THIRD,
    STEP_EVERY_FOURTH,
    STEP_EVERY_FIFTH,
    STEP_EVERY_SIXTH,
    STEP_EVERY_SEVENTH,
    STEP_EVERY_EIGHTH,
    STEP_EVERY_IMPAIR,
    STEP_1_PERCENT,
    STEP_2_PERCENT,
    STEP_5_PERCENT,
    STEP_10_PERCENT,
    STEP_20_PERCENT,
    STEP_30_PERCENT,
    STEP_40_PERCENT,
    STEP_50_PERCENT,
    STEP_60_PERCENT,
    STEP_70_PERCENT,
    STEP_80_PERCENT,
    STEP_90_PERCENT,
    STEP_95_PERCENT,
    STEP_COUNT,
};

const char* stepNames[STEP_COUNT] = {
    "Muted",
    "Playing",
    "Pair",
    "Third",
    "4th",
    "5th",
    "6th",
    "7th",
    "8th",
    "Impair",
    "1%",
    "2%",
    "5%",
    "10%",
    "20%",
    "30%",
    "40%",
    "50%",
    "60%",
    "70%",
    "80%",
    "90%",
    "95%",
};

unsigned int seqTime = 0;
uint8_t seqPos = 0;

bool seqNext()
{
    seqTime++;
    if (seqTime >= sampleCountTempo) {
        seqTime = 0;
        seqPos++;
        if (seqPos >= PATTERN_STEPS) {
            seqPos = 0;
        }
        if (seqPos % 4 == 0) {
            return true;
        }
    }
    return false;
}

void setTempo(uint8_t _bpm = bpm)
{
    bpm = _bpm;
    sampleCountTempo = SAMPLE_RATE * 60.0f / _bpm;
}

#endif