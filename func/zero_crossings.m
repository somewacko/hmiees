function zc = zero_crossings(sig, threshold)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

    zc = 0;

    for k = 1:length(sig)-1
        
        if abs(sig(k)-sig(k+1)) >= threshold
            
            if -sig(k) * sig(k+1) > 0
                zc = zc +1;
            end
        end       
    end
end

