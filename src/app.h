#ifndef APP_H_
#define APP_H_

#include "button.h"
#include "sequencer.h"
#include "synth.h"
#include "ui.h"

void appInit()
{
    render();
    setTempo();
}

void appLoop()
{
}

#endif