function [emg_signal, t] = get_emg_signal(filename, sampling_rate)
    % Reads in a signal from a signed 24-bit raw file, filters and
    % downsamples it to 1000 Hz.

    % Read in the data

    file_id = fopen(filename, 'r');
    signal = fread(file_id, inf, 'bit24');
    signal = signal ./ 2^23; % Scale between -1 and 1


    % Filter and downsample the signal to 1000 Hz

    % Note that the filtering stage might be unnecessary
    % since Matlab's decimate() function uses an 8th-order
    % Chebyshev filter before downsampling.

    filtered_signal = detrend(signal);  % Remove DC offset
    n = 4;                              % Order of the filter
    nyquist = sampling_rate/2;
    Wn = [10 500];                      % Cutoff frequencies

    [btw_b, btw_a] = butter(n, Wn/nyquist);
    filtered_signal = filtfilt(btw_b, btw_a, filtered_signal);

    D = ceil(sampling_rate/1000);
    emg_signal = decimate(filtered_signal, D);
    
    
    % Get time vector too
    
    t = 0 : 1/1000 : (length(emg_signal)-1)/1000;
    
end
