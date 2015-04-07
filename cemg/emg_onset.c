/* Drew Simmons, Michael Flynn, Matthew Nelson, Stefan Sharpley
 Senior Design Project 2015
 VCU Dept of ECE

 This function takes a filtered EMG signal and uses the Bonato method to
 detect onset of motion. This function returns an array of equal size to
 the input array and designates which samples are in the "on" state versus
 the off state. use stem(x) to plot the output.
*/

#include "emg_onset.h"


bool onset_detected(emg_sample_t current_member)
{
	int M = 1000, h = 4, n = 2, m = 5, T1 = 80;     			  //M:number of "no motion" samples to set base_variance
	static int active, off, activeflag;                							 //these should occur at beginning of the sample set
	static unsigned int test_count, count;
	static float sum, base_variance; 			  //h:threshold value to detect onset
	emg_sample_t  previous_member;
	int n_of_m = 0;	      //n:number of above threshold samples out of m samples
	float mean = 0.0, smean = 0.0, g = 0.0; 								  //m:number of samples in window
											         			  //T1:number of successive windows to achieve "onset"
	if(test_count<M){
		sum += current_member;
		if(test_count == (M-1)){
			mean = sum/M;
			smean = (sum*sum)/M;
			base_variance = smean - mean*mean; 
			previous_member = current_member;	
		}
		test_count++;
		return(false);				
	}
	else{		
		    
		if (count%2 == 0){         //g only takes odd samples (first sample ignored)
		    g = (1/base_variance)*(previous_member*previous_member+current_member*current_member);
	    
	        if(g>=h){                //increments n_of_m if g is larger than h otherwise
	        	n_of_m += 1;    	//decrements n_of_m
	        	if (n_of_m >= m)
	            	n_of_m = m;	      
			}
			else{
				n_of_m -= 1;
	        	if (n_of_m <= 0)
	            	n_of_m = 0;
			}

	        
	        if (!activeflag){
	            
	            if (n_of_m>=n){              //increments "active" if n out of last m samples
	               active += 1;  			 //is above threshold h. Otherwise it resets active to zero
	            }
	            else{
	                active = 0; 
	            }          
	            if (active >= T1)             //if the number of "active windows" exceeds T1
	                activeflag = 1;
	        }
	        else{
	            if (n_of_m<n){
	                off += 1;
	            }
	            else{
	                off = 0;
	            }
	            
	            if (off >= T1)
	                activeflag = 0;	         
	        }
	    }
	    else{
	    	previous_member = current_member;
	    }

	    count++;	    
	    if (activeflag){
	        return(true);     //then "motion" is detected. Otherwise "no motion" is detected
	    }
	    else{
	    	return(false);
	    }  
	}
}