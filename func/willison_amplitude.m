function wamp = willison_amplitude(sig, threshold)
    % Calcuates the willison amplitude, the number of times the signal's
    % change in amplitude exceeds a certain value.
    
    [N, cols] = size(sig);
    
    wamp = zeros(1, cols);
    
    for i = 1:cols
        for k = 1:N-1
            if abs(sig(k,i)-sig(k+1,i)) > threshold
                wamp(i) = wamp(i)+1;
            end
        end
    end
end
