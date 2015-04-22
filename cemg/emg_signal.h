//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_signal.h
//  flynn, michael
//
//  definitions for representing emg signals.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_SIGNAL_H
#define _EMG_SIGNAL_H


#define MAX_EMG_SIGNAL_LENGTH 150
#define MAX_EMG_CHANNELS      2


// ---- Base sample type that signals will be read in as.

typedef float emg_sample_t; // NOTE: This is assuming that we're going to use
                            // float on the microcontroller. (I was assured it
                            // would be fine..)


// ---- Types to represent groups of signals, into channels or streams.

typedef emg_sample_t emg_signal_t[MAX_EMG_SIGNAL_LENGTH];

typedef emg_sample_t emg_sample_group_t[MAX_EMG_CHANNELS];

typedef emg_sample_t
    emg_signal_group_t[MAX_EMG_CHANNELS][MAX_EMG_SIGNAL_LENGTH];

void init_emg_signal(emg_signal_t sig);
void init_emg_sample_group(emg_sample_group_t sample_group);
void init_emg_signal_group(emg_signal_group_t signal_group);


#endif
