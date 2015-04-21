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
#define MAX_EMG_CHANNELS      3


// ---- Base sample type that signals will be read in as.

typedef float emg_sample_t; // NOTE: This is assuming that we're going to use
                            // float on the microcontroller. (I was assured it
                            // would be fine..)


// ---- Struct type to represent an emg signal from one sensor.

typedef struct emg_signal_t
{
    // Preallocated buffer of emg samples.
    emg_sample_t samples[MAX_EMG_SIGNAL_LENGTH];

    // Length of the actual signal.
    unsigned length;

} emg_signal_t;

void init_emg_signal(emg_signal_t * sig);


// ---- Struct types to represent a group of emg signals
//      coming from different sensors.

typedef struct emg_sample_group_t
{
    // Preallocated buffer of samples for each channel.
    emg_sample_t channels[MAX_EMG_CHANNELS];

    // Number of channels in this group.
    unsigned num_channels;

} emg_sample_group_t;

void init_emg_sample_group(
    emg_sample_group_t * sample_group,
    unsigned num_channels
);


typedef struct emg_signal_group_t
{
    // Preallocated buffer of signals for each channel.
    emg_signal_t channels[MAX_EMG_CHANNELS];

    // Number of channels in this group.
    unsigned num_channels;

    // Length of the smallest signal.
    unsigned length;

} emg_signal_group_t;

void init_emg_signal_group(
    emg_signal_group_t * signal_group,
    unsigned num_channels
);

void insert_sample_group(
    emg_signal_group_t * signal_group,
    emg_sample_group_t * sample_group,
    unsigned index
);


#endif
