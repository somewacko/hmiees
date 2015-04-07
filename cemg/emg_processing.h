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

#include "emg_signal.h"

void process_sample(emg_sample_t sample);

#endif
