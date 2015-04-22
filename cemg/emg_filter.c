//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_filter.c
//  flynn, michael
//
//  provides methods for filtering an emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include <libq.h>

#include "emg_filter.h"


// ---- 7th-order butterworth filter coefficients to get cutoff frequency
//      of 500 Hz from 8000 Hz
//
//      matlab:
//
//      > [b, a] = butter(7, 2*500/8000);
//      > a =
//           1.0000000000  -5.2367698634  11.9272434137 -15.2840131998
//          11.8827420583  -5.5983497659   1.4785129329 - 0.1687178026
//      > b = 
//           0.0000050607   0.0000354251   0.0001062753   0.0001771255
//           0.0001771255   0.0001062753   0.0000354251   0.0000050607

#define FILTER_SIZE 8

_Q16 filt_a[FILTER_SIZE];
_Q16 filt_b[FILTER_SIZE];

void init_filters()
{
    filt_a[0] = _Q16ftoi(  1.0000000000);
    filt_a[1] = _Q16ftoi(- 5.2367698634);
    filt_a[2] = _Q16ftoi( 11.9272434137);
    filt_a[3] = _Q16ftoi(-15.2840131998);
    filt_a[4] = _Q16ftoi( 11.8827420583);
    filt_a[5] = _Q16ftoi(- 5.5983497659);
    filt_a[6] = _Q16ftoi(  1.4785129329);
    filt_a[7] = _Q16ftoi(- 0.1687178026);

    filt_b[0] = _Q16ftoi(  0.0000050607);
    filt_b[1] = _Q16ftoi(  0.0000354251);
    filt_b[2] = _Q16ftoi(  0.0001062753);
    filt_b[3] = _Q16ftoi(  0.0001771255);
    filt_b[4] = _Q16ftoi(  0.0001771255);
    filt_b[5] = _Q16ftoi(  0.0001062753);
    filt_b[6] = _Q16ftoi(  0.0000354251);
    filt_b[7] = _Q16ftoi(  0.0000050607);
}


void filter_sample_group(_Q16 sample_group[MAX_EMG_CHANNELS])
{
    static _Q16 input_buffers [MAX_EMG_CHANNELS][BUFFER_SIZE];
    static _Q16 output_buffers[MAX_EMG_CHANNELS][BUFFER_SIZE];
    static short unsigned z[BUFFER_SIZE];
    static short unsigned buffer_index;

    // Put sample in input buffer

    for (int n = 0; n < MAX_EMG_CHANNELS; n++)
        input_buffers[n][buffer_index] = sample_group[n];


    // Indicies from current index down without going out of bounds
    // (e.g. with current index = 1: z={1, 0, 7, 6..} so that z[n] is
    // the corresponding index for x*z^-n)

    for (int i = 0; i < BUFFER_SIZE; i++)
        z[i] = (-i + BUFFER_SIZE + buffer_index) % BUFFER_SIZE;


    // Apply the filter

    for (int n = 0; n < MAX_EMG_CHANNELS; n++)
    {
        _Q16 filtered_sample = 0;

        // OPTIMIZATION: Unroll these loops?

//        for (int i = 0; i < FILTER_SIZE; i++)
//            filtered_sample += n * input_buffers[n][i];
//        for (int i = 0; i < FILTER_SIZE; i++)
//            filtered_sample += n * output_buffers[n][i];

        for (int i = 0; i < FILTER_SIZE; i++)
            filtered_sample += _Q16mpy(filt_b[i], input_buffers [n][ z[i] ]);
        for (int i = 1; i < FILTER_SIZE; i++)
            filtered_sample -= _Q16mpy(filt_a[i], output_buffers[n][ z[i] ]);

        // Overwrite current sample with result and put in buffer
        output_buffers[n][buffer_index] = sample_group[n] = filtered_sample;
    }


    // Increment the index

    buffer_index++;
    if (buffer_index >= BUFFER_SIZE)
        buffer_index = 0;
}

