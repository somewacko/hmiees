function successes = TestClassifier(signals, sampling_period)

    % Tests the classifier with a group of signals at a given sampling
    % period.
    
    % signals         : The group of signals to test in a cell array.
    % sampling_period : The sampling period for the classifier.
    
    % successes       : An array of the success rates for each
    %                   individual gesture.

    successes = zeros(1, size(signals, 2));

    for test_group = 1:size(signals, 2)
        for test_signal = 1:size(signals{test_group}, 2)

            classifier = EMGClassifier(sampling_period);
            test_gesture = [];

            for i = 1:size(signals, 2)

                if i == test_group
                    % If test directory, train using all signals
                    % except the test signal

                    test_signals_copy = signals{i};
                    test_signals_copy(:,test_signal) = [];

                    test_gesture = classifier.register_gesture( ...
                        sprintf('%d', i)                        ...
                    );
                    classifier.train(test_signals_copy, test_gesture);
                else                
                    gesture = classifier.register_gesture( ...
                        sprintf('%d', i)                   ...
                    );
                    classifier.train(signals{i}, gesture);
                end
            end

            sig = signals{test_group}(:,test_signal);
            [gesture, ~] = classifier.classify(sig);

            if gesture == test_gesture
                successes(test_group) = successes(test_group) + 1;
            end
        end

        successes(test_group) = 100 * successes(test_group) ...
                / size(signals{test_group}, 2);
    end

end

