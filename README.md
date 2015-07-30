# Human-Machine Interfacing via Epidermal Electronic Systems

A VCU Engineering Capstone Design project to measure and classify EMG signals to control an external system in realtime. Awarded *Excellence in Design* at the 2015 Capstone Expo for having one of the most exemplary projects in the ECE department.

Our poster describing the project in more detail can be found [here](https://drive.google.com/file/d/0B_jWp8d11aB5cVhoM2UyTEJtTkE/view?usp=sharing).

#### Using the Matlab classifier:

```matlab

    reference_signals = 2*rand(200, 10)-1;
    test_signal       = 2*rand(200,  1)-1;
    
    classifier = EMGClassifier(200);
    
    % Specifying features is optional
    classifier.features = [
        EMGFeature.MAV,  ...
        EMGFeature.WAMP, ...
        EMGFeature.ZC,   ...
        EMGFeature.WL    ...
    ];
    
    example_gesture = classifier.register_gesture('The Example Gesture');
    classifier.train(reference_signals, example_gesture);
    [gesture, distance] = classifier.classify(test_signal);
    
    fprintf('Classifier recognized %s with a distance of %0.2f\n', ...
        gesture.name, distance);
```

#### Directories:

| Name     | Description |
| -------- | ----------- |
| *cemg*   | C code for the classifier devices.
| *ctest*  | Tests for the C classifier.
| *data*   | Pre-recorded data to test and experiment with. Includes functions to access
| *matlab* | Scripts used to develop and test the classifier.


