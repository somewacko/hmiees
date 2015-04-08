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

#include "constants.h"
#include "emg_signal.h"


#define BUFFER_SIZE DOWNSAMPLING_FACTOR // = 8, 8000 Hz -> 1000 Hz


// ---- Struct type to hold all information for processing signals

typedef struct processing_info_t
{
    // Buffers for read-in and filtered samples
    emg_sample_t input_buffer[BUFFER_SIZE];
    emg_sample_t output_buffer[BUFFER_SIZE];

    // The "head" of the buffer
    unsigned current_index;

    // How many samples to read in after onset is detected
    unsigned speriod;

} processing_info_t;


// ---- Initializes processing_info_t struct

processing_info_t init_processing_info(unsigned speriod);


// ---- Reads in a sample and adds it to the buffer in processing info after
//      filtering. Have an interrupt call this method to read in samples.

void read_in_sample(processing_info_t * processing_info, emg_sample_t sample);


// ---- Gets the current sample from the info struct.

emg_sample_t get_current_sample(processing_info_t * processing_info);


// ---- Entry point for processing - onset detection, feature extraction, and
//      transmission.

void process_sample(processing_info_t * processing_info);


#endif
