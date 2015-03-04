function [emg_signal, t] = get_emg_signal(filename, sampling_rate)
    % Reads in a signal from a signed 24-bit raw file, filters and
    % downsamples it to 1000 Hz.

    % Read in the data

    file_id = fopen(filename, 'r');
    signal = fread(file_id, inf, 'bit24');
    signal = signal ./ 2^23; % Scale between -1 and 1


    % Decimate the signal to 1000 Hz

    D = ceil(sampling_rate/1000);
    emg_signal = decimate(signal, D);
    
    
    % Also return the time vector
    
    t = 0 : 1/1000 : (length(emg_signal)-1)/1000;
    
end
