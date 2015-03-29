function successes = TestClassifierTwoChannel( ...
    signals, sampling_period, lambda, names ...
)
    % Tests the classifier with a group of two-channel signals.
    
    % signals         : The group of signals to test in a cell array.
    % sampling_period : The sampling period for the classifier.
    
    % successes       : An array of the success rates for each
    %                   individual gesture.

    successes = zeros(1, size(signals, 2));

    for test_group = 1:size(signals, 2)
        for test_signal = 1:size(signals{test_group}, 2)

            classifier = EMGClassifier(sampling_period);
            if ~isempty(lambda)
                classifier.lambda = lambda; end
            test_gesture = [];

            for i = 1:size(signals, 2)

                if i == test_group
                    % If test directory, train using all signals
                    % except the test signal

                    test_signals_copy = signals{i};
                    test_signals_copy(:,test_signal) = [];

                    test_gesture = classifier.register_gesture( ...
                        char(names(i))                          ...
                    );
                
                    for k = 1:length(test_signals_copy)
                        classifier.train_multiple_channels( ...
                            test_signals_copy{k}, test_gesture);
                    end
                else                
                    gesture = classifier.register_gesture( ...
                        char(names(i))                     ...
                    );
                
                    signals_copy = signals{i};
                    
                    for k = 1:length(signals_copy)
                        classifier.train_multiple_channels( ...
                            signals_copy{k}, gesture);
                    end
                end
            end

            sig = signals{test_group}{test_signal};
            [gesture, ~] = classifier.classify(sig);

            if gesture == test_gesture
                successes(test_group) = successes(test_group) + 1;
            else
                fprintf('\tMistook %s for %s\n', ...
                    test_gesture.name, gesture.name);
            end
        end

        successes(test_group) = 100 * successes(test_group) ...
                / size(signals{test_group}, 2);
    end
end

