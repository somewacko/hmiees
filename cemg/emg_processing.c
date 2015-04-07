//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_processing.c
//  flynn, michael
//
//  functions to manage the processing of an emg signal, including onset of
//  motion detection and feature extraction.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_processing.h"

#include "emg_features.h"
#include "emg_onset.h"

#include <stdio.h>

typedef enum processing_state_t
{
    waiting_for_onset,
    recording_samples,

} processing_state_t;


void extract_all_features(float features[], emg_signal_t * sig)
{
    for (emg_feature_t feat = 0; feat < emg_feature_count; feat++)
        features[feat] = extract_feature(sig, feat, 0.005);

    #ifdef __CEMG_TEST__
    printf("\nExtracted features:\n");
    for (emg_feature_t f = 0; f < emg_feature_count; f++)
        printf("\t%s - %5.2f\n", feature_name(f), features[f]);
    printf("\n");
    #endif
}


void transmit_features(float features[])
{
    // To be implemented on PIC...
}


void process_sample(emg_sample_t sample, const unsigned speriod)
{
    static processing_state_t state;
    static emg_signal_t sig;
    static float features[emg_feature_count];
    static unsigned count;
    static unsigned total_count;

    switch (state)
    {
        case waiting_for_onset:

            // Wait for motion to begin before collecting
            // samples to extract features from.

            if (onset_detected(sample))
            {
                #ifdef __CEMG_TEST__
                printf("Onset detected at sample %u\n", total_count);
                #endif

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

                    extract_all_features(features, &sig);
                    transmit_features(features);

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

