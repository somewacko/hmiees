//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_classifier_test.c
//  flynn, michael
//
//  program to test classifier with randomly generated vectors.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "classifier_constants.h"
#include "emg_gesture.h"
#include "emg_matrix.h"


float rand_float() 
{
    // Returns a float between 0 and 1
    return rand() / (float)RAND_MAX; 
}


int main(void)
{
    srand(time(NULL));

    printf("\nTesting emg classifier using randomly generated vectors...\n\n");


    const unsigned num_features = MAX_CHANNELS * NUM_FEATURES;
    const unsigned num_obs      = 2 * num_features;
    const unsigned num_gestures = 3;


    emg_gesture_t gesture_A = init_emg_gesture("Gesture A", num_features);
    emg_gesture_t gesture_B = init_emg_gesture("Gesture B", num_features);
    emg_gesture_t gesture_C = init_emg_gesture("Gesture C", num_features);

    emg_gesture_t * gestures[] = { &gesture_A, &gesture_B, &gesture_C };


    fmatrix_t m = init_fmatrix(1, num_features);

    for (unsigned n = 0; n < num_gestures; n++)
    {
        for (unsigned i = 0; i < num_obs; i++)
        {
            for (unsigned j = 0; j < num_features; j++)
                m.values[0][j] = 2*n + rand_float()*(j+1);
            train_gesture(gestures[n], &m);
        }
        commit_training(gestures[n]);
    }
    

    fmatrix_t test_a = init_fmatrix(1, num_features);
    for (unsigned i = 0; i < num_features; i++)
        test_a.values[0][i] = 2*0 + rand_float()*(i+1);

    fmatrix_t test_b = init_fmatrix(1, num_features);
    for (unsigned i = 0; i < num_features; i++)
        test_b.values[0][i] = 2*1 + rand_float()*(i+1);

    fmatrix_t test_c = init_fmatrix(1, num_features);
    for (unsigned i = 0; i < num_features; i++)
        test_c.values[0][i] = 2*2 + rand_float()*(i+1);

    fmatrix_t test_x = init_fmatrix(1, num_features);
    for (unsigned i = 0; i < num_features; i++)
        test_x.values[0][i] = 10 + rand_float()*(i+1);


    float threshold = 1000.f;
    classification_info_t info;

    info = classify(&test_a, gestures, num_gestures, threshold);
    printf("Test a classified as %12s with distance^2: %0.2f\n",
        info.identified_gesture ? info.identified_gesture->name : "[no gesture]",
        info.distance);

    info = classify(&test_b, gestures, num_gestures, threshold);
    printf("Test b classified as %12s with distance^2: %0.2f\n",
        info.identified_gesture ? info.identified_gesture->name : "[no gesture]",
        info.distance);

    info = classify(&test_c, gestures, num_gestures, threshold);
    printf("Test c classified as %12s with distance^2: %0.2f\n",
        info.identified_gesture ? info.identified_gesture->name : "[no gesture]",
        info.distance);

    info = classify(&test_x, gestures, num_gestures, threshold);
    printf("Test x classified as %12s with distance^2: %0.2f\n",
        info.identified_gesture ? info.identified_gesture->name : "[no gesture]",
        info.distance);

    printf("\n");


    return 0;
}
