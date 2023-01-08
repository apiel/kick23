#ifndef DISTORTION_H_
#define DISTORTION_H_

/**
 * https://www.musicdsp.org/en/latest/Effects/114-waveshaper-simple-description.html?highlight=distortion
 * 
 > The other question; what's a 'waveshaper' algorithm. Is it simply another
> word for distortion?

A typical "waveshaper" is some function which takes an input sample value
X and transforms it to an output sample X'. A typical implementation would
be a look-up table of some number of points, and some level of interpolation
between those points (say, cubic). When people talk about a wave shaper,
this is most often what they mean. Note that a wave shaper, as opposed to a
filter, does not have any state. The mapping from X -> X' is stateless.

Some wave shapers are implemented as polynomials, or using other math
functions. Hard clipping is a wave shaper implemented using the min() and
max() functions (or the three-argument clamp() function, which is the same
thing). A very mellow and musical-sounding distortion is implemented using
a third-degree polynomial; something like X' = (3/2)X - (1/2)X^3. The nice
thing with polynomial wave shapers is that you know that the maximum they
will expand bandwidth is their order. Thus, you need to oversample 3x to
make sure that a third-degree polynomial is aliasing free. With a lookup
table based wave shaper, you don't know this (unless you treat an N-point
table as an N-point polynomial :-)
 * 
 */

float waveshape_distort( float in ) {
  return 1.5f * in - 0.5f * in *in * in;
}

/*
// See
// https://stackoverflow.com/questions/22312841/waveshaper-node-in-webaudio-how-to-emulate-distortion/22313408#22313408
// https://tonejs.github.io/docs/14.7.77/Distortion
// https://github.com/Tonejs/Tone.js/blob/dev/Tone/effect/Distortion.ts

#ifndef IO_AudioEffectDistortion_h_
#define IO_AudioEffectDistortion_h_

#include <Arduino.h>
#include <Audio.h>
#include <arm_math.h>

#define WAVESHAPE_SIZE 4097

class IO_AudioEffectDistortion : public AudioEffectWaveshaper {
   public:
    float amount = 50;
    float range = 20.0;

    IO_AudioEffectDistortion(void) { distortion(50); };

    void distortion(float _amount) {
        amount = _amount;
        if (amount > 0) {
            float deg = PI / 180;
            for (u_int16_t i = 0; i < WAVESHAPE_SIZE; i++) {
                float x = (float)i * 2.0 / (float)WAVESHAPE_SIZE - 1.0;
                waveshapeData[i] =
                    (3 + amount) * x * range * deg / (PI + amount * abs(x));
            }
            shape(waveshapeData, WAVESHAPE_SIZE);
        }
    }

    void setRange(float _range) {
        range = _range;
        distortion(amount);
    }

   private:
    float waveshapeData[WAVESHAPE_SIZE];
};
*/

#endif