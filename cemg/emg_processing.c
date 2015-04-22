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

#include <stdio.h>


// ---- States for the device

typedef enum processing_state_t
{
    pstate_waiting_for_onset,
    pstate_recording_samples,
    pstate_waiting_for_rest

} processing_state_t;


// ---- processing_info_t methods

void init_processing_info(
    processing_info_t *processing_info,
    unsigned speriod
){
    processing_info->speriod = speriod;

    for (int i = 0; i < MAX_EMG_CHANNELS; i++)
        init_onset_info(&processing_info->onset_info[i]);
}


// ---- Main processing methods

void extract_all_features(double features[], emg_signal_group_t signal_group)
{
    // Extract features using 0.005 as the default parameter for now..

    const int N = MAX_EMG_CHANNELS * emg_feature_count;

    for (int n = 0; n < N; n++)
    {
        features[n] = extract_feature(
            signal_group[n % MAX_EMG_CHANNELS],
            n % emg_feature_count,
            0.005f
        );
    }
}


void transmit_features(double features[])
{
    const int N = MAX_EMG_CHANNELS * emg_feature_count;

    printf("\n[");
    for (unsigned n = 0; n < N; n++)
        printf("%0.4f ", features[n]);
    printf("]\n\n");
}


void process_sample(
    processing_info_t * processing_info,
    emg_sample_group_t sample_group
){
    static processing_state_t state;
    static double features[emg_feature_count * MAX_EMG_CHANNELS];
    static unsigned count;
    static unsigned total_count;
    static unsigned onset_found;
    static unsigned feat_count;

    static emg_signal_group_t signal_group; // Signal to hold data after onset
                                            // of motion has been detected

    switch (state)
    {
        case pstate_waiting_for_onset:

            // Wait for motion to begin before collecting
            // samples to extract features from.

            if (onset_detected(processing_info->onset_info, sample_group))
            {
                onset_found = total_count;

                for (int n = 0; n < MAX_EMG_CHANNELS; n++)
                    signal_group[n][0] = sample_group[n];

                count = 1;

                state = pstate_recording_samples;
            }

            break;

        case pstate_recording_samples:

            // While motion is maintained, record samples until
            // enough to extract features from is obtained.

            if (onset_detected(processing_info->onset_info, sample_group))
            {
                // Read in sample
                for (int n = 0; n < MAX_EMG_CHANNELS; n++)
                    signal_group[n][count] = sample_group[n];

                count++;

                if (count >= MAX_EMG_SIGNAL_LENGTH)
                {
                    printf("Onset detected at sample %u\n", onset_found);

                    // OPTIMIZATION: Calculate features incrementally, instead
                    //               of all at once.
                    extract_all_features(features, signal_group);

                    //transmit_features(features);

                    state = pstate_waiting_for_rest;

                    feat_count++;

                    printf("Read in %u gestures\n", feat_count);
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

            if (!onset_detected(processing_info->onset_info, sample_group))
            {
                //printf("Rest at %u\n", total_count);
                state = pstate_waiting_for_onset;
            }

            break;
    }

    total_count++;
}

