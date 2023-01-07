#ifndef ROTARY_H_
#define ROTARY_H_

#include <stdint.h>

#include "def.h"
#include "state.h"
#include "ui.h"

int counterRT = 0;
void rotaryChanged(int8_t direction)
{
    counterRT += direction;
    APP_LOG("rotaryChanged: %d\n", counterRT);
}

void rotaryPressed()
{
    APP_LOG("rotaryPressed\n");
}


#endif