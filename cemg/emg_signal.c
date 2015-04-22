//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_signal.c
//  flynn, michael
//
//  definitions for representing emg signals.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_signal.h"


void init_emg_signal(emg_signal_t sig)
{
    for (int i = 0; i < MAX_EMG_SIGNAL_LENGTH; i++)
        sig[i] = 0;
}


void init_emg_sample_group(emg_sample_group_t sample_group)
{
    for (int n = 0; n < MAX_EMG_CHANNELS; n++)
        sample_group[n] = 0;
}


void init_emg_signal_group(emg_signal_group_t signal_group)
{
    for (int n = 0; n < MAX_EMG_CHANNELS; n++)
        for (int i = 0; i < MAX_EMG_SIGNAL_LENGTH; i++)
            signal_group[n][i] = 0;
}

