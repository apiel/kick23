#ifndef APP_H_
#define APP_H_

#include "synth.h"
#include "sequencer.h"
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