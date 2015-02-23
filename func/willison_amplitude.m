function wamp = willison_amplitude(sig, threshold)
    % Calcuates the willison amplitude, the number of times the signal's
    % change in amplitude exceeds a certain value.
    
    wamp = 0;
    
    for k = 1:length(sig)-1
        if abs(sig(k)-sig(k+1)) > threshold
            wamp = wamp+1;
        end
    end
end
