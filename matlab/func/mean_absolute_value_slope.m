function mavslp = mean_absolute_value_slope(sig, I)
    % Computes the mean absolute value slope of a signal across 'i'
    % segments.
    
    mavs = zeros(I, 1);
    slopes = zeros(I-1, 1);
    
    segment_size = floor(length(sig)/I);
    
    for i = 1:I
        segment = sig(1+segment_size*(i-1):segment_size*i);
        mavs(i) = mean_absolute_value(segment);
    end
    
    for i = 1:I-1
        slopes(i) = mavs(i+1)-mavs(i);
    end
    
    % Note: Unsure if the slopes should be averaged out like this or we
    % should just be returning the slopes vector.
    mavslp = sum(slopes)/length(slopes); 
end
