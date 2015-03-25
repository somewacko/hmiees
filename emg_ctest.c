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
//      -frate {val}   : Gives the sampling rate of the file being read
//                       in. (Default 8000)
//      -speriod {val} : Specifies the sampling period to extract 
//                       features from after onset of motion has been
//                       detected. (Default 200)
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cemg/emg_features.h"
#include "cemg/emg_onset.h"
#include "cemg/emg_processing.h"
#include "cemg/emg_signal.h"


// ---- Message to display when used incorrectly

void print_usage()
{
    printf("\n"
        "Usage:\n"
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
    char filename[128];
    unsigned frate;
    unsigned speriod;
} emg_params_t;


emg_params_t parse_args(int argc, char *argv[])
{
    emg_params_t params = { "", 8000, 200 };

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-file") == 0)
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


// ---- Main entry

int main(int argc, char *argv[])
{
    emg_params_t params = parse_args(argc, argv);

    printf("filename: %s\n", params.filename);
    printf("frate:    %d\n", params.frate);
    printf("speriod:  %d\n", params.speriod);

    return 0;
}

