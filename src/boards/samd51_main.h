#include <Adafruit_NeoTrellisM4.h>
#include <Arduino.h>

#include "samd51_dac.h"

#define SAMPLE_RATE AUDIO_TC_FREQ

#include "synth.h"

void audioCallback(const uint32_t* end, uint32_t* dest)
{
    do {
        int16_t sample = getSample() * 16383;
        // int16_t sample = getSample() *  0x7FFF;
        // uint32_t sample = getSample() * 16383;
        // uint32_t sample = getSample() * 0x7FFF;
        // uint32_t sample = getSample() * 2147483647;
        // *dest++ = sample;
        // *dest++ = sample;

        uint32_t out = ((sample & 0xFFFF) + 32768) >> 1;
        // uint32_t out = ((sample & 0xFFFF) + 32768) >> 4;
        // out |= (((sample & 0xFFFF) + 32768) >> 4) << 16;
        *dest++ = out;
        *dest++ = out;
    } while (dest < end);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Kick23");

    initDac(audioCallback);
}

uint8_t counter = 0;
void loop()
{
    if (counter < 5) {
        // if (counter < 10) {
        Serial.println("Trigger sound");
        triggerSound();
        delay(1000);
        counter++;
    }
}
