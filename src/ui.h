#ifndef UI_H_
#define UI_H_

#include <stdint.h>

#include "def.h"
#include "state.h"
#include "ui.h"
#include "wavetable.h"

void render()
{
    printf("Wav\nM%.1f\n%dHz\n", morph, (int)frequency);
}

void rotaryChanged(int8_t direction)
{
    morph += direction * 0.1f;
    if (morph < 0.0f) {
        morph = 0.0f;
    } else if (morph > WAVETABLE_COUNT) {
        morph = WAVETABLE_COUNT;
    }
    wavetablePos = (uint16_t)(morph / WAVETABLE_COUNT * (WAVETABLE_TOTAL_SIZE - WAVETABLE_SIZE));
    render();
}

void rotaryPressed()
{
}

#endif