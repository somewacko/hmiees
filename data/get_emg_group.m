function emg_signals = get_emg_group(directory, sampling_rate)
    % Reads in all 24-bit raw emg signal files from a directory
    % and puts them in an n-column vector.
    
    % Note: this will cut all signals so that they are all the 
    % same size - the size of the shortest signal.
    
    files = dir(directory);
    
    emg_signals = [];
    min_length = Inf;
    
    for i = 1:length(files)
        if ~files(i).isdir
            filename = strcat(directory, files(i).name);
            [signal, ~] = get_emg_signal(filename, sampling_rate);
            
            min_length = min(min_length, length(signal));
            
            if isempty(emg_signals)
                emg_signals = signal;
            else
                emg_signals = horzcat( ...
                    emg_signals(1:min_length,:), signal(1:min_length) );
            end
        end
    end
end
