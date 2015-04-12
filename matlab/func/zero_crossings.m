function zc = zero_crossings(sig, threshold)
    % Calculates the number of times the signal crosses zero.

    [N, cols] = size(sig);
    
    zc = zeros(1, cols);

    for i = 1:cols
        for k = 1:N-1        
            if abs(sig(k,i)-sig(k+1,i)) >= threshold
                if -sig(k,i) * sig(k+1,i) > 0
                    zc(i) = zc(i) + 1;
                end
            end
        end       
    end
end

