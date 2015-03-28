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
        "\t-feats         : Tests features with generated signals.\n"
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


// ---- Testing features

void test_features()
{
    // Generate a sawtooth signal from ~ -1 to 1 with
    // a period of 10 samples

    emg_signal_t sig;
    sig.length = 100;

    printf("\nTesting signal:\n\n");

    for (int i = 0; i < sig.length; i++)
    {
        sig.samples[i] = (i%10-5)/(emg_sample_t)5;
        printf("%5.2f ", sig.samples[i]);
    }
    
    // Extract and print features from this test signal.

    printf("\n\n");
    printf("MAV  : %7.2f\n", extract_feature(&sig, emg_feat_MAV,  0   ));
    printf("VAR  : %7.2f\n", extract_feature(&sig, emg_feat_VAR,  0   ));
    printf("WAMP : %7.2f\n", extract_feature(&sig, emg_feat_WAMP, 0.05));
    printf("WL   : %7.2f\n", extract_feature(&sig, emg_feat_WL,   0   ));
    printf("ZC   : %7.2f\n", extract_feature(&sig, emg_feat_ZC,   0.10));
    printf("\n");
}


// ---- Main entry

int main(int argc, char *argv[])
{
    emg_params_t params = parse_args(argc, argv);

    printf("filename: %s\n", params.filename);
    printf("frate:    %d\n", params.frate);
    printf("speriod:  %d\n", params.speriod);

    // Test features with generated 

    if (params.feats)
        test_features();

    return 0;
}

