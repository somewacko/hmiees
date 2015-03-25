function ssc = slope_sign_changes(sig, threshold)
    % Counts the number of times the slope's sign changes
    % after exceeding a certain threshold.

    [N, cols] = size(sig);
    
    ssc = zeros(1, cols);

    for i = 1:cols
        for k = 2:N-1 
            calc = (sig(k,i)-sig(k-1,i)) * (sig(k,i)-sig(k+1,i));
            if calc >= threshold
                if -sig(k,i) * sig(k+1,i) > 0
                    ssc(i) = ssc(i) + 1;
                end
            end
        end       
    end
end

