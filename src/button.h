#ifndef BUTTON_H_
#define BUTTON_H_

#include "synth.h"

enum {
    BUTTON_TRIGGER,
    BUTTON_PATTERN2,
    BUTTON_MODE_COUNT,
};

const char* buttonNames[BUTTON_MODE_COUNT] = {
    "Trig",
    "Pat2",
};

uint8_t buttonMode = BUTTON_PATTERN2;

void buttonPressed()
{
    switch (buttonMode) {
    case BUTTON_TRIGGER:
        triggerSound();
        return;

    case BUTTON_PATTERN2:
        patternPtr = pattern2;
        return;
    }
}

void buttonReleased()
{
    switch (buttonMode) {
    case BUTTON_PATTERN2:
        patternPtr = pattern;
        return;
    }
}

#endif
