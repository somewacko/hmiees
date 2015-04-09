//  -------- -------- -------- -------- -------- -------- -------- --------  //
//  emg_onset.c
//  flynn, michael / drew simmons / stefan sharpley
//
//  functions to detect the onset of motion of a given emg signal.
//
//  -------- -------- -------- -------- -------- -------- -------- --------  //

#include "emg_onset.h"


bool onset_detected(emg_sample_t sample)
{
    const int M  = 1000, // Number of "no motion" samples to set base variance.
              n  = 1,    // Number of above threshold samples out of m samples.
              m  = 12,   // Number of samples in window.
              T1 = 20;   // Number of successive windows to achieve "onset".

    const float h = 40.f; // Threshold value to detect onset.

    static bool activeflag;
    static int active, off;
    static unsigned base_var_count, count;
    static float base_variance;
    static emg_sample_t previous_sample;
    static int n_of_m = 0;
    static float mean, sq_mean, g = 0.0;

    if (base_var_count < M) // Find base variance for the first M samples
    {
        mean    += sample / (float) M;
        sq_mean += (sample * sample) / (float) M;

        if (base_var_count == M-1)
        {
            base_variance = sq_mean - mean * mean; 
            previous_sample = sample;

            printf("Baseline variance established: %0.8f\n", base_variance);
            printf("mean = %0.8f, sq_mean = %0.8f\n",
                mean, sq_mean);
        }

        base_var_count++;

        return false; // Return false while doing so.
    }
    else // After establishing base variance, 
    {               
        if (count % 2 == 0)
        {
            g = (1/base_variance) * ( sample*sample
                + previous_sample*previous_sample );
        
            if (g >= h)
            {
                n_of_m += 1;

                if (n_of_m >= m)
                    n_of_m = m;       
            }
            else
            {
                n_of_m -= 1;

                if (n_of_m <= 0)
                    n_of_m = 0;
            }
            
            if (!activeflag)
            {
                if (n_of_m >= n)
                    active += 1;
                else
                    active = 0; 

                if (active >= T1)
                    activeflag = true;
            }
            else
            {
                if (n_of_m < n)
                    off += 1;
                else
                    off = 0;
                
                if (off >= T1)
                    activeflag = false;          
            }
        }
        else
        {
            previous_sample = sample;
        }

        count++;

        return activeflag;
    }
}

