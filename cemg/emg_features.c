//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_features.c
//  flynn, michael
//
//  functions to extract and organize features from a given emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_features.h"

#include <math.h>
#include <stdlib.h>


float extract_feature(emg_signal_t sig, emg_feature_t feat, float param)
{
    switch (feat)
    {
        case emg_feat_MAV:
            return mean_absolute_value(sig);
        case emg_feat_VAR:
            return variance(sig);
        case emg_feat_WAMP:
            return wilson_amplitude(sig, param);
        case emg_feat_WL:
            return waveform_length(sig);
        case emg_feat_ZC:
            return zero_crossings(sig, param);
        default:
            return 0;
    }
}


float mean_absolute_value(emg_signal_t sig)
{
    float mav = 0.f;
    
    for (int i = 0; i < MAX_EMG_SIGNAL_LENGTH; i++)
        mav += fabs(sig[i]) / (float)MAX_EMG_SIGNAL_LENGTH;

    return mav;
}


float variance(emg_signal_t sig)
{
    float mean = 0.f, sq_mean = 0.f;

    for (int i = 0; i < MAX_EMG_SIGNAL_LENGTH; i++)
    {
        emg_sample_t s = sig[i];

        mean    +=   s   / (float)MAX_EMG_SIGNAL_LENGTH;
        sq_mean += (s*s) / (float)MAX_EMG_SIGNAL_LENGTH;
    }

    return sq_mean - mean * mean;
}


float wilson_amplitude(emg_signal_t sig, float threshold)
{
    unsigned count = 0;
    const int N = MAX_EMG_SIGNAL_LENGTH - 1;

    for (int i = 0; i < N; i++)
        if ( fabs(sig[i]-sig[i+1]) >= threshold )
            count++;

    return count;
}


float waveform_length(emg_signal_t sig)
{
    float wl = 0;

    for (int i = 1; i < MAX_EMG_SIGNAL_LENGTH; i++)
        wl += fabs(sig[i] - sig[i-1]);

    return wl;
}


float zero_crossings(emg_signal_t sig, float threshold)
{
    unsigned count = 0;
    const int N = MAX_EMG_SIGNAL_LENGTH - 1;

    for (int i = 0; i < N; i++)
        if (fabs(sig[i] - sig[i+1]) >= threshold)
            if ((-sig[i] * sig[i+1]) > 0)
                count++;

    return count;
}


char * feature_name(emg_feature_t feat)
{
    switch (feat)
    {
        case emg_feat_MAV:
            return "MAV ";
        case emg_feat_VAR:
            return "VAR ";
        case emg_feat_WAMP:
            return "WAMP";
        case emg_feat_WL:
            return "WL  ";
        case emg_feat_ZC:
            return "ZC  ";
        default:
            return "FEAT";
    }
}

