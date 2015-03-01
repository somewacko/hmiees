function wl = waveform_length(sig)
    % Calculates the overall waveform length.

    [N, cols] = size(sig);
    
    wl = zeros(1, cols);

    for k = 2:N
        wl = wl + abs(sig(k,:)-sig(k-1,:));
    end
end
