//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_gesture.c
//  flynn, michael
//
//  structs to hold information for different gesture classes and be able
//  to classify signals.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_gesture.h"

#include <float.h>
#include <stdio.h>
#include <string.h>


emg_gesture_t init_emg_gesture(
    char name[],
    unsigned num_features
){
    emg_gesture_t gesture = {
        .num_features   = num_features,
        .observations   = init_fmatrix(0, num_features),
        .inv_covariance = init_fmatrix(0, 0),
        .mean_obs       = init_fmatrix(0, 0),
        .is_committed   = false
    };

    strcpy(gesture.name, name);

    return gesture;
}


// ---- Training methods

void train_gesture(
    emg_gesture_t * gesture,
    fmatrix_t * features
){
    if (features->rows == 1) // Enforce features as a row vector
    {
        gesture->is_committed = false;

        unsigned num_obs = gesture->observations.rows;

        for (unsigned i = 0; i < gesture->num_features; i++)
            gesture->observations.values[num_obs][i] = features->values[0][i];

        gesture->observations.rows = num_obs + 1;
        gesture->observations.cols = gesture->num_features;
    }
}


void commit_training(
    emg_gesture_t * gesture
){
    // Calculate inverse covariance
    fmatrix_t cov = covariance_matrix(&gesture->observations);
    gesture->inv_covariance = inverted_matrix(&cov);

    // Calculate averages in observations
    gesture->mean_obs = average_columns_matrix(&gesture->observations);

    gesture->is_committed = true;
}


// ---- Classification methods

float mahal_distance(
    fmatrix_t * test,
    fmatrix_t * inv_cov,
    fmatrix_t * mean_obs
){
    // Mahalanobis distance:
    //
    //  D^2 = (x-u) * C^-1 * (x-u)^T
    //
    //  where:
    //      x - The test vector
    //      u - Vector of averages of the observations
    //      C - The covariance matrix of the observations
    //      T - Matrix transpose

    // Subtract averages from test vector
    fmatrix_t m = subtract_matricies(test, mean_obs);
    fmatrix_t m_t = transposed_matrix(&m);

    // Multiply down to 1x1 matrix
    fmatrix_t result;
    result = multiply_matricies(&m, inv_cov);
    result = multiply_matricies(&result, &m_t);

    return result.values[0][0];
}


emg_classification_info_t classify(
    fmatrix_t * features,
    emg_gesture_t gestures[],
    const unsigned num_gestures,
    float threshold
){
    emg_classification_info_t classification = {
        .identified_gesture = NULL,
        .distance = FLT_MAX
    };

    for (unsigned i = 0; i < num_gestures; i++)
    {
        // Commit training if not done already
        if (!gestures[i].is_committed)
            commit_training(&gestures[i]);

        float d = mahal_distance(
            features,
            &gestures[i].inv_covariance,
            &gestures[i].mean_obs
        );

        if (d < threshold && d < classification.distance)
        {
            classification.identified_gesture = &gestures[i];
            classification.distance = d;
        }
    }

    return classification;
}

