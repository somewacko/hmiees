function onset_array = detect_onset(signals)

% Drew Simmons, Michael Flynn, Matthew Nelson, Stefan Sharpley
% Senior Design Project 2015
% VCU Dept of ECE

% This function takes a filtered EMG signal and uses the Bonato method to
% detect onset of motion. This function returns an array of equal size to
% the input array and designates which samples are in the "on" state versus
% the off state. use stem(x) to plot the output.

M = 1000;   % Number of "no motion" samples to set base_variance

h = 12;     % Threshold value to detect onset
n = 8;      % Number of above threshold samples out of m samples
m = 10;     % Number of samples in window
T1 = 80;    % Number of successive windows to achieve "onset"

base_variance = var( signals(1:M,:) );

n_of_m     = zeros(1, size(signals, 2));
active     = zeros(1, size(signals, 2));
off        = zeros(1, size(signals, 2));
activeflag = zeros(1, size(signals, 2));

onset_array = zeros(size(signals, 1), 1);

for i = 3:size(signals, 1) % for each 'ith' sample
    for s = 1:size(signals, 2) % in channel 's'
        
        if mod(i,2) ~= 0 % Only take in odd samples

            g = (1/base_variance(s)) * ...
                (signals(i-1,s)^2 + signals(i,s)^2);

            if (g >= h)
                n_of_m(s) = n_of_m(s) + 1;
                if n_of_m(s) >= m;
                    n_of_m(s) = m;
                end
            else
                n_of_m(s) = n_of_m(s) - 1;
                if n_of_m(s) <= 0
                    n_of_m(s) = 0;
                end
            end

            if activeflag(s) == 0

                if n_of_m(s) >= n            % Increments "active" if n 
                    active(s) = active(s)+1; % out of last m samples is 
                else                         % above threshold h. 
                    active(s) = 0;           % Otherwise, it resets.
                end

                if active(s) >= T1           % If the number of "active
                    activeflag(s) = 1;       % windows" exceeds T1, set
                end                          % activeflag
            else
                if n_of_m(s) < n
                    off(s) = off(s) + 1;
                else
                    off(s) = 0;
                end

                if off(s) >= T1
                    activeflag(s) = 0;
                end
            end
        end
        
        if activeflag(s) == 1
            onset_array(i) = 1; % Motion detected
        end
    end

end
end

