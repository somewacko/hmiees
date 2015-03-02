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


% Make feature vectors for the reference and input signals

wamp = 0.1;  % Willison Amplitude threshold
zc   = 0.05; % Zero-Crossing threshold

sine_ref_feats = PrelimFeatures(sine_ref_signals, wamp, zc);
sawt_ref_feats = PrelimFeatures(sawt_ref_signals, wamp, zc);
sqre_ref_feats = PrelimFeatures(sqre_ref_signals, wamp, zc);
rand_ref_feats = PrelimFeatures(rand_ref_signals, wamp, zc);

sine_feats = PrelimFeatures(sine_signal, wamp, zc);
sawt_feats = PrelimFeatures(sawt_signal, wamp, zc);
sqre_feats = PrelimFeatures(sqre_signal, wamp, zc);
rand_feats = PrelimFeatures(rand_signal, wamp, zc);


% Plot input signals for reference

subplot(221); plot(t, sine_signal);
xlim([min(t) max(t)]); title('Sine input');

subplot(222); plot(t, sawt_signal);
xlim([min(t) max(t)]); title('Sawtooth input');

subplot(223); plot(t, sqre_signal);
xlim([min(t) max(t)]); title('Square input');

subplot(224); plot(t, rand_signal);
xlim([min(t) max(t)]); title('Random input');


% Get distance for each input/ref pair and print results

% Note: Make sure inputs for Matlab's mahal() function are transposed.

fprintf('\nMahalanobis distances (Lowest is most similar)\n\n');

fprintf('With Sine Reference:\n');
fprintf('\tSine:     %0.2f\n', mahal(sine_feats', sine_ref_feats'));
fprintf('\tSawtooth: %0.2f\n', mahal(sawt_feats', sine_ref_feats'));
fprintf('\tSquare:   %0.2f\n', mahal(sqre_feats', sine_ref_feats'));
fprintf('\tRandom:   %0.2f\n', mahal(rand_feats', sine_ref_feats'));

fprintf('With Sawtooth Reference:\n');
fprintf('\tSine:     %0.2f\n', mahal(sine_feats', sawt_ref_feats'));
fprintf('\tSawtooth: %0.2f\n', mahal(sawt_feats', sawt_ref_feats'));
fprintf('\tSquare:   %0.2f\n', mahal(sqre_feats', sawt_ref_feats'));
fprintf('\tRandom:   %0.2f\n', mahal(rand_feats', sawt_ref_feats'));

fprintf('With Square Reference:\n');
fprintf('\tSine:     %0.2f\n', mahal(sine_feats', sqre_ref_feats'));
fprintf('\tSawtooth: %0.2f\n', mahal(sawt_feats', sqre_ref_feats'));
fprintf('\tSquare:   %0.2f\n', mahal(sqre_feats', sqre_ref_feats'));
fprintf('\tRandom:   %0.2f\n', mahal(rand_feats', sqre_ref_feats'));

fprintf('With Rand Reference:\n');
fprintf('\tSine:     %0.2f\n', mahal(sine_feats', rand_ref_feats'));
fprintf('\tSawtooth: %0.2f\n', mahal(sawt_feats', rand_ref_feats'));
fprintf('\tSquare:   %0.2f\n', mahal(sqre_feats', rand_ref_feats'));
fprintf('\tRandom:   %0.2f\n', mahal(rand_feats', rand_ref_feats'));

fprintf('\n');


