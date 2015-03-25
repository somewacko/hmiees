% EMGClassificationTest.m
% Flynn, Michael
% 
%   Script that tests classification with the .raw files in
%   data/{name}/slices.
%
%   Currently only uses 'simple_squeeze' and 'reverse_grasp' from
%   data/flynn/slices.


% Read in data and set up variables.

file_sampling_rate = 8000;

directories = {
    'data/flynn/slices/simple_squeeze/', ...
    'data/flynn/slices/reverse_grasp/',  ...
    'data/flynn/slices/inwards_bend/'    ...
};

gesture_names = {
    'Simple Squeeze', ...
    'Reverse Grasp',  ...
    'Inwards Bend'    ...
};

signals = cell(1, size(directories, 2));

for i = 1:size(directories, 2)
    directory = char(directories(i));
    signals{i} = get_emg_group(directory, file_sampling_rate);
end


% Test classifier at different sampling periods

successes = [];
periods   = 25:25:500;

for sampling_period = periods

    %fprintf('\nTesting with sampling_period = %d\n\n', ...
    %    sampling_period);

    avg_success = TestClassifier(signals, sampling_period);

    %fprintf('Results:\n');
    %for i = 1:size(directories, 2)
    %    fprintf('\t%s\tSuccess: %0.2f%%\n', ...
    %        char(gesture_names{i}), avg_success(i));
    %end
    %fprintf('\nOverall Success: %0.2f%%\n\n', mean(avg_success));

    successes = [successes, mean(avg_success)]; %#ok<AGROW>
end


% Display results on a bar graph

figure(1); clf;
bar(periods, successes);
ylim([0 100]);

ttl = sprintf('Success Rates for Classifier With %d Gestures', ...
    size(signals, 2));

title(ttl);
xlabel('Sampling Period');
ylabel('Success Rate');


