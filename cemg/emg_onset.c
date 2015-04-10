//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_onset.c
//  flynn, michael / drew simmons / stefan sharpley
//
//  functions to detect the onset of motion of a given emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_onset.h"

#include "emg_processing.h"

#include <stdio.h>


onset_info_t init_onset_info()
{
    onset_info_t onset_info = {
        .base_var_count  = 0,
        .is_active       = false,
        .base_variance   = 0,
        .base_mean       = 0,
        .base_sq_mean    = 0,
        .prev_sample     = 0,

        .n_of_m          = 0,
        .active_count    = 0,
        .off_count       = 0,
        .is_even         = false
    };

    return onset_info;
}


bool onset_detected(
    onset_info_t onset_infos[],
    unsigned onset_infos_length,
    emg_sample_group_t * sample_group
){
    bool onset = false;

    for (int i = 0; i < onset_infos_length; i++)
    {
        onset = onset || onset_detected_in_channel(
            &onset_infos[i], sample_group->channels[i]
        );
    }

    return onset;
}


bool onset_detected_in_channel(
    onset_info_t * info,
    emg_sample_t sample
){
    const int M  = 1000, // Number of "no motion" samples to set base variance.
              n  = 1,    // Number of above threshold samples out of m samples.
              m  = 12,   // Number of samples in window.
              T1 = 20;   // Number of successive windows to achieve "onset".

    const float h = 40.f; // Threshold value to detect onset.


    if (info->base_var_count < M) 
    {
        // Find base variance in the first M samples

        info->base_mean    +=      sample       / (float) M;
        info->base_sq_mean += (sample * sample) / (float) M;

        if (++info->base_var_count == M)
        {
            info->base_variance = info->base_sq_mean
                - info->base_mean * info->base_mean; 
        }
    }
    else if (info->is_even)
    {               
        // Check for onset every other sample

        float sq_sample = sample * sample;
        float sq_prev_sample = info->prev_sample * info->prev_sample;

        float g = (1 / info->base_variance) * (sq_sample + sq_prev_sample);
    
        if (g >= h)
        {
            info->n_of_m += 1;

            if (info->n_of_m >= m)
                info->n_of_m = m;       
        }
        else
        {
            info->n_of_m -= 1;

            if (info->n_of_m <= 0)
                info->n_of_m = 0;
        }
        
        if (!info->is_active)
        {
            if (info->n_of_m >= n)
                info->active_count += 1;
            else
                info->active_count = 0; 

            if (info->active_count >= T1)
                info->is_active = true;
        }
        else
        {
            if (info->n_of_m < n)
                info->off_count += 1;
            else
                info->off_count = 0;
            
            if (info->off_count >= T1)
                info->is_active = false;          
        }
    }

    info->is_even = !info->is_even;
    info->prev_sample = sample;

    return info->is_active;
}

