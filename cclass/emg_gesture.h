//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_gesture.c
//  flynn, michael
//
//  structs to hold information for different gesture classes and be able
//  to classify signals.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_GESTURE_H
#define _EMG_GESTURE_H

#include "classifier_constants.h"
#include "emg_matrix.h"


#define MAX_CHAR 32


// ---- Struct to represent a gesture and hold training information for it.

typedef struct emg_gesture_t
{
    // The number of features that will be read in.
    unsigned num_features;

    // Matrix of features from signals of this gesture.
    fmatrix_t observations;

    // The inverse covariance matrix derived from the observations.
    fmatrix_t inv_covariance;

    // Vector of averages of each column in the observation matrix.
    fmatrix_t mean_obs;

    // Whether or not the covariance matrix is updated.
    bool is_committed;

    // The name of this gesture.
    char name[MAX_CHAR];

} emg_gesture_t;

emg_gesture_t init_emg_gesture(char name[], unsigned num_features);


// ---- Small object that holds results of classification

typedef struct emg_classification_info_t
{
    emg_gesture_t * identified_gesture;
    float distance;
} emg_classification_info_t;


// ---- Training methods

// Adds a vector of features to the observation matrix.
void train_gesture(emg_gesture_t * gesture, fmatrix_t * features);

// Performs calculations to assist with classification.
void commit_training(emg_gesture_t * gesture);


// ---- Classification methods

// Metric used for classification.
float mahal_distance(
    fmatrix_t * test,
    fmatrix_t * inv_cov,
    fmatrix_t * mean_obs
);

// Perform classification, returns the recognized gesture or NULL if none.
emg_classification_info_t classify(
    fmatrix_t * features,
    emg_gesture_t gestures[],
    const unsigned num_gestures,
    float threshold
);


#endif
