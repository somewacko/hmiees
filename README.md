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
| *classifier* | The classifier and other related classes.
| *data*       | Pre-recorded data to test and experiment with. Includes functions to access
| *func*       | All Matlab functions used with the program and scripts.
| *gui*        | All code and figures for the GUI program.
| *scripts*    | Scripts used to develop and test the classifier.

#### Files:

| Name | Directory | Description |
| ---- | --------- | ----------- |
| EMGClassifier.m  | *classifier* | Top-level classifier class.
| EMGFeature.m     | *classifier* | Enumerated class to represent and extract individual features.
| EMGGesture.m     | *classifier* | Class that represents a recognizable gesture and holds training data.
| get_emg_group.m  | *data* | Function to read multiple 24-bit .raw signals from a specified directory.
| get_emg_signal.m | *data* | Function to read a single 24-bit .raw signal from a specified file.
| mean_absolute_value.m       | *func* | MAV feature.
| mean_absolute_value_slope.m | *func* | MAVSLP feature.
| waveform_length.m           | *func* | WL feature.
| willison_amplitude.m        | *func* | WAMP feature.
| zero_crossings.m            | *func* | ZC feature.
| EMGGui.fig   | *gui* | GUIDE GUI figure.
| EMGGui.m     | *gui* | Entry point for the GUI program.
| EMGSession.m | *gui* | Class that holds data and functions for EMG classification within the GUI program.
| EMGClassificationTest.m | *scripts* | Script that measures the success rate of the classifier with signals from the data directory.
| EMGFeatureAnalysis.m    | *scripts* | Script that computes the mean, variance, and standard deviation for different features among EMG files. *Note: Needs to be updated to only extract features from onset of motion*
| PrelimMahalClassifier.m | *scripts* | Script to test classifier with synthesized non-EMG signals.

#### To do:

- EMG Classifier
    - Full feature set.
    - Real-time onset of movement detection.
    - Allow for multiple channels of features.
- Data
	- More data that includes multiple signal channels from different muscles.
- GUI Program
    - Additional options to sample and process the input signal.
    - A GUI segway for training the classifier.
    - Ability to input files or export/import training data.
    - Ability to interface with our final EMG sensor device through Bluetooth.
- Eventual
    - C/C++ port of feature extraction for use with the EMG sensor device.
    - Drivers for interfacing with other systems or software. (e.g: Allowing this to control a video game, controlling an external robot, etc.)
    - Port of classifier to a framework which can be integrated and extended upon in another project without the use of Matlab.


