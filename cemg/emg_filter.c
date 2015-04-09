//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_filter.c
//  flynn, michael
//
//  provides methods for filtering an emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_filter.h"


// ---- 7th-order butterworth filter coefficients to get cutoff frequency
//      of 500 Hz from 8000 Hz
//
//      matlab:
//
//      > [b, a] = butter(7, 2*1000/8000);
//      > a =
//           1.0000000000  -5.2367698634  11.9272434137 -15.2840131998
//          11.8827420583  -5.5983497659   1.4785129329 - 0.1687178026
//      > b = 
//           0.0000050607   0.0000354251   0.0001062753   0.0001771255
//           0.0001771255   0.0001062753   0.0000354251   0.0000050607

static const unsigned filt_size = 8;

static const float filt_a[] = {
     1.0000000000, - 5.2367698634,
    11.9272434137, -15.2840131998,
    11.8827420583, - 5.5983497659,
     1.4785129329, - 0.1687178026
};

static const float filt_b[] = {
     0.0000050607,   0.0000354251,
     0.0001062753,   0.0001771255,
     0.0001771255,   0.0001062753, 
     0.0000354251,   0.0000050607
};


// ---- Methods

emg_filter_buffer_t init_filter_buffer()
{
    emg_filter_buffer_t buffer = {
        .current_index = 0
    };

    for (unsigned i = 0; i < BUFFER_SIZE; i++)
    {
        buffer.input_buffer[i]  = 0;
        buffer.output_buffer[i] = 0;
    }

    return buffer;
}


void insert_sample(emg_filter_buffer_t * buffer, emg_sample_t sample)
{
    // Determine the current index in the buffer and put in input buffer

    unsigned buffer_index = buffer->current_index + 1 >= BUFFER_SIZE ?
        0 : buffer->current_index + 1;

    buffer->input_buffer[buffer_index] = sample;


    // Indicies from current index down without going out of bounds
    // (e.g. with current index = 1: z={1, 0, 7, 6..} so that z[n] is
    // the corresponding index for x*z^-n)

    unsigned z[BUFFER_SIZE]; 
    for (int i = 0; i < BUFFER_SIZE; i++)
        z[i] = (-i + BUFFER_SIZE + buffer_index) % BUFFER_SIZE;


    // Apply filter

    emg_sample_t filtered_sample = 0;

    for (unsigned i = 0; i < filt_size; i++)
        filtered_sample += filt_b[i] * buffer->input_buffer [ z[i] ];
    for (unsigned i = 1; i < filt_size; i++)
        filtered_sample -= filt_a[i] * buffer->output_buffer[ z[i] ];

    buffer->output_buffer[buffer_index] = filtered_sample;


    // Update current index after processing is complete

    buffer->current_index = buffer_index;
}


emg_sample_t get_current_sample(emg_filter_buffer_t * buffer)
{
    return buffer->output_buffer[buffer->current_index];
}

