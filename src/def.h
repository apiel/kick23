#ifndef _DEF_H_
#define _DEF_H_

// For linux runtime compatibility
#ifndef IRAM_ATTR
#define IRAM_ATTR
#endif

#ifndef SAMPLE_RATE
#define SAMPLE_RATE 44100
#endif
const float SAMPLE_PER_MS = SAMPLE_RATE / 1000.0f;

#define ENVELOP_STEPS 5

#define POT_COUNT 3

#endif