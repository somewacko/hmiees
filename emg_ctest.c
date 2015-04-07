//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_ctest.c
//  flynn, michael
//
//  program to test c files for emg processing and classification on a
//  microcontroller.
//
//  usage:
//      -feats         : Calculates features for the entire file up to
//                       MAX_EMG_SIGNAL_LENGTH.
//      -file {name}   : Specifies a 24-bit signed raw emg signal file to
//                       read in. (Required)
//      -frate {val}   : Gives the sampling rate of the file being read
//                       in. (Default 8000)
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


// ---- Message to display when used incorrectly

void print_usage()
{
    printf("\n"
        "Usage:\n"
        "\t-feats         : Calculates features for the entire file.\n"
        "\t-file {name}   : Specifies a 24-bit signed raw emg signal file to\n"
        "\t                 read in. (Required)\n"
        "\t-frate {val}   : Gives the sampling rate of the file being read\n"
        "\t                 in. (Default 8000)\n"
        "\t-speriod {val} : Specifies the sampling period to extract\n"
        "\t                 features from after onset of motion has been\n"
        "\t                 detected. (Default 200)\n"
        "\n");
    exit(0);
}


// ---- Parsing command line arguments

typedef struct emg_params_t
{
    bool feats;
    char filename[128];
    unsigned frate;
    unsigned speriod;
} emg_params_t;


emg_params_t parse_args(int argc, char *argv[])
{
    emg_params_t params = { false, "", 8000, 200 };

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-feats") == 0)
        {
            params.feats = true;
        }
        else if (strcmp(argv[i], "-file") == 0)
        {
            if (i+1 < argc)
                strcpy(params.filename, argv[++i]);
            else
                print_usage();
        }
        else if (strcmp(argv[i], "-frate") == 0)
        {
            if (i+1 < argc)
                params.frate = atoi(argv[++i]);
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

emg_sample_t get_24bit_sample(FILE * file, unsigned downsample_factor)
{
    emg_sample_t samples[downsample_factor];

    int32_t raw_sample = 0;

    // Read in D samples, return only the first one. (No filtering for now)

    for (unsigned i = 0; i < downsample_factor; i++)
    {
        fread(&raw_sample, 3, 1, file);

        if (raw_sample & 0x00800000)
            raw_sample |= 0xff000000;

        samples[i] = raw_sample / (emg_sample_t) pow(2,23);

        raw_sample = 0;
    }

    return samples[0];
}


// ---- Main entry

int main(int argc, char *argv[])
{
    emg_params_t params = parse_args(argc, argv);

    const unsigned d_factor = params.frate / SAMPLING_RATE;

    FILE *file = fopen(params.filename, "r");

    if (file == NULL)
    {
        printf("\nUnable to open file!\n\n");
        exit(0);
    }

    if (params.feats)
    {
        emg_signal_t sig;

        unsigned i = 0;

        while (!feof(file) && i < MAX_EMG_SIGNAL_LENGTH)
            sig.samples[i++] = get_24bit_sample(file, d_factor);

        sig.length = i;

        // Extract and print features from this test signal.

        printf("\nFeatures for first %u samples in %s:\n\n",
            sig.length, params.filename);
        printf("MAV  : %7.3f\n", extract_feature(&sig, emg_feat_MAV,  0    ));
        printf("VAR  : %7.3f\n", extract_feature(&sig, emg_feat_VAR,  0    ));
        printf("WAMP : %7.3f\n", extract_feature(&sig, emg_feat_WAMP, 0.006));
        printf("WL   : %7.3f\n", extract_feature(&sig, emg_feat_WL,   0    ));
        printf("ZC   : %7.3f\n", extract_feature(&sig, emg_feat_ZC,   0.004));
        printf("\n");
    }
    else
    {
        printf("\nReading in signal from %s...\n\n", params.filename);

        while (!feof(file))
            process_sample( get_24bit_sample(file, d_factor) );

        printf("\nFinished!\n\n");
    }

    fclose(file);    

    return 0;
}

