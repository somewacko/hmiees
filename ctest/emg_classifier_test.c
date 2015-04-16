//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_classifier_test.h
//  flynn, michael
//
//  program to test classifier with randomly generated sets.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "classifier_constants.h"
#include "emg_gesture.h"
#include "emg_matrix.h"


float rand_float() // Returns a float between 0 and 1
{
    return rand() / (float)RAND_MAX; 
}


void print_matlab(fmatrix_t * a)
{
    // Prints the array to easily be copy/pasted into matlab

    printf("\n[");
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            printf("%f", a->values[i][j]);
            if (j != a->cols-1)
                printf(",");
        }
        if (i != a->rows-1)
            printf(";");
    }
    printf("]\n\n");
}


int main(void)
{
    srand(time(NULL));

    fmatrix_t a = init_fmatrix(10, 5);

    for (int i = 0; i < a.rows; i++)
        for (int j = 0; j < a.cols; j++)
            a.values[i][j] = rand_float();

    printf("a:\n");
    print_matrix(&a);
    print_matlab(&a);

    fmatrix_t c = covariance_matrix(&a);
    c = inverted_matrix(&c);

    printf("inv(cov(a)):\n");
    print_matrix(&c);

    return 0;
}
