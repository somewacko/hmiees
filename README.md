# EMG Classifier

Matlab classes to process and classify EMG signals, with the ultimate goal of leading to a real-time classifier that interfaces with a wireless external sensor device.

Part of a 2015 VCU Engineering Capstone Design project, *Human-Machine Interfacing via Epidermal Electronic Systems*, which will be displayed at the Science Museum of Virginia on April 24, 2015.

#### Using the classifier:

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

| Name | Description |
| ---- | ----------- |
| *cemg*       | C code for the classifier device
| *classifier* | The classifier and other related classes.
| *data*       | Pre-recorded data to test and experiment with. Includes functions to access
| *func*       | All Matlab functions used with the program and scripts.
| *gui*        | All code and figures for the GUI program.
| *scripts*    | Scripts used to develop and test the classifier.


