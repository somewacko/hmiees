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


% Read in signals

signals = cell(1, size(directories, 2));

for i = 1:size(directories, 2)
    directory = char(directories(i));
        
    sig = get_emg_group(directory, file_sampling_rate);
    signals(i) = {sig(1:sampling_period,:)};
end


% Calculate features without parameters

feats = [ ...
    EMGFeature.MAV, ...
    EMGFeature.SSI, ...
    EMGFeature.VAR, ...
    EMGFeature.WL   ...
];

for i = 1:length(feats)
    
    calc = cell(1, size(directories, 2));
    
    for l = 1:size(directories, 2)
        calc(l) = {feats(i).extract(cell2mat(signals(l)), [])};
    end
    
    fprintf('%s:\n', feats(i).name);
    for l = 1:size(directories, 2)
        fprintf('\t%s\n', char(names(l)));
        fprintf('\t\tMean: %f\n', mean( cell2mat(calc(l)) ));
        fprintf('\t\tStd:  %f\n',  std( cell2mat(calc(l)) ));
    end
end


% Plot WAMP and ZC

fig_wamp = figure(1); clf;
title('Willison Amplitude');
xlabel('Parameter Value');

fig_zc = figure(2); clf;
title('Zero Crossings');
xlabel('Parameter Value');

for i = 1:size(directories, 2)

    % WAMP
    
    val = 0:0.01:0.45;
    
    avgs = zeros(1, length(val));
    stds = zeros(1, length(val));
    
    for n = 1:length(val)
        wamp = EMGFeature.WAMP.extract(cell2mat(signals(i)), val(n));
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
        wamp = EMGFeature.ZC.extract(cell2mat(signals(i)), val(n));
        avgs(n) = mean(wamp);
        stds(n) = std(wamp); 
    end
    
    figure(fig_zc); hold on;
    errorbar(val+(i-1)*0.001, avgs, stds, char(colors(i)));
end

hold off;
