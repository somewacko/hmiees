//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_ctest.c
//  flynn, michael
//
//  program to test c files for emg processing and classification on a
//  microcontroller.
//
//  usage:
//      -file {name}   : Specifies a 24-bit signed raw emg signal file to
//                       read in. (Required)
//      -speriod {val} : Specifies the sampling period to extract 
//                       features from after onset of motion has been
//                       detected. (Default 200)
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cemg/constants.h"
#include "cemg/emg_features.h"
#include "cemg/emg_onset.h"
#include "cemg/emg_processing.h"
#include "cemg/emg_signal.h"

#define __CEMG_TEST__


// ---- Message to display when used incorrectly

void print_usage()
{
    printf("\n"
        "Usage:\n"
        "\t-file {name}   : Specifies a 24-bit signed raw emg signal file to\n"
        "\t                 read in. (Required)\n"
        "\t-speriod {val} : Specifies the sampling period to extract\n"
        "\t                 features from after onset of motion has been\n"
        "\t                 detected. (Default 200)\n"
        "\n");
    exit(0);
}


// ---- Parsing command line arguments

typedef struct emg_params_t
{
    char filename[128];
    unsigned speriod;
} emg_params_t;


emg_params_t parse_args(int argc, char *argv[])
{
    emg_params_t params = { "", 200 };

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-file") == 0)
        {
            if (i+1 < argc)
                strcpy(params.filename, argv[++i]);
            else
                print_usage();
        }
        else if (strcmp(argv[i], "-s") == 0
            || strcmp(argv[i], "-speriod") == 0)
        {
            if (i+1 < argc)
                params.speriod = atoi(argv[++i]);
            else
                print_usage();
        }
        else
            print_usage();
    }

    return params;
}


// ---- Reading in file

emg_sample_t get_24bit_sample(FILE * file)
{
    int32_t raw_sample = 0;

    // Read in 24-bit signed integer
    fread(&raw_sample, 3, 1, file);

    // If negative, pad the top byte with 1's (24 -> 32 bit)
    if (raw_sample & 0x00800000)
        raw_sample |= 0xff000000;

    // Normalize between -1 and 1
    return raw_sample / (emg_sample_t) pow(2,23);
}


// ---- Main entry

int main(int argc, char *argv[])
{
    emg_params_t params = parse_args(argc, argv);


    processing_info_t processing_info = init_processing_info(params.speriod);


    FILE *file = fopen(params.filename, "r");

    if (file == NULL)
    {
        printf("\nUnable to open file!\n\n");
        exit(0);
    }


    printf("\nReading in signal from %s...\n\n", params.filename);

    while (!feof(file))
    {
        for (int i = 0; i < DOWNSAMPLING_FACTOR && !feof(file); i++)
            read_in_sample(&processing_info, get_24bit_sample(file));

        process_sample(&processing_info);
    }

    printf("\nFinished!\n\n");


    fclose(file);


    return 0;
}

