% EMGLambdaAnalysis.m
% Flynn, Michael
%
%   Tests different values of lambda for the power transformation to see
%   what effect it has on classifier success.


% Read in data..

file_sampling_rate = 8000;

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
    %'Clockwise Rot.',         ...
    %'Counter-Clockwise Rot.', ...
    'Inward Flex',            ...
    'Outward Flex',           ...
    'Reverse Grasp',          ...
    'Simple Squeeze'          ...
};

signals = cell(1, size(files, 2)/2);

n = 1;
for i = 1:2:size(files, 2)
    signals(n) = {get_two_channel_signals(      ...
        char(files(i)), char(files(i+1)), 8000, 150 ...
    )};
    n = n+1;
end


l_range = 0.05:0.05:1;
sp_range = [150];


figure(1); clf;

for n = 1:length(sp_range)
    
    fprintf('\nTesting %d ms\n\n', sp_range(n));
    
    successes = zeros(1, length(l_range));
    
    for i = 1:length(l_range)
        
        s = TestClassifierTwoChannel( ...
            signals, sp_range(n), l_range(i), gesture_names, 0);
        successes(i) = mean(s);
        
        fprintf('\tLambda: %0.2f, Success: %0.2f\n', l_range(i), mean(s));
    end
    fprintf('\n');
    
    subplot(220+n)
    plot(l_range, successes);
    title(sprintf('%d ms', sp_range(n)));
    xlabel('Lambda'); ylabel('Success Rate');
    ylim([0 100]);
end





