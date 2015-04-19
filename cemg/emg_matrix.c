//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_matrix.c
//  flynn, michael
//
//  represeting matricies and performing operations
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_matrix.h"

#include <math.h>
#include <stdio.h>


fmatrix_t init_fmatrix(unsigned rows, unsigned cols)
{
    fmatrix_t a = { .rows = rows, .cols = cols };
    clear_matrix(&a);
    return a;
}


void clear_matrix(fmatrix_t * a)
{
    for (unsigned i = 0; i < MAX_MATRIX_COLS; i++)
        for (unsigned j = 0; j < MAX_MATRIX_ROWS; j++)
            a->values[i][j] = 0;
}


void copy_matrix(fmatrix_t * dest, fmatrix_t * a)
{
    dest->rows = a->rows;
    dest->cols = a->cols;

    for (unsigned i = 0; i < a->rows; i++)
        for (unsigned j = 0; j < a->cols; j++)
            dest->values[i][j] = a->values[i][j];
}


fmatrix_t add_matricies(fmatrix_t * a, fmatrix_t * b)
{
    fmatrix_t result;

    if (a->rows == b->rows && a->cols == b->cols)
    {
        result.rows = a->rows;
        result.cols = a->cols;

        for (unsigned i = 0; i < result.rows; i++)
            for (unsigned j = 0; j < result.cols; j++)
                result.values[i][j] = a->values[i][j] + b->values[i][j];
    }
    else
    {
        result.rows = 0;
        result.cols = 0;
    }

    return result;
}


fmatrix_t subtract_matricies(fmatrix_t * a, fmatrix_t * b)
{
    fmatrix_t result;

    if (a->rows == b->rows && a->cols == b->cols)
    {
        result.rows = a->rows;
        result.cols = a->cols;

        for (unsigned i = 0; i < result.rows; i++)
            for (unsigned j = 0; j < result.cols; j++)
                result.values[i][j] = a->values[i][j] - b->values[i][j];
    }
    else
    {
        result.rows = 0;
        result.cols = 0;
    }

    return result;
}


fmatrix_t multiply_matricies(fmatrix_t * a, fmatrix_t * b)
{
    fmatrix_t result;

    if (a->cols == b->rows)
    {
        result.rows = a->rows;
        result.cols = b->cols;

        for (unsigned i = 0; i < result.rows; i++)
        {
            for (unsigned j = 0; j < result.cols; j++)
            {
                result.values[i][j] = 0;
                for (unsigned k = 0; k < a->cols; k++)
                    result.values[i][j] += a->values[i][k] * b->values[k][j];
            }
        }
    }
    else
    {
        result.rows = 0;
        result.cols = 0;
    }

    return result;
}


fmatrix_t average_columns_matrix(fmatrix_t * a)
{
    fmatrix_t result;
    result.rows = 1;
    result.cols = a->cols;

    for (unsigned j = 0; j < a->cols; j++)
    {
        result.values[0][j] = 0;
        for (unsigned i = 0; i < a->rows; i++)
            result.values[0][j] += a->values[i][j] / (float)a->rows;
    }

    return result;
}


fmatrix_t average_rows_matrix(fmatrix_t * a)
{
    fmatrix_t result;
    result.rows = a->rows;
    result.cols = 1;

    for (unsigned i = 0; i < a->rows; i++)
    {
        result.values[i][0] = 0;
        for (unsigned j = 0; j < a->cols; j++)
            result.values[i][0] += a->values[i][j] / (float)a->cols;
    }

    return result;
}


fmatrix_t transposed_matrix(fmatrix_t * a)
{
    fmatrix_t result;
    result.rows = a->cols;
    result.cols = a->rows;

    for (unsigned i = 0; i < a->rows; i++)
        for (unsigned j = 0; j < a->cols; j++)
            result.values[j][i] = a->values[i][j];

    return result;
}


fmatrix_t covariance_matrix(fmatrix_t * a)
{
    fmatrix_t result;
    result.rows = a->cols;
    result.cols = a->cols;

    // Calculate half of the matrix

    fmatrix_t m1 = init_fmatrix(a->rows, 1);
    fmatrix_t m2 = init_fmatrix(1, a->rows);

    fmatrix_t mean = average_columns_matrix(a);

    for (unsigned i = 0; i < result.rows; i++)
    {
        for (unsigned j = i; j < result.cols; j++)
        {
            // Copy column (implicit transpose)
            for (unsigned ii = 0; ii < a->rows; ii++)
            {
                m1.values[ii][0] = a->values[ii][i] - mean.values[0][i];
                m2.values[0][ii] = a->values[ii][j] - mean.values[0][j];
            }

            result.values[i][j] = multiply_matricies(&m2, &m1).values[0][0];
            result.values[i][j] /= (float) a->rows-1;
        }
    }

    // Copy other half over (covariance matrix is symmetric)

    for (unsigned i = 0; i < result.rows; i++)
        for (unsigned j = 0; j < i; j++)
            result.values[i][j] = result.values[j][i];

    return result;
}


fmatrix_t inverted_matrix(fmatrix_t * a)
{
    // Inverts a matrix using LU-decomposition.

    fmatrix_t result;

    if (a->rows == a->cols)
    {
        unsigned n = a->rows;

        result.rows = result.cols = a->rows;

        // Do LU-decomposition (A = LU)

        fmatrix_t L = init_fmatrix(n, n);
        fmatrix_t U = init_fmatrix(n, n);
        fmatrix_t P = init_fmatrix(n, n);

        LU_decomposition(a, &L, &U, &P);

        // Solve the system A * A^-1 = I using forward and back-substitution.

        // Much help from: http://www.mathworks.com/matlabcentral/fileexchange/
        //                     37459-matrix-inverse-using-lu-factorization

        fmatrix_t I = init_fmatrix(n, 1); // Identity

        for (int col = 0; col < n; col++)
        {
            for (int i = 0; i < n; i++)
                I.values[i][0] = (i == col);

            fmatrix_t b = multiply_matricies(&P, &I);


            fmatrix_t f_sub = init_fmatrix(n, 1);

            f_sub.values[0][0] = b.values[0][0] / L.values[0][0];

            for (int i = 1; i < n; i++)
            {
                float sum = 0;
                for (int j = 0; j < i; j++)
                    sum += L.values[i][j] * f_sub.values[j][0];
                f_sub.values[i][0] = (b.values[i][0] - sum) / L.values[i][i];
            }


            fmatrix_t b_sub = init_fmatrix(n, 1);

            b_sub.values[n-1][0] = f_sub.values[n-1][0] / U.values[n-1][n-1];

            for (int i = n-1; i >= 0; i--)
            {
                float sum = 0;
                for (int j = n-1; j > i; j--)
                    sum += U.values[i][j] * b_sub.values[j][0];
                b_sub.values[i][0] = (f_sub.values[i][0]-sum) / U.values[i][i];
            }


            for (int i = 0; i < n; i++)
                result.values[i][col] = b_sub.values[i][0];
        }
    }
    else
        result.rows = result.cols = 0;

    return result;
}


fmatrix_t boxcox_transform(fmatrix_t * a, float lambda)
{
    fmatrix_t result = init_fmatrix(a->rows, a->cols);

    if (lambda == 0.f)
    {
        for (int i = 0; i < a->rows; i++)
            for (int j = 0; j < a->cols; j++)
                result.values[i][j] = log(a->values[i][j]);
    }
    else
    {
        for (int i = 0; i < a->rows; i++)
            for (int j = 0; j < a->cols; j++)
                result.values[i][j] = (pow(a->values[i][j], lambda)-1)/lambda;
    }
    

    return result;
}


