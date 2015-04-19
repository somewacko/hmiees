//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  constants.h
//  flynn, michael
//
//  constants!
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define SAMPLING_RATE       8000 // Read in signals at 8000 Hz
#define DOWNSAMPLING_FACTOR    8 // Downsample incoming signal by 8 to 1000 Hz

// Configurable

extern unsigned MAX_CHANNELS;
extern unsigned NUM_FEATURES;

extern float BOXCOX_LAMBDA;

#endif
