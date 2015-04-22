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
    unsigned num_channels,
    unsigned speriod
){
    unsigned i;

    processing_info->speriod = speriod;

    init_filter_buffer(&processing_info->buffer);
    init_emg_signal_group(&processing_info->signal_group, num_channels);

    for (i = 0; i < MAX_EMG_CHANNELS; i++)
        init_onset_info(&processing_info->onset_info[i]);

    processing_info->signal_group.length = speriod;

    for (i = 0; i < MAX_EMG_CHANNELS; i++)
        processing_info->signal_group.channels[i].length = speriod;
}


void read_in_sample_group(
    processing_info_t * processing_info,
    emg_sample_group_t * sample_group
){
    insert_sample_group_filt_buffer(&processing_info->buffer, sample_group);
}


// ---- Main processing methods

void extract_all_features(double features[], emg_signal_group_t * signal_group)
{
    unsigned n;
    emg_feature_t f;
    // Extract features using 0.005 as a default parameter for now..
    for (n = 0; n < signal_group->num_channels; n++)
        for (f = 0; f < emg_feature_count; f++)
            features[f+n*emg_feature_count] = extract_feature(&signal_group->channels[n], f, .005);
}


void transmit_features(double features[], emg_signal_group_t * signal_group)
{
    emg_feature_t f;
    unsigned n;

    printf("[%0.6f %0.6f %0.6f %0.6f %0.6f %0.6f %0.6f %0.6f %0.6f %0.6f]");

    printf("\n");
    printf("[");
    for (n = 0; n < signal_group->num_channels; n++)
        for (f = 0; f < emg_feature_count; f++)
            printf("%0.6f ", features[f+n*emg_feature_count]);
    printf("]");
    printf("\n");

    /*
    printf("\nExtracted features:\n");
    for (n = 0; n < signal_group->num_channels; n++){
        for (f = 0; f < emg_feature_count; f++)
            printf("\t%s - %5.2f\n", feature_name(f), );
        printf("\n");
    }
    */
}


void process_sample(processing_info_t * processing_info)
{
    static processing_state_t state;
    static double features[emg_feature_count * MAX_EMG_CHANNELS];
    static unsigned count;
    static unsigned total_count;

    emg_sample_group_t sample_group = get_current_sample_group(
        &processing_info->buffer
    );

    switch (state)
    {
        case pstate_waiting_for_onset:

            // Wait for motion to begin before collecting
            // samples to extract features from.

            if (onset_detected(processing_info->onset_info, sample_group.num_channels, &sample_group))
            {
                printf("Onset detected at sample %u\n", total_count);

                insert_sample_group(
                    &processing_info->signal_group,
                    &sample_group,
                    0
                );

                count = 1;

                state = pstate_recording_samples;
            }

            break;

        case pstate_recording_samples:

            // While motion is maintained, record samples until
            // enough to extract features from is obtained.

            if (onset_detected(processing_info->onset_info, sample_group.num_channels, &sample_group))
            {
                insert_sample_group(
                    &processing_info->signal_group,
                    &sample_group,
                    count++
                );

                if (count >= processing_info->speriod)
                {
                    extract_all_features(
                        features,
                        &processing_info->signal_group
                    );
                    transmit_features(features, &processing_info->signal_group);

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

            if (!onset_detected(processing_info->onset_info, sample_group.num_channels, &sample_group))
            {
                printf("Rest at %u\n", total_count);
                state = pstate_waiting_for_onset;
            }

            break;
    }

    total_count++;
}

