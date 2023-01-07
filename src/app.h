#ifndef APP_H_
#define APP_H_

#include "synth.h"
#include "ui.h"

void appInit()
{
    render();
}

uint8_t counter = 0;
void appLoop()
{
    // if (counter < 5) {
    //     // if (counter < 10) {
    //     APP_LOG("Trigger sound");
    //     triggerSound();
    //     delay(1000);
    //     counter++;
    // }
}

#endif