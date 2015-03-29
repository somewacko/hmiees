function sliced_signals = slice_signals(signals, limit)
    % Slices up signals according to where onset of motion is detected.
    % Returns a cell array of all of the slices, where each slice is longer
    % than "limit"
    
    onset = detect_onset(signals);
    
    sliced_signals = {};
    
    slice_start = 1;
    slice_end = 1;
    
    is_motion = 0;
    
    for i = 1:length(onset)
    
        if is_motion == 1
            
            if onset(i) == 0
                slice_end = i;
                is_motion = 0;
                
                if slice_end-slice_start >= limit
                
                    slice = signals(slice_start:slice_end,:);
                    sliced_signals( length(sliced_signals)+1 ) = {slice}; %#ok<AGROW>
                end
            end
        else
            if onset(i) == 1
                slice_start = i;
                
                if i - slice_end > limit
                    is_motion = 1;
                end
            end
        end
    end
end

