% EMGFeatureAnalysis.m
% Flynn, Michael
%
%   Reads in an EMG signal (signed 24-bit raw) and extracts features
%   upon detecting onset of motion. 


% Get information from the user

filename        = input('File of raw EMG data : ', 's');
sampling_rate   = input('Sampling rate (Hz)   : ');
analysis_period = input('Analysis Period (s)  : ');

samples_per_period = sampling_rate * analysis_period;


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
downsampled_signal = decimate(filtered_signal, D);


% Plot it to spit it back out

t   = 0 : 1/sampling_rate : (length(signal)-1)/sampling_rate;
t_d = 0 : 1/1000 : (length(downsampled_signal)-1)/1000;

subplot(121); plot(t, signal);
xlim([0 max(t)]); ylim([-1 1]);
title('Raw EMG Signal'); ylabel('t (s)');

subplot(122); plot(t_d, downsampled_signal);
xlim([0 max(t_d)]); ylim([-1 1]);
title('Filtered/Downsampled Signal'); ylabel('t (s)');


% Perform analysis on each frame

onset_threshold = 0.05;

mavslp_seg = 4;
wamp_threshold = 0.05;
zc_threshold = 0.05;

mav    = [];
mavslp = [];
wl     = [];
wamp   = [];
zc     = [];

x = samples_per_period;
periods = 0;
onsets = 0;

while x < length(filtered_signal)

    slice = filtered_signal(x-samples_per_period+1 : x);
    
    if max(abs(min(slice)),max(slice)) > onset_threshold
        mav    = [mav,    mean_absolute_value(slice)]; %#ok<*AGROW> :)
        mavslp = [mavslp, mean_absolute_value_slope(slice,mavslp_seg)];
        wl     = [wl,     waveform_length(slice)];
        wamp   = [wamp,   willison_amplitude(slice, wamp_threshold)];
        zc     = [zc,     zero_crossings(slice, zc_threshold)];
        onsets = onsets + 1;
    end
    
    x = x + samples_per_period;
    periods = periods + 1;
end


% Display results:

fprintf('Parameters:\n');
fprintf('\n');
fprintf('Onset of motion method: Threshold @ %0.2f\n',onset_threshold);
fprintf('\n');
fprintf('MAVSLP Segments: %d\n', mavslp_seg);
fprintf('WAMP Threshold:  %0.2f\n', wamp_threshold);
fprintf('ZC Threshold:    %0.2f\n', zc_threshold);
fprintf('\n');
fprintf('Results:\n');
fprintf('\n');
fprintf('Num. Onsets: %d/%d\n', onsets, periods);
fprintf('\n');
fprintf('MAV:\n\tAvg: %f\n\tVar: %f\n\tStd: %f\n', ...
    mean(mav), var(mav), std(mav));
fprintf('MAVSLP:\n\tAvg: %f\n\tVar: %f\n\tStd: %f\n', ...
    mean(mavslp), var(mavslp), std(mavslp));
fprintf('WL:\n\tAvg: %f\n\tVar: %f\n\tStd: %f\n', ...
    mean(wl), var(wl), std(wl));
fprintf('WAMP:\n\tAvg: %f\n\tVar: %f\n\tStd: %f\n', ...
    mean(wamp), var(wamp), std(wamp));
fprintf('ZC:\n\tAvg: %f\n\tVar: %f\n\tStd: %f\n', ...
    mean(zc), var(zc), std(zc));
fprintf('\n');
