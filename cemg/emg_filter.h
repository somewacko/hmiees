//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_filter.h
//  flynn, michael
//
//  provides methods for filtering an emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_FILTER_H
#define _EMG_FILTER_H

#include <libq.h>

#include "constants.h"
#include "emg_signal.h"


#define BUFFER_SIZE DOWNSAMPLING_FACTOR // = 8, 8000 Hz -> 1000 Hz

void init_filters();
void filter_sample_group(_Q16 sample_group[MAX_EMG_CHANNELS]);

#endif
