% EMGFeatureAnalysis.m
% Flynn, Michael
%
%   Reads in EMG signals and outputs statistics about their features.

clf;

file_sampling_rate = 8000;
sampling_period    = 200;

directories = {
    'data/flynn/slices/simple_squeeze/', ...
    'data/flynn/slices/reverse_grasp/',  ...
    'data/flynn/slices/inwards_bend/'    ...
};

names = {
    'Simple Squeeze', ...
    'Reverse Grasp',  ...
    'Inwards Bend'    ...
};

colors = {
    'b.', ...
    'c.', ...
    'g.'  ...
};

fprintf('\n');
fprintf('Sampling period: %f\n', sampling_period);
fprintf('\n');


% Calculate MAV and WL (these don't have parameters)

mav = cell(1, size(directories, 2));
wl  = cell(1, size(directories, 2));

for i = 1:size(directories, 2)
    directory = char(directories(i));
       
    signals = get_emg_group(directory, file_sampling_rate);
    slice = signals(1:sampling_period,:);
    
    mav(i) = {EMGFeature.MAV.extract(slice, [])};
    wl(i)  = {EMGFeature.WL.extract(slice, [])};
end

fprintf('Mean Absolute Value:\n');
for i = 1:size(directories, 2)
    fprintf('\t%s\n', char(names(i)));
    fprintf('\t\tMean: %f\n', mean( cell2mat(mav(i)) ));
    fprintf('\t\tStd:  %f\n',  std( cell2mat(mav(i)) ));
end
fprintf('\nWaveform Length:\n')
for i = 1:size(directories, 2)
    fprintf('\t%s\n', char(names(i)));
    fprintf('\t\tMean: %f\n', mean( cell2mat(wl(i)) ));
    fprintf('\t\tStd:  %f\n',  std( cell2mat(wl(i)) ));
end
fprintf('\n');


% Plot WAMP and ZC

fig_wamp = figure(1);
title('Willison Amplitude');
xlabel('Parameter Value');

fig_zc = figure(2);
title('Zero Crossings');
xlabel('Parameter Value');

for i = 1:size(directories, 2)
    directory = char(directories(i));
       
    signals = get_emg_group(directory, file_sampling_rate);
    slice = signals(1:sampling_period,:);

    % WAMP
    
    val = 0:0.01:0.45;
    
    avgs = zeros(1, length(val));
    stds = zeros(1, length(val));
    
    for n = 1:length(val)
        wamp = EMGFeature.WAMP.extract(slice, val(n));
        avgs(n) = mean(wamp);
        stds(n) = std(wamp); 
    end
    
    figure(fig_wamp); hold on;
    errorbar(val+(i-1)*0.0025, avgs, stds, char(colors(i)));
    
    % ZC
    
    val = 0:0.01:0.5;
    
    avgs = zeros(1, length(val));
    stds = zeros(1, length(val));
    
    for n = 1:length(val)
        wamp = EMGFeature.ZC.extract(slice, val(n));
        avgs(n) = mean(wamp);
        stds(n) = std(wamp); 
    end
    
    figure(fig_zc); hold on;
    errorbar(val+(i-1)*0.001, avgs, stds, char(colors(i)));
end

hold off;
