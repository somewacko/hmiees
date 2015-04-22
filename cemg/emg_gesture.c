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
    // Enforce features as a row vector and ensure that there is room for it
    if (features->rows == 1 && gesture->observations.cols < MAX_MATRIX_ROWS)
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
    fmatrix_t boxcox = boxcox_transform(&gesture->observations, BOXCOX_LAMBDA);

    // Calculate inverse covariance
    fmatrix_t cov = covariance_matrix(&boxcox);
    gesture->inv_covariance = inverted_matrix(&cov);

    // Calculate averages in observations
    gesture->mean_obs = average_columns_matrix(&boxcox);

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


classification_info_t classify(
    fmatrix_t * features,
    emg_gesture_t * gestures[],
    const unsigned num_gestures,
    float threshold
){
    // Classify a vector of features by calculating the Mahal distance for
    // each gesture and choosing the gesture with the shortest distance.

    // If no gesture has a distance below the given threshold,
    // emg_classification_info_t.identified_gesture will be NULL

    fmatrix_t bcfeats = boxcox_transform(features, BOXCOX_LAMBDA);

    classification_info_t info = {
        .identified_gesture = NULL,
        .distance = FLT_MAX
    };

    for (unsigned i = 0; i < num_gestures; i++)
    {
        // Ignore gestures which don't have enough training to classify.
        if (gestures[i]->observations.rows < gestures[i]->observations.cols)
            continue;

        // Commit training if not done already
        if (!gestures[i]->is_committed)
            commit_training(gestures[i]);

        float d = mahal_distance(
            &bcfeats,
            &gestures[i]->inv_covariance,
            &gestures[i]->mean_obs
        );

        if (d < threshold && d < info.distance)
        {
            info.identified_gesture = gestures[i];
            info.distance = d;
        }
    }

    if (!info.identified_gesture)
        info.distance = 0;

    return info;
}

