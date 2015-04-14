//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_classifier.c
//  flynn, michael
//
//  functions to classify a given set of features from an emg signal as a
//  known gesture.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_classifier.h"

#include <stdlib.h>
#include <stdio.h>


float mahal_distance(fmatrix_t * test, fmatrix_t * observations)
{
    // D^2 = (t-u)^T * C^-1 * (t-u)

    fmatrix_t mean = average_columns_matrix(observations);

    fmatrix_t m = subtract_matricies(test, &mean);
    fmatrix_t m_t = transposed_matrix(&m);

    fmatrix_t cov = covariance_matrix(observations);
    fmatrix_t inv_cov = inverted_matrix(&cov);

    // Multiply down to 1x1 matrix
    fmatrix_t result;
    result = multiply_matricies(&m, &inv_cov);
    result = multiply_matricies(&result, &m_t);

    return result.values[0][0];
}


emg_gesture_t * classify(
    fmatrix_t * features,
    emg_gesture_t * gestures[],
    float threshold
){
    return NULL;
}

