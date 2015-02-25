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

t = 0 : 1/sampling_rate : (length(signal)-1)/sampling_rate;

plot(t, signal);
xlim([0 max(t)]); ylim([-1 1]);
title('EMG Signal'); ylabel('t (s)');


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

while x < length(signal)

    slice = signal(x-samples_per_period+1 : x);
    
    if max(abs(min(slice)),max(slice)) > onset_threshold
        mav    = [mav,    mean_absolute_value(slice)]; %#ok<*AGROW> :)
        mavslp = [mavslp, mean_absolute_value_slope(slice, mavslp_seg)];
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
fprintf('Onset of motion method: Threshold @ %0.2f\n', onset_threshold);
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
