#ifndef UI_H_
#define UI_H_

#include <stdint.h>

#include "def.h"
#include "state.h"
#include "ui.h"
#include "wavetable.h"

#ifndef UI_PRINT
#define UI_PRINT printf
#endif

#define UI_MAX_ROW 3

enum {
    UI_MODE_WAVE,
    UI_MODE_AMP,
    UI_MODE_FREQ,
    UI_MODE_COUNT
};

uint8_t uiMode = UI_MODE_WAVE;
uint8_t uiCursor = 0;
bool edit = false;

char cursor(uint8_t pos)
{
    return pos == uiCursor ? (edit ? '>' : ':') : ' ';
}

void render()
{
    switch (uiMode) {
    case UI_MODE_WAVE:
        UI_PRINT("%cWav\n", cursor(0));
        UI_PRINT("%cM%.1f\n", cursor(1), morph);
        UI_PRINT("%c%dHz\n", cursor(2), (int)frequency);
        break;

    case UI_MODE_AMP:
        UI_PRINT("%cAmp\n", cursor(0));
        UI_PRINT("%cM%.1f\n", cursor(1), morph);
        UI_PRINT("%c%dHz\n", cursor(2), (int)frequency);
        break;

    case UI_MODE_FREQ:
        UI_PRINT("%cFreq\n", cursor(0));
        UI_PRINT("%cM%.1f\n", cursor(1), morph);
        UI_PRINT("%c%dHz\n", cursor(2), (int)frequency);
        break;

    default:
        break;
    }
}

void updateWav(int8_t direction)
{
    morph += direction * 0.1f;
    if (morph < 0.0f) {
        morph = 0.0f;
    } else if (morph > WAVETABLE_COUNT) {
        morph = WAVETABLE_COUNT;
    }
    wavetablePos = (uint16_t)(morph / WAVETABLE_COUNT * (WAVETABLE_TOTAL_SIZE - WAVETABLE_SIZE));
}

void rotaryChanged(int8_t direction)
{
    if (edit) {
        if (uiCursor == 0) {
            uiMode = (uiMode + direction + UI_MODE_COUNT) % UI_MODE_COUNT;
        } else {
            switch (uiMode) {
            case UI_MODE_WAVE:
                updateWav(direction);
                break;

            default:
                break;
            }
        }
    } else {
        uiCursor = (uiCursor + direction + UI_MAX_ROW) % UI_MAX_ROW;
    }
    render();
}

void rotaryPressed()
{
    edit = !edit;
    render();
}

#endif