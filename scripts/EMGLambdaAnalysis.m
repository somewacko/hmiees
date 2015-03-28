% EMGLambdaAnalysis.m
% Flynn, Michael
%
%   Tests different values of lambda for the power transformation to see
%   what effect it has on classifier success.


% Read in data..

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


l_range = 0:0.05:1;
sp_range = 50:50:200;


figure(1); clf;

for n = 1:length(sp_range)
    
    successes = zeros(1, length(l_range));
    
    for i = 1:length(l_range)
        s = TestClassifier(signals, sp_range(n), l_range(i));
        successes(i) = mean(s);
    end
    
    subplot(220+n)
    plot(l_range, successes);
    title(sprintf('%d ms', sp_range(n)));
    xlabel('Lambda'); ylabel('Success Rate');
    ylim([0 100]);
end





