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


// ---- States for the device

typedef enum processing_state_t
{
    pstate_waiting_for_onset,
    pstate_recording_samples,
    pstate_waiting_for_rest

} processing_state_t;


// ---- processing_info_t methods

processing_info_t init_processing_info(unsigned speriod)
{
    processing_info_t processing_info = {
        .buffer  = init_filter_buffer(),
        .speriod = speriod
    };

    return processing_info;
}


void read_in_sample(processing_info_t * processing_info, emg_sample_t sample)
{
    insert_sample(&processing_info->buffer, sample);
}


// ---- Main processing methods

void extract_all_features(float features[], emg_signal_t * sig)
{
    // Extract features using 0.005 as a default parameter for now..
    for (emg_feature_t feat = 0; feat < emg_feature_count; feat++)
        features[feat] = extract_feature(sig, feat, 0.005);
}


void transmit_features(float features[])
{
    // { Actual transmittion yet to be implemented... }

    printf("\nExtracted features:\n");
    for (emg_feature_t f = 0; f < emg_feature_count; f++)
        printf("\t%s - %5.2f\n", feature_name(f), features[f]);
    printf("\n");
}


void process_sample(processing_info_t * processing_info)
{
    static processing_state_t state;
    static emg_signal_t sig;
    static float features[emg_feature_count];
    static unsigned count;
    static unsigned total_count;

    emg_sample_t sample = get_current_sample(&processing_info->buffer);

    switch (state)
    {
        case pstate_waiting_for_onset:

            // Wait for motion to begin before collecting
            // samples to extract features from.

            if (onset_detected(sample))
            {
                printf("Onset detected at sample %u\n", total_count);

                sig.samples[0] = sample;
                count = 1;

                state = pstate_recording_samples;
            }

            break;

        case pstate_recording_samples:

            // While motion is maintained, record samples until
            // enough to extract features from is obtained.

            if (onset_detected(sample))
            {
                sig.samples[count++] = sample;

                if (count >= processing_info->speriod)
                {
                    sig.length = processing_info->speriod;

                    extract_all_features(features, &sig);
                    transmit_features(features);

                    state = pstate_waiting_for_rest;
                }
            }
            else
            {
                state = pstate_waiting_for_onset;
            }

            break;

        case pstate_waiting_for_rest:

            // After the gesture has been transmitted, wait
            // for motion rest before recognizing another.

            if (!onset_detected(sample))
            {
                printf("Rest at %u\n", total_count);
                state = pstate_waiting_for_onset;
            }

            break;
    }

    total_count++;
}

