% PrelimOnsetMotion.m
% Flynn, Michael
%
%   Reads in a 24-bit raw file of EMG signal data and finds the
%   locations of the onset of motion, annotating them on a plot.


% Get information from the user

filename        = input('File of raw EMG data : ', 's');
sampling_rate   = input('Sampling rate (Hz)   : ');
threshold       = input('Onset threshold      : ');


% Read in signal and find the onset of motion using Miller's
% Bonato method

[signal, t] = get_emg_signal(filename, sampling_rate);

onsets = [];

for i = 201:200:length(signal)
    next_onset = BonatoOnset(signal(i-200:i), threshold);
    
    if ~isempty(next_onset)
        next_onset = next_onset+i-200;
        onsets = [onsets, next_onset]; %#ok<AGROW>
    end
end


% Plot to figure

clf; hold on;
plot(t, signal);
stem(onsets/1000,  2*ones(1, length(onsets)), 'r');
stem(onsets/1000, -2*ones(1, length(onsets)), 'r');
hold off;
xlim([0 max(t)]); ylim([-1 1]);
