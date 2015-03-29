//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_signal.h
//  flynn, michael
//
//  definitions for representing emg signals.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_SIGNAL_H
#define _EMG_SIGNAL_H

#include <stdint.h>

#define MAX_EMG_SIGNAL_LENGTH 10000

typedef float emg_sample_t; // NOTE: This is assuming that we're going to use
                            // float on the microcontroller. (I was assured it
                            // would be fine..)

typedef struct emg_signal_t
{
    // Preallocated buffer of emg samples.
    emg_sample_t samples[MAX_EMG_SIGNAL_LENGTH];

    // Length of the actual signal.
    unsigned length;

} emg_signal_t;

#endif
