//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_onset.h
//  flynn, michael
//
//  functions to detect the onset of motion of a given emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_ONSET_H
#define _EMG_ONSET_H

#include "emg_signal.h"
#include "constants.h"


bool onset_detected(emg_sample_t current_member);


#endif
