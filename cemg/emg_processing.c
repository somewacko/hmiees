//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_processing.c
//  flynn, michael
//
//  functions to manage the processing of an emg signal, including onset of
//  motion detection and feature extraction.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_processing.h"

#include "emg_onset.h"

#include <stdio.h>


typedef enum processing_state_t
{
    waiting_for_onset,
    recording_samples,

} processing_state_t;


void process_sample(emg_sample_t sample, const unsigned speriod)
{
    static processing_state_t state;
    static emg_signal_t sig;
    static unsigned count;
    static unsigned total_count;

    switch (state)
    {
        case waiting_for_onset:

            // Wait for motion to begin before collecting
            // samples to extract features from.

            if (onset_detected(sample))
            {
                printf("Onset detected at sample %u\n", total_count);

                sig.samples[0] = sample;
                count = 1;

                state = recording_samples;
            }

            break;

        case recording_samples:

            // While motion is maintained, record samples until
            // enough to extract features from is obtained.

            if (onset_detected(sample))
            {
                sig.samples[count++] = sample;

                if (count >= speriod)
                {
                    sig.length = speriod;

                    // { Extract features }

                    // { Transmit via bluetooth }

                    state = waiting_for_onset;
                }
            }
            else
            {
                state = waiting_for_onset;
            }

            break;
    }

    total_count++;
}

