function signals = get_two_channel_signals( ...
    filename1, filename2, sampling_rate, limit ...
)
    % Reads in two-channel signals from signed 24-bit raw files, filters
    % and downsamples it to 1000 Hz, and slices it up where it detects
    % onset of motion. Returns a cell array.
    
    signal1 = get_emg_signal(filename1, sampling_rate);
    signal2 = get_emg_signal(filename2, sampling_rate);

    signals = slice_signals([signal1, signal2], limit);
end

