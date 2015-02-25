function wl = waveform_length(signal)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

    wl = 0;

    for k = 2:length(signal)
        wl = wl + abs(signal(k)-signal(k-1));
    end
end
