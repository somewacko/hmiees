//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_processing.h
//  flynn, michael
//
//  functions to manage the processing of an emg signal, including onset of
//  motion detection and feature extraction.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_PROCESSING_H
#define _EMG_PROCESSING_H
#define MAX_SIGNAL_NUMBER 3

#include "constants.h"
#include "emg_filter.h"
#include "emg_onset.h"
#include "emg_signal.h"


#define BUFFER_SIZE DOWNSAMPLING_FACTOR // = 8, 8000 Hz -> 1000 Hz


// ---- Struct type to hold all information for processing signals

typedef struct processing_info_t
{
    // Onset info for the incoming signals, one for each channel
    onset_info_t onset_info[MAX_EMG_CHANNELS];

    // How many samples to read in after onset is detected
    unsigned speriod;

} processing_info_t;


// ---- Initializes processing_info_t struct

void init_processing_info(
    processing_info_t * processing_info,
    unsigned speriod
);


// ---- Entry point for processing - onset detection, feature extraction, and
//      transmission.

void process_sample(
    processing_info_t * processing_info,
    emg_sample_group_t sample_group
);


#endif
