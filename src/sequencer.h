#ifndef SEQUENCER_H_
#define SEQUENCER_H_

#include <stdint.h>

#include "def.h"
#include "state.h"

enum {
    STEP_MUTED,
    STEP_PLAYING,
    STEP_EVERY_PAIR,
    STEP_EVERY_FOURTH,
    STEP_EVERY_SIXTH,
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
    "4th",
    "6th",
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

uint8_t pattern[PATTERN_STEPS] = {
    STEP_PLAYING,
    STEP_MUTED,
    STEP_MUTED,
    STEP_MUTED,
    STEP_PLAYING,
    STEP_MUTED,
    STEP_EVERY_FOURTH,
    STEP_MUTED,
};

uint8_t seqLoopCounter = 1; // Start at 1 else STEP_EVERY_PAIR, STEP_EVERY_THIRD, ... will be triggered at the beginning
unsigned int seqTime = 0;
uint8_t seqPos = 0;

bool seqNext()
{
    seqTime++;
    if (seqTime >= sampleCountPerStep) {
        seqTime = 0;
        seqPos++;
        if (seqPos >= PATTERN_STEPS) {
            seqPos = 0;
            seqLoopCounter++;
            if (seqLoopCounter >= 8) { // 8 because of STEP_EVERY_EIGHTH
                seqLoopCounter = 0;
            }
        }
        switch (pattern[seqPos]) {
        case STEP_MUTED:
            return false;

        case STEP_PLAYING:
            return true;

        case STEP_EVERY_PAIR:
            return seqLoopCounter % 2 == 0;

        case STEP_EVERY_FOURTH:
            return seqLoopCounter % 4 == 0;

        case STEP_EVERY_SIXTH:
            return seqLoopCounter % 6 == 0;

        case STEP_EVERY_EIGHTH:
            return seqLoopCounter % 8 == 0;

        case STEP_EVERY_IMPAIR:
            return seqLoopCounter % 2 == 0;

        case STEP_1_PERCENT:
            return APP_RAND(100) == 0;

        case STEP_2_PERCENT:
            return APP_RAND(100) < 2;

        case STEP_5_PERCENT:
            return APP_RAND(100) < 5;

        case STEP_10_PERCENT:
            return APP_RAND(100) < 10;

        case STEP_20_PERCENT:
            return APP_RAND(100) < 20;

        case STEP_30_PERCENT:
            return APP_RAND(100) < 30;

        case STEP_40_PERCENT:
            return APP_RAND(100) < 40;

        case STEP_50_PERCENT:
            return APP_RAND(100) < 50;

        case STEP_60_PERCENT:
            return APP_RAND(100) < 60;

        case STEP_70_PERCENT:
            return APP_RAND(100) < 70;

        case STEP_80_PERCENT:
            return APP_RAND(100) < 80;

        case STEP_90_PERCENT:
            return APP_RAND(100) < 90;

        case STEP_95_PERCENT:
            return APP_RAND(100) < 95;
        }
    }
    return false;
}

void setTempo(uint8_t _bpm = bpm)
{
    bpm = _bpm;
    unsigned int samplePerBeat = (float)SAMPLE_RATE * 60.0f / (float)_bpm;
    sampleCountPerStep = samplePerBeat / 4;
    // APP_LOG("Tempo: %d bpm, %d samples per beat %d samples per step\n", bpm, samplePerBeat, sampleCountPerStep);
}

#endif