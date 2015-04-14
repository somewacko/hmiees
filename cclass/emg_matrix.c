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


fmatrix_t cofactor_matrix(fmatrix_t * a)
{
    fmatrix_t result;

    if (a->rows == a->cols)
    {
        result.rows = a->rows;
        result.cols = a->cols;

        for (unsigned i = 0; i < a->rows; i++)
        {
            for (unsigned j = 0; j < a->cols; j++)
            {
                result.values[i][j] = first_minor(a, i, j);

                if ((i+j) % 2 == 1)
                    result.values[i][j] *= -1;
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


fmatrix_t adjoint_matrix(fmatrix_t * a)
{
    fmatrix_t cof = cofactor_matrix(a);
    fmatrix_t result = transposed_matrix(&cof);

    return result;
}


fmatrix_t inverted_matrix(fmatrix_t * a)
{
    fmatrix_t result;

    float det = determinant(a);

    if (det != 0.f)
    {
        fmatrix_t adj = adjoint_matrix(a);

        result.rows = adj.rows;
        result.cols = adj.cols;

        for (unsigned i = 0; i < result.rows; i++)
            for (unsigned j = 0; j < result.cols; j++)
                result.values[i][j] = adj.values[i][j] / det;
    }
    else
    {
        result.rows = 0;
        result.cols = 0;
    }

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


float determ(float a[MAX_MATRIX_ROWS][MAX_MATRIX_ROWS], unsigned n)
{
    // This function is from stack overflow. Not great, but I don't want to
    // spend a lot of time on this..

    float det = 0;
    int p, h, k, i, j;
    float temp[MAX_MATRIX_ROWS][MAX_MATRIX_ROWS];

    if (n == 1)
    {
        return a[0][0];
    }
    else if (n == 2)
    {
        return (a[0][0]*a[1][1] - a[0][1]*a[1][0]);
    }
    else
    {
        for (p = 0; p < n; p++)
        {
            h = 0;
            k = 0;
            for (i = 1; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    if (j == p)
                        continue;

                    temp[h][k] = a[i][j];
                    k++;

                    if (k == n-1)
                    {
                        h++;
                        k = 0;
                    }
                }
            }
            det += a[0][p] * pow(-1, p) * determ(temp, n-1);
        }
        return det;
    }

    return 0;
}


float determinant(fmatrix_t * a)
{
    if (a->rows == a->cols)
        return determ(a->values, a->rows);
    else
        return 0;
}


float first_minor(fmatrix_t * a, unsigned ii, unsigned jj)
{
    fmatrix_t result;
    result.rows = a->rows-1;
    result.cols = a->cols-1;

    for (unsigned i = 0; i < a->rows; i++)
    {
        for (unsigned j = 0; j < a->cols; j++)
        {
            if (i == ii || j == jj)
                continue;
            result.values[i-(i>ii?1:0)][j-(j>jj?1:0)] = a->values[i][j];
        }
    }

    return determinant(&result);
}


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

