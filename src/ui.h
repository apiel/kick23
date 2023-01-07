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
    UI_MODE_MAIN,
    // PRESET might be in main view depending screen size (preset need also save)
    // as wave could move to main as well?
    UI_MODE_WAVE,
    UI_MODE_AMP,
    UI_MODE_FREQ,
    UI_MODE_COUNT
};

uint8_t uiMode = 0;
uint8_t uiCursor = 0;
bool edit = false;

char cursor(uint8_t pos)
{
    return pos == uiCursor ? (edit ? '>' : ':') : ' ';
}

void render()
{
    switch (uiMode) {
    case UI_MODE_MAIN:
        UI_PRINT("%cMain\n", cursor(0));
        UI_PRINT("%c%dms\n", cursor(1), duration);
        UI_PRINT("%c%d%%\n", cursor(2), (int)(volume * 100));
        break;
    case UI_MODE_WAVE:
        UI_PRINT("%cWav\n", cursor(0));
        UI_PRINT("%cM%.1f\n", cursor(1), morph);
        UI_PRINT("%c%dHz\n", cursor(2), (int)frequency);
        break;

    // for AMP and FREQ, we might need multiple SCREEN like AMP1, AMP2, AMP3 depending screen size?
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

void updateMain(int8_t direction)
{
    if (uiCursor == 1) {
        duration += direction * 10;
        if (duration < 10) {
            duration = 10;
        } else if (duration > 5000) {
            duration = 5000;
        }
        sampleCountDuration = duration * SAMPLE_PER_MS;
    } else if (uiCursor == 2) {
        volume += direction * 0.01f;
        if (volume < 0.0f) {
            volume = 0.0f;
        } else if (volume > 1.0f) {
            volume = 1.0f;
        }
    }
}

void updateWav(int8_t direction)
{
    if (uiCursor == 1) {
        morph += direction * 0.1f;
        if (morph < 0.0f) {
            morph = 0.0f;
        } else if (morph > WAVETABLE_COUNT) {
            morph = WAVETABLE_COUNT;
        }
        wavetablePos = (uint16_t)(morph / WAVETABLE_COUNT * (WAVETABLE_TOTAL_SIZE - WAVETABLE_SIZE));
    } else if (uiCursor == 2) {
        frequency += direction * 10.0f;
        if (frequency < 10.0f) {
            frequency = 0.0f;
        } else if (frequency > 2000.0f) {
            frequency = 20000.0f;
        }
    }
}

void rotaryChanged(int8_t direction)
{
    if (edit) {
        if (uiCursor == 0) {
            uiMode = (uiMode + direction + UI_MODE_COUNT) % UI_MODE_COUNT;
        } else {
            switch (uiMode) {
            case UI_MODE_MAIN:
                updateMain(direction);
                break;

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