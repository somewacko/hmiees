//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_classifier.h
//  flynn, michael
//
//  functions to classify a given set of features from an emg signal as a
//  known gesture.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#ifndef _EMG_CLASSIFIER_H
#define _EMG_CLASSIFIER_H

#include "emg_gesture.h"
#include "emg_matrix.h"

float mahal_distance(
    fmatrix_t * test,
    fmatrix_t * observations
);

emg_gesture_t * classify(
    fmatrix_t * features,
    emg_gesture_t * gestures[],
    float threshold
);

#endif
