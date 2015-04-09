//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_filter.h
//  flynn, michael
//
//  provides methods for filtering an emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //


#include "constants.h"
#include "emg_signal.h"


#define BUFFER_SIZE DOWNSAMPLING_FACTOR // = 8, 8000 Hz -> 1000 Hz


// ---- Struct to hold filter buffers

typedef struct emg_filter_buffer_t {

    // Buffers for read-in and filtered samples
    emg_sample_t input_buffer [BUFFER_SIZE];
    emg_sample_t output_buffer[BUFFER_SIZE];

    // The "head" of the buffer
    unsigned current_index;

} emg_filter_buffer_t;


// ---- Initializes emg_filter_buffer_t struct.

emg_filter_buffer_t init_filter_buffer();


// ---- Inserts a sample into the buffer and filters it.

void insert_sample(emg_filter_buffer_t * buffer, emg_sample_t sample);


// ---- Method to get the current filtered sample from a filter buffer.

emg_sample_t get_current_sample(emg_filter_buffer_t * buffer);

