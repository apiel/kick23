#include <Adafruit_NeoTrellisM4.h>
#include <Arduino.h>

#include "samd51_dac.h"

#define SAMPLE_RATE AUDIO_TC_FREQ

#include "app.h"

Adafruit_NeoTrellisM4 trellis = Adafruit_NeoTrellisM4();

void audioCallback(const uint32_t* end, uint32_t* dest)
{
    do {
        int16_t sample = getSample() * 16383;
        // uint32_t out = ((sample & 0xFFFF) + 32768) >> 4 << 16;
        // uint32_t out = ((sample & 0xFFFF) + 32768) >> 4 << 18;
        uint32_t out = ((sample & 0xFFFF) + 32768) >> 4 << 19;
        *dest++ = out;
    } while (dest < end);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Kick23");

    initDac(audioCallback);

    trellis.begin();
    trellis.setBrightness(255);
    appInit();
}

void loop()
{
    appLoop();

    trellis.tick();
    while (trellis.available()) {
        keypadEvent e = trellis.read();
        int keyindex = e.bit.KEY;
        if (e.bit.EVENT == KEY_JUST_PRESSED) {
            trellis.setPixelColor(keyindex, 125);
            triggerSound();
        } else if (e.bit.EVENT == KEY_JUST_RELEASED) {
            trellis.setPixelColor(keyindex, 0);
        }
    }
}
