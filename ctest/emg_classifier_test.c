#include <stdio.h>

#include "emg_classifier.h"
#include "emg_matrix.h"

int main(void)
{
    fmatrix_t s = init_fmatrix(4, 2);
    s.values[0][0] =  0.75; s.values[0][1] =  2.00;
    s.values[1][0] =  1.00; s.values[1][1] =  2.25;
    s.values[2][0] =  1.25; s.values[2][1] =  2.12;
    s.values[3][0] =  1.05; s.values[3][1] =  1.88;

    fmatrix_t t = init_fmatrix(1, 2);
    t.values[0][0] =  0.88; t.values[0][1] =  2.10;

    print_matrix(&t);
    print_matrix(&s);

    float d = mahal_distance(&t, &s); // Should be 0.5612

    printf("\nMahal Distance: %0.4f\n\n", d);

    return 0;
}
