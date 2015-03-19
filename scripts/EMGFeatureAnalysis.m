% EMGFeatureAnalysis.m
% Flynn, Michael
%
%   Reads in EMG signals and outputs statistics about their features.

file_sampling_rate = 8000;
sampling_period    = 200;

directories = {
    'data/flynn/slices/simple_squeeze/', ...
    'data/flynn/slices/reverse_grasp/'   ...
};

fprintf('\n');
fprintf('Sampling period: %f\n', sampling_period);
fprintf('\n');
fprintf('MAVSLP Segments: %d\n',    EMGFeature.MAVSLP.value);
fprintf('WAMP Threshold:  %0.2f\n', EMGFeature.WAMP.value);
fprintf('ZC Threshold:    %0.2f\n', EMGFeature.ZC.value);
fprintf('\n');

for i = 1:size(directories, 2)
    directory = char(directories(i));
   
    % Read in signals and take a slice
    
    signals = get_emg_group(directory, file_sampling_rate);
    slice = signals(1:sampling_period,:);
    
    % Extract features

    feat_mav    = EMGFeature.MAV.extract(slice, []);
    feat_mavslp = EMGFeature.MAVSLP.extract(slice, []);
    feat_wamp   = EMGFeature.WAMP.extract(slice, []);
    feat_wl     = EMGFeature.ZC.extract(slice, []);
    feat_zc     = EMGFeature.ZC.extract(slice, []);

    % Display results:

    fprintf('%s:\n', directory);
    fprintf('\n');
    fprintf('MAV:\n\tAvg: %0.8f\n\tVar: %0.8f\n\tStd: %0.8f\n', ...
        mean(feat_mav), var(feat_mav), std(feat_mav));
    fprintf('MAVSLP:\n\tAvg: %0.8f\n\tVar: %0.8f\n\tStd: %0.8f\n', ...
        mean(feat_mavslp), var(feat_mavslp), std(feat_mavslp));
    fprintf('WAMP:\n\tAvg: %0.8f\n\tVar: %0.8f\n\tStd: %0.8f\n', ...
        mean(feat_wamp), var(feat_wamp), std(feat_wamp));
    fprintf('WL:\n\tAvg: %0.8f\n\tVar: %0.8f\n\tStd: %0.8f\n', ...
        mean(feat_wl), var(feat_wl), std(feat_wl));
    fprintf('ZC:\n\tAvg: %0.8f\n\tVar: %0.8f\n\tStd: %0.8f\n', ...
        mean(feat_zc), var(feat_zc), std(feat_zc));
    fprintf('\n');
end


