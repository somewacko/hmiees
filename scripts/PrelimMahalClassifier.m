% PrelimMahalClassifier.m
% Flynn, Michael
%
%   Script to test a preliminary Mahalanobis classification procedure.
%
%   Each signal is either a noisy sine, sawtooth, square, or rand
%   signal from -2 to 2 and the same frequency. The classifier relies 
%   on mean absolute value, willison amplitudes, zero crossings, and
%   waveform length to determine an input signals's similarity to the
%   reference.
%
%   Note that for the square signal, the amplitude for the square wave
%   is reduced and the noise level is increased. This is to get the
%   signal to have an indeterminate number of zero crossings, as
%   otherwise each signal would have the same number of zc's, which
%   would introduce errors in the mahal() calculation for the
%   inverse covariance matrix.


% Reference signals

t = 0:0.01:10;
t = rot90(t, 3); % Make vertical

num_signals = 10;

sine_ref_signals = zeros(length(t), num_signals);
sawt_ref_signals = zeros(length(t), num_signals);
sqre_ref_signals = zeros(length(t), num_signals);
rand_ref_signals = zeros(length(t), num_signals);

for i = 1:8
    sine_ref_signals(:,i) = sin(2*t)      + 2*rand(length(t), 1) - 1;
    sawt_ref_signals(:,i) = sawtooth(2*t) + 2*rand(length(t), 1) - 1;
    sqre_ref_signals(:,i) = square(2*t)/2 + 3*rand(length(t), 1) - 1.5;
    rand_ref_signals(:,i) = 4 * rand(length(t), 1) - 2;
end


% Input signals

sine_signal = sin(2*t)      + 2*rand(length(t), 1) - 1;
sawt_signal = sawtooth(2*t) + 2*rand(length(t), 1) - 1;
sqre_signal = square(2*t)/2 + 3*rand(length(t), 1) - 1.5;
rand_signal = 4 * rand(length(t), 1) - 2;


% Create and train classifier

classifier = EMGClassifier(length(t), []);

sine_gesture = classifier.register_gesture('Sine');
sawt_gesture = classifier.register_gesture('Sawtooth');
sqre_gesture = classifier.register_gesture('Square');
rand_gesture = classifier.register_gesture('Random');

classifier.train(sine_ref_signals, sine_gesture);
classifier.train(sawt_ref_signals, sawt_gesture);
classifier.train(sqre_ref_signals, sqre_gesture);
classifier.train(rand_ref_signals, rand_gesture);


% Plot input signals for reference

subplot(221); plot(t, sine_signal);
xlim([min(t) max(t)]); title('Sine input');

subplot(222); plot(t, sawt_signal);
xlim([min(t) max(t)]); title('Sawtooth input');

subplot(223); plot(t, sqre_signal);
xlim([min(t) max(t)]); title('Square input');

subplot(224); plot(t, rand_signal);
xlim([min(t) max(t)]); title('Random input');


% Classify the signals

fprintf('\n');

[gesture, distance] = classifier.classify(sine_signal);

fprintf('Sine wave is a...\n');
fprintf('\tClass:    %s\n', gesture.name);
fprintf('\tDistance: %0.2f\n', distance);

[gesture, distance] = classifier.classify(sawt_signal);

fprintf('Sawtooth wave is a...\n');
fprintf('\tClass:    %s\n', gesture.name);
fprintf('\tDistance: %0.2f\n', distance);

[gesture, distance] = classifier.classify(sqre_signal);

fprintf('Square wave is a...\n');
fprintf('\tClass:    %s\n', gesture.name);
fprintf('\tDistance: %0.2f\n', distance);

[gesture, distance] = classifier.classify(rand_signal);

fprintf('Random wave is a...\n');
fprintf('\tClass:    %s\n', gesture.name);
fprintf('\tDistance: %0.2f\n', distance);

fprintf('\n');


