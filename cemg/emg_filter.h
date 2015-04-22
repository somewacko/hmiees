//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_filter.h
//  flynn, michael
//
//  provides methods for filtering an emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_FILTER_H
#define _EMG_FILTER_H

#include "constants.h"
#include "emg_signal.h"


#define BUFFER_SIZE DOWNSAMPLING_FACTOR // = 8, 8000 Hz -> 1000 Hz

void filter_sample_group(emg_sample_group_t sample_group);

#endif
