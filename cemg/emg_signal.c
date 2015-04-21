//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_signal.c
//  flynn, michael
//
//  definitions for representing emg signals.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_signal.h"


void init_emg_signal(emg_signal_t * sig)
{
    unsigned i;
    sig->length = 0;

    for (i = 0; i < MAX_EMG_SIGNAL_LENGTH; i++)
        sig->samples[i] = 0;
}


void init_emg_sample_group(
    emg_sample_group_t * sample_group,
    unsigned num_channels
){
    unsigned i;

    sample_group->num_channels = num_channels > MAX_EMG_CHANNELS ? MAX_EMG_CHANNELS : num_channels;

    for (i = 0; i < MAX_EMG_CHANNELS; i++)
        sample_group->channels[i] = 0;
}


void init_emg_signal_group(
    emg_signal_group_t * signal_group,
    unsigned num_channels
){
    unsigned i;

    signal_group->num_channels = num_channels > MAX_EMG_CHANNELS ? MAX_EMG_CHANNELS : num_channels;

    for (i = 0; i < MAX_EMG_CHANNELS; i++)
        init_emg_signal(&signal_group->channels[i]);
}


void insert_sample_group(
    emg_signal_group_t * signal_group,
    emg_sample_group_t * sample_group,
    unsigned index
){
    unsigned n;
    for (n = 0; n < signal_group->num_channels; n++)
        signal_group->channels[n].samples[index] = sample_group->channels[n];
}

