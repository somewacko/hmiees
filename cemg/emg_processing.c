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


// ---- 7th-order butterworth filter coefficients to get cutoff frequency
//      of 500 Hz from 8000 Hz
//
//      matlab:
// 
//      > [b, a] = butter(7, 2*1000/8000);
//      > a =
//           1.0000000000  -5.2367698634  11.9272434137 -15.2840131998
//          11.8827420583  -5.5983497659   1.4785129329 - 0.1687178026
//      > b = 
//           0.0000050607   0.0000354251   0.0001062753   0.0001771255
//           0.0001771255   0.0001062753   0.0000354251   0.0000050607

static const unsigned filt_size = 8;

static const float filt_a[] = {
     1.0000000000, - 5.2367698634,
    11.9272434137, -15.2840131998,
    11.8827420583, - 5.5983497659,
     1.4785129329, - 0.1687178026
};

static const float filt_b[] = {
     0.0000050607,   0.0000354251,
     0.0001062753,   0.0001771255,
     0.0001771255,   0.0001062753, 
     0.0000354251,   0.0000050607
};


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
        .current_index = 0,
        .speriod       = speriod
    };

    // Initialize buffer to 0
    for (unsigned i = 0; i < BUFFER_SIZE; i++)
    {
        processing_info.input_buffer[i]  = 0;
        processing_info.output_buffer[i] = 0;
    }

    return processing_info;
}


void read_in_sample(processing_info_t * processing_info, emg_sample_t sample)
{
    // Determine the current index in the buffer and put in input buffer

    unsigned buffer_index = processing_info->current_index + 1 >= BUFFER_SIZE ?
        0 : processing_info->current_index + 1;

    processing_info->input_buffer[buffer_index] = sample;


    // Indicies from current index down without going out of bounds
    // (e.g. with current index = 1: z={1, 0, 7, 6..} so that z[n] is
    // the corresponding index for x*z^-n)

    unsigned z[BUFFER_SIZE]; 
    for (int i = 0; i < BUFFER_SIZE; i++)
        z[i] = (-i + BUFFER_SIZE + buffer_index) % BUFFER_SIZE;


    // Apply filter

    emg_sample_t filtered_sample = 0;

    for (unsigned i = 0; i < filt_size; i++)
        filtered_sample += filt_b[i] * processing_info->input_buffer [ z[i] ];
    for (unsigned i = 1; i < filt_size; i++)
        filtered_sample -= filt_a[i] * processing_info->output_buffer[ z[i] ];

    processing_info->output_buffer[buffer_index] = filtered_sample;


    // Update current index after processing is complete

    processing_info->current_index = buffer_index;
}


emg_sample_t get_current_sample(processing_info_t * processing_info)
{
    return processing_info->output_buffer[processing_info->current_index];
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

    emg_sample_t sample = get_current_sample(processing_info);

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

