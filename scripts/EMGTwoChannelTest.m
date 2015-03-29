% EMGTwoChannelTest.m
% Flynn, Michael
%
%   Script that reads in two channels of EMG signals and tests the
%   classifier with them. Uses data from data/stefan/whole.


% Read in data and cut signals into slices

file_sampling_rate = 8000;

files = {
    'data/stefan/whole/2xClockwise_two_Sharpley1.raw',   ...
    'data/stefan/whole/2xClockwise_two_Sharpley2.raw',   ...
    'data/stefan/whole/2xCounter_two_Sharpley1.raw',     ...
    'data/stefan/whole/2xCounter_two_Sharpley2.raw',     ...
    'data/stefan/whole/InwardFlex_two_Sharpley1.raw',    ...
    'data/stefan/whole/InwardFlex_two_Sharpley2.raw',    ...
    'data/stefan/whole/OutwardFlex_two_Sharpley1.raw',   ...
    'data/stefan/whole/OutwardFlex_two_Sharpley2.raw',   ...
    'data/stefan/whole/RevGrasp_two_Sharpley1.raw',      ...
    'data/stefan/whole/RevGrasp_two_Sharpley2.raw',      ...
    'data/stefan/whole/SimpleSqueeze_two_Sharpley1.raw', ...
    'data/stefan/whole/SimpleSqueeze_two_Sharpley2.raw'  ...
};

gesture_names = {
    'Clockwise Rot.',         ...
    'Counter-Clockwise Rot.', ...
    'Inward Flex',            ...
    'Outward Flex',           ...
    'Reverse Grasp',          ...
    'Simple Squeeze'          ...
};

signals = cell(1, size(files, 2)/2);

n = 1;
for i = 1:2:size(files, 2)
    signals(n) = {get_two_channel_signals(      ...
        char(files(i)), char(files(i+1)), 8000 ...
    )};
    n = n+1;
end


% Test classifier

successes = [];
periods   = 50:50:400;

for sampling_period = periods

    avg_success = TestClassifierTwoChannel(signals, sampling_period, [], gesture_names);

    successes = [successes, mean(avg_success)]; %#ok<AGROW>
end

% Display results on a bar graph

figure(1); clf;
bar(periods, successes);
ylim([0 100]);

ttl = sprintf(...
    'Success Rates for Classifier With %d Gestures (2 channels)', ...
    size(signals, 2));

title(ttl);
xlabel('Sampling Period');
ylabel('Success Rate');







