//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_onset.h
//  flynn, michael / drew simmons / stefan sharpley
//
//  functions to detect the onset of motion of a given emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_ONSET_H
#define _EMG_ONSET_H

#include <stdbool.h>

#include "emg_signal.h"
#include "constants.h"


typedef struct onset_info_t {

    // Counting variable to establish base variance in first N samples
    unsigned base_var_count;
    
    // Whether or not motion is active
    bool is_active;

    // The base variance to adjust threshold with
    float base_variance, base_mean, base_sq_mean;

    // The last sample read in
    emg_sample_t prev_sample;

    // Counts for the Bonato algorithm
    int n_of_m, active_count, off_count;
    bool is_even;

} onset_info_t;


void init_onset_info(onset_info_t * onset_info);

bool onset_detected(
    onset_info_t onset_infos[MAX_EMG_CHANNELS],
    emg_sample_group_t sample_group
);
bool onset_detected_in_channel(
    onset_info_t * onset_info,
    emg_sample_t sample
);


#endif
