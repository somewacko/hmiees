% EMGFeatureAnalysis.m
% Flynn, Michael
%
%   Reads in EMG signals and outputs statistics about their features.

clf;

file_sampling_rate = 8000;
sampling_period    = 150;

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

names = {
    %'CW Rot.       ', ...
    %'C-CW Rot.     ', ...
    'Inward Flex   ', ...
    'Outward Flex  ', ...
    'Reverse Grasp ', ...
    'Simple Squeeze'  ...
};

colors = {
    'b.', ...
    'c.', ...
    'g.', ...
    'm.'  ...
};

fprintf('\n');
fprintf('Sampling period: %f\n', sampling_period);
fprintf('\n');


% Read in signals

signals = cell(1, size(files, 2)/2);

n = 1;
for i = 1:2:size(files, 2)
    signals(n) = {get_two_channel_signals( ...
        char(files(i)), char(files(i+1)), ...
        file_sampling_rate, sampling_period ...
    )};
    n = n+1;
end


% Calculate features without parameters

feats = [ ...
    EMGFeature.MAV, ...
    EMGFeature.SSI, ...
    EMGFeature.VAR, ...
    EMGFeature.WL   ...
];

for i = 1:length(feats)
    for channel = 1:2
        
        fprintf('Channel %d:\n\n', channel);
    
        calc = cell(1, length(signals));

        for grp = 1:length(signals)
            x = [];
            for n = 1:length(signals{grp})
                x = [ x, feats(i).extract( ...
                    signals{grp}{n}(:,channel), []) ]; %#ok<AGROW>
            end
            calc(grp) = {x};
        end

        fprintf('%s:\n', feats(i).name);
        for l = 1:length(signals)
            fprintf('\t%s\n', char(names(l)));
            fprintf('\t\tMean: %f\n', mean( cell2mat(calc(l)) ));
            fprintf('\t\tStd:  %f\n',  std( cell2mat(calc(l)) ));
        end
    end
end


% Plot features with parameters

feats = [ ...
    EMGFeature.SSC,  ...
    EMGFeature.WAMP, ...
    EMGFeature.ZC    ...
];

for i = 1:length(feats)
    
    figure(i); clf;
    
    for channel = 1:2
        
        subplot(210+channel); hold on;
        
        title(feats(i).name);
        xlabel('Value');

        val = 0:0.0005:0.05;

        if feats(i) == EMGFeature.SSC
            val = 0:0.00001:0.001;
        elseif feats(i) == EMGFeature.WAMP
            val = 0:0.0001:0.02;
        elseif feats(i) == EMGFeature.ZC
            val = 0:0.0001:0.02;
        end

        for grp = 1:length(signals)
            
            avgs = zeros(1, length(val));
            stds = zeros(1, length(val));
            
            for v = 1:length(val)
                x = [];
                for n = 1:length(signals{grp})
                    x = [ x, feats(i).extract( ...
                        signals{grp}{n}(:,channel), val(v)) ]; %#ok<AGROW>
                end
                avgs(v) = mean(x);
                stds(v) = std(x);
            end

            plot(val, avgs, char(colors(grp)));
        end
        
        hold off;
    end
    
    legend('IF', 'OF', 'RG', 'SS');
end

