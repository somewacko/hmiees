//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_features.h
//  flynn, michael
//
//  functions to extract and organize features from a given emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_FEATURES_H
#define _EMG_FEATURES_H

#include "emg_signal.h"

typedef enum emg_feature_t
{
    emg_feat_MAV,
    emg_feat_VAR,
    emg_feat_WAMP,
    emg_feat_WL,
    emg_feat_ZC,
    emg_feature_count
} emg_feature_t;

// Dynamic function that will calculate the feature
// indicated by emg_feature_t

float extract_feature(emg_signal_t *sig, emg_feature_t feat, float param);

// Functions for calculating individual features

float mean_absolute_value(emg_signal_t *sig);
float variance(emg_signal_t *sig);
float wilson_amplitude(emg_signal_t *sig, float threshold);
float waveform_length(emg_signal_t *sig);
float zero_crossings(emg_signal_t *sig, float threshold);

// Get the name of the feature

char * feature_name(emg_feature_t feat);

#endif