float determinant(fmatrix_t * a)
{
    if (a->rows == a->cols)
    {
        unsigned n = a->rows;

        if (n == 1)
        {
            return a->values[0][0];
        }
        else if (n == 2)
        {
            return a->values[0][0]*a->values[1][1]
                - a->values[0][1]*a->values[1][0];
        }
        else
        {
            // Do LU Decomposition - the product of the diagonals is
            // the determinant

            fmatrix_t L = init_fmatrix(n, n);
            fmatrix_t U = init_fmatrix(n, n);
            fmatrix_t P = init_fmatrix(n, n);

            unsigned S = LU_decomposition(a, &L, &U, &P);

            float det = pow(-1, S);

            for (unsigned i = 0; i < n; i++)
                det *= L.values[i][i] * U.values[i][i];

            return det;
        }
    }
    else
        return 0;
}


// ---- LU-Decomposition functions

unsigned LU_pivot(fmatrix_t * a, fmatrix_t * p)
{
    // Pivot function for LU-decomposition

    // Adapted from: http://rosettacode.org/wiki/LU_decomposition#C

    unsigned num_swaps = 0;
    unsigned n = a->rows;

    for (unsigned i = 0; i < n; i++)
        for (unsigned j = 0; j < n; j++)
            p->values[i][j] = (i == j);

    for (unsigned i = 0; i < n; i++)
    {
        int max_j = i;
        for (unsigned j = i; j < n; j++)
            if (fabs(a->values[j][i]) > fabs(a->values[max_j][i]))
                max_j = j;
        if (max_j != i)
        {
            for (unsigned k = 0; k < n; k++)
            {
                float temp = p->values[i][k];
                p->values[i][k] = p->values[max_j][k];
                p->values[max_j][k] = temp;
            }
            num_swaps++;
        }
    }

    return num_swaps;
}


unsigned LU_decomposition(
    fmatrix_t * A,
    fmatrix_t * L,
    fmatrix_t * U,
    fmatrix_t * P
){
    // Decomposes a matrix into upper and lower triangular matricies
    // such that A=LU. Returns the number of swaps from pivot function
    // (which can be used to compute the determinant of A)

    // Adapted from: http://rosettacode.org/wiki/LU_decomposition#C

    if (A->rows == A->cols)
    {
        const unsigned n = A->rows;

        L->rows = U->rows = P->rows = n;
        L->cols = U->cols = P->cols = n;

        clear_matrix(L);
        clear_matrix(U);
        clear_matrix(P);

        unsigned num_swaps = LU_pivot(A, P);

        fmatrix_t a_prime = multiply_matricies(P, A);

        for (unsigned i = 0; i < n; i++)
            L->values[i][i] = 1;

        for (unsigned i = 0; i < n; i++)
        {
            for (unsigned j = 0; j < n; j++)
            {
                if (j <= i)
                {
                    float sum = 0;

                    for (unsigned k = 0; k < j; k++)
                        sum += L->values[j][k] * U->values[k][i];

                    U->values[j][i] = a_prime.values[j][i] - sum;
                }
                if (j >= i)
                {
                    float sum = 0;

                    for (unsigned k = 0; k < i; k++)
                        sum += L->values[j][k]*U->values[k][i];

                    L->values[j][i]  = a_prime.values[j][i] - sum;
                    L->values[j][i] /= U->values[i][i];

                    if (U->values[i][i] == 0.f)
                        {}//printf("Warning: U[%d][%d] == 0 (!)\n", i, i);
                }
            }
        }

        return num_swaps;
    }
    else
        return 0;
}


// ---- Utility print function

void print_matrix(fmatrix_t * a)
{
    printf("\n%ux%u Matrix:\n\n", a->rows, a->cols);
    for (unsigned i = 0; i < a->rows; i++)
    {
        for (unsigned j = 0; j < a->cols; j++)
            printf("%8.4f ", a->values[i][j]);
        printf("\n");
    }
    printf("\n");
}

