% EMGClassificationTest.m
% Flynn, Michael
% 
%   Script that tests classification with the .raw files in
%   data/{name}/slices.
%
%   Currently only uses 'simple_squeeze' and 'reverse_grasp' from
%   data/flynn/slices.


% Read in data and set up variables.

ss_signals = get_emg_group('data/flynn/slices/simple_squeeze/', 8000);
rg_signals = get_emg_group('data/flynn/slices/reverse_grasp/' , 8000);

ss_name = 'Simple Squeeze';
rg_name = 'Reverse Grasp';

ss_success = 0;
rg_success = 0;

ss_correct_distance   = 0;
ss_incorrect_distance = 0;
rg_correct_distance   = 0;
rg_incorrect_distance = 0;

sampling_period = 200;


fprintf('\nTesting with sampling_period = %d\n\n', sampling_period);


% Test simple squeeze

for i = 1:size(ss_signals, 2)
    
    % Copy signals over and remove signal that we're going to test.
    ss_signals_copy = ss_signals;
    ss_signals_copy(:,i) = [];
    
    classifier = EMGClassifier(sampling_period);
    
    ss_gesture = classifier.register_gesture(ss_name);
    classifier.train(ss_signals_copy, ss_gesture);
    
    rg_gesture = classifier.register_gesture(rg_name);
    classifier.train(rg_signals, rg_gesture);
    
    [gesture, distance] = classifier.classify(ss_signals(:,i));
    
    %fprintf('Simple squeeze signal %2d\n', i);
    %fprintf('\tGesture  - %s\n', gesture.name);
    %fprintf('\tDistance - %0.2f\n', distance);
    
    if gesture == ss_gesture
        ss_success = ss_success + 1;
        ss_correct_distance = ss_correct_distance + distance;
    else
        ss_incorrect_distance = ss_incorrect_distance + distance;
    end
end

ss_correct_distance = ss_correct_distance / ss_success;
ss_incorrect_distance = ss_incorrect_distance ...
    / (size(ss_signals, 2)-ss_success);


% Test reverse grasp

for i = 1:size(rg_signals, 2)
    
    % Copy signals over and remove signal that we're going to test.
    rg_signals_copy = rg_signals;
    rg_signals_copy(:,i) = [];
    
    classifier = EMGClassifier(sampling_period);
    
    ss_gesture = classifier.register_gesture(ss_name);
    classifier.train(ss_signals, ss_gesture);
    
    rg_gesture = classifier.register_gesture(rg_name);
    classifier.train(rg_signals_copy, rg_gesture);
    
    [gesture, distance] = classifier.classify(rg_signals(:,i));
    
    %fprintf('Reverse Grasp signal %2d\n', i);
    %fprintf('\tGesture  - %s\n', gesture.name);
    %fprintf('\tDistance - %0.2f\n', distance);
    
    if gesture == rg_gesture
        rg_success = rg_success + 1;
        rg_correct_distance = rg_correct_distance + distance;
    else
        rg_incorrect_distance = rg_incorrect_distance + distance;
    end
end

rg_correct_distance = rg_correct_distance / rg_success;
rg_incorrect_distance = rg_incorrect_distance ...
    / (size(rg_signals, 2)-rg_success);


% Print final results

fprintf('\n');
fprintf('Sampling period: %d\n', sampling_period);
fprintf('\n');
fprintf('SS success: %0.2f%%\n', 100*ss_success/size(ss_signals, 2));
fprintf('RG success: %0.2f%%\n', 100*rg_success/size(rg_signals, 2));
fprintf('\n');
fprintf('SS Avg correct distance:   %0.2f\n', ss_correct_distance);
fprintf('SS Avg incorrect distance: %0.2f\n', ss_incorrect_distance);
fprintf('\n');
fprintf('RG Avg correct distance:   %0.2f\n', rg_correct_distance);
fprintf('RG Avg incorrect distance: %0.2f\n', rg_incorrect_distance);
fprintf('\n');

