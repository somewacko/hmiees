function features = PrelimFeatures(signals, wamp_thres, zc_thres)
% Feature extraction that creates a column vector for MAV, WAMP,
% ZC, and WL features. To be used with preliminary Mahal-based
% classifier. If more than one signal is provided, each signal's
% features will be in its own column.

features = [ mean_absolute_value(signals);
             willison_amplitude(signals, wamp_thres);
             zero_crossings(signals, zc_thres);
             waveform_length(signals)
];

end
