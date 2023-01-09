#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

/**
 * https://www.musicdsp.org/en/latest/Effects/169-compressor.html
 * 
 * RMS is a true way to estimate _musical_ signal energy,
our ears behaves in a same way.

to making all it work,
try this values (as is, routine accepts percents and milliseconds) for first time:

threshold = 50%
slope = 50%
RMS window width = 1 ms
lookahead = 3 ms
attack time = 0.1 ms
release time = 300 ms

This code can be significantly improved in speed by
changing RMS calculation loop to 'running summ'
(keeping the summ in 'window' -
adding next newest sample and subtracting oldest on each step)
 * 
 */

void compress
    (
        float*  wav_in,     // signal
        int     n,          // N samples
        double  threshold,  // threshold (percents)
        double  slope,      // slope angle (percents)
        int     sr,         // sample rate (smp/sec)
        double  tla,        // lookahead  (ms)
        double  twnd,       // window time (ms)
        double  tatt,       // attack time  (ms)
        double  trel        // release time (ms)
    )
{
    typedef float   stereodata[2];
    stereodata*     wav = (stereodata*) wav_in; // our stereo signal
    threshold *= 0.01;          // threshold to unity (0...1)
    slope *= 0.01;              // slope to unity
    tla *= 1e-3;                // lookahead time to seconds
    twnd *= 1e-3;               // window time to seconds
    tatt *= 1e-3;               // attack time to seconds
    trel *= 1e-3;               // release time to seconds

    // attack and release "per sample decay"
    double  att = (tatt == 0.0) ? (0.0) : exp (-1.0 / (sr * tatt));
    double  rel = (trel == 0.0) ? (0.0) : exp (-1.0 / (sr * trel));

    // envelope
    double  env = 0.0;

    // sample offset to lookahead wnd start
    int     lhsmp = (int) (sr * tla);

    // samples count in lookahead window
    int     nrms = (int) (sr * twnd);

    // for each sample...
    for (int i = 0; i < n; ++i)
    {
        // now compute RMS
        double  summ = 0;

        // for each sample in window
        for (int j = 0; j < nrms; ++j)
        {
            int     lki = i + j + lhsmp;
            double  smp;

            // if we in bounds of signal?
            // if so, convert to mono
            if (lki < n)
                smp = 0.5 * wav[lki][0] + 0.5 * wav[lki][1];
            else
                smp = 0.0;      // if we out of bounds we just get zero in smp

            summ += smp * smp;  // square em..
        }

        double  rms = sqrt (summ / nrms);   // root-mean-square

        // dynamic selection: attack or release?
        double  theta = rms > env ? att : rel;

        // smoothing with capacitor, envelope extraction...
        // here be aware of pIV denormal numbers glitch
        env = (1.0 - theta) * rms + theta * env;

        // the very easy hard knee 1:N compressor
        double  gain = 1.0;
        if (env > threshold)
            gain = gain - (env - threshold) * slope;

        // result - two hard kneed compressed channels...
        float  leftchannel = wav[i][0] * gain;
        float  rightchannel = wav[i][1] * gain;
    }
}

/**
* https://www.musicdsp.org/en/latest/Synthesis/272-randja-compressor.html?highlight=compressor
*/

#include <cmath>
#define max(a,b) (a>b?a:b)

class compressor
{

    private:
            float   threshold;
            float   attack, release, envelope_decay;
            float   output;
            float   transfer_A, transfer_B;
            float   env, gain;

    public:
    compressor()
    {
            threshold = 1.f;
            attack = release = envelope_decay = 0.f;
            output = 1.f;

            transfer_A = 0.f;
            transfer_B = 1.f;

            env = 0.f;
            gain = 1.f;
    }

    void set_threshold(float value)
    {
            threshold = value;
            transfer_B = output * pow(threshold,-transfer_A);
    }


    void set_ratio(float value)
    {
            transfer_A = value-1.f;
            transfer_B = output * pow(threshold,-transfer_A);
    }


    void set_attack(float value)
    {
            attack = exp(-1.f/value);
    }


    void et_release(float value)
    {
            release = exp(-1.f/value);
            envelope_decay = exp(-4.f/value); /* = exp(-1/(0.25*value)) */
    }


    void set_output(float value)
    {
            output = value;
            transfer_B = output * pow(threshold,-transfer_A);
    }


    void reset()
    {
            env = 0.f; gain = 1.f;
    }


    void process(float *input_left, float *input_right,float *output_left, float *output_right,       int frames)
    {
            float det, transfer_gain;
            for(int i=0; i<frames; i++)
            {
                    det = max(fabs(input_left[i]),fabs(input_right[i]));
                    det += 10e-30f; /* add tiny DC offset (-600dB) to prevent denormals */

                    env = det >= env ? det : det+envelope_decay*(env-det);

                    transfer_gain = env > threshold ? pow(env,transfer_A)*transfer_B:output;

                    gain = transfer_gain < gain ?
                                                    transfer_gain+attack *(gain-transfer_gain):
                                                    transfer_gain+release*(gain-transfer_gain);

                    output_left[i] = input_left[i] * gain;
                    output_right[i] = input_right[i] * gain;
            }
    }


    void process(double *input_left, double *input_right,     double *output_left, double *output_right,int frames)
    {
            double det, transfer_gain;
            for(int i=0; i<frames; i++)
            {
                    det = max(fabs(input_left[i]),fabs(input_right[i]));
                    det += 10e-30f; /* add tiny DC offset (-600dB) to prevent denormals */

                    env = det >= env ? det : det+envelope_decay*(env-det);

                    transfer_gain = env > threshold ? pow(env,transfer_A)*transfer_B:output;

                    gain = transfer_gain < gain ?
                                                    transfer_gain+attack *(gain-transfer_gain):
                                                    transfer_gain+release*(gain-transfer_gain);

                    output_left[i] = input_left[i] * gain;
                    output_right[i] = input_right[i] * gain;
            }
    }

};

#endif