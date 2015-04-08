//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  constants.h
//  flynn, michael
//
//  constants and utility types for the program.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

typedef enum { false, true } bool;

#define SAMPLING_RATE       8000 // Read in signals at 8000 Hz
#define DOWNSAMPLING_FACTOR    8 // Downsample incoming signal by 8 to 1000 Hz

#endif
