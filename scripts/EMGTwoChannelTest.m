% EMGTwoChannelTest.m
% Flynn, Michael
%
%   Script that reads in two channels of EMG signals and tests the
%   classifier with them. Uses data from data/stefan/whole. Spits out
%   a large repor.


% Read in data and cut signals into slices

file_sampling_rate = 8000; % The sampling rate of the signal being read.
slice_limit        = 100;  % The minimum length of a slice.

fprintf('\nSampling rate       : %d\n', file_sampling_rate);
fprintf(  'Min. slice duration : %d\n', slice_limit)

files = {
    %'data/stefan/whole/2xClockwise_two_Sharpley1.raw',   ...
    %'data/stefan/whole/2xClockwise_two_Sharpley2.raw',   ...
    %'data/stefan/whole/2xCounter_two_Sharpley1.raw',     ...
    %'data/stefan/whole/2xCounter_two_Sharpley2.raw',     ...
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
    %'CW Rot.       ', ...
    %'C-CW Rot.     ', ...
    'Inward Flex   ', ...
    'Outward Flex  ', ...
    'Reverse Grasp ', ...
    'Simple Squeeze'  ...
};

signals = cell(1, size(files, 2)/2);

n = 1;
for i = 1:2:size(files, 2)
    signals(n) = {get_two_channel_signals(      ...
        char(files(i)), char(files(i+1)), ...
        file_sampling_rate, 400 ...
    )};
    n = n+1;
end

num_trials = 0;

fprintf('\n');
for i = 1:size(signals, 2)
    fprintf('%s: %d trials\n', ...
        char(gesture_names(i)), length(signals{i}));
    num_trials = num_trials + length(signals{i});
end
fprintf('\n');


% Test classifier

successes = [];
periods   = 25:25:400;

for sampling_period = periods

    fprintf('Testing with Sampling Period: %d ms\n\n', sampling_period);
    
    [avg_successes, distances] = TestClassifierTwoChannel( ...
        signals, sampling_period, [], gesture_names, 1);
    
    %fprintf('\n');
    %for i = 1:length(avg_successes)
    %    fprintf('\t%s success : %0.2f\n', ...
    %        char(gesture_names(i)), avg_successes(i));
    %end
    
    avg = 0;
    for i = 1:length(avg_successes)
        avg = avg + avg_successes(i) * (length(signals{i})/num_trials);
    end
    
    fprintf('\n\tAvg Success : %0.2f\n\n', avg);
    %fprintf(  '\tAvg Successful Distance : %0.2f\n', mean(distances));
    %fprintf(  '\tStd Successful Distance : %0.2f\n', std(distances));
    %fprintf(  '\tMax Successful Distance : %0.2f\n', max(distances));
    %fprintf(  '\tMin Successful Distance : %0.2f\n\n', min(distances));

    successes = [successes, avg]; %#ok<AGROW>
end


% Make a new classifier to poke around with after this script is finished, 
% leaving out the first signal in each group.

classifier = EMGClassifier(200);
gestures = [];

for i = 1:size(signals, 2)
    signals_copy = signals{i};
    signals_copy(:,1) = [];
    gesture = classifier.register_gesture(char(gesture_names(i)));
    for k = 1:length(signals_copy)
        classifier.train_multiple_channels(signals_copy{k}, gesture);
    end
    gestures = [gestures, gesture]; %#ok<AGROW>
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







