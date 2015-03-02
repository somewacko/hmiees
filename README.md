# EMG Classifier

A GUI program for Matlab to analyze and classify an incoming EMG signal. The program reads a single channel through an audio input, analyzes it, and displays information about it.

Currently the program employs a Mahalanobis distance classifier to classify an input based on several features. The program continually scans the signal until an onset of movement is detected, takes a period of samples after the onset, and then classifies the movement.

#### Folders:

- classifier
    The code that makes up the classifier and the GUI.
- data
    Pre-recorded data to test and experiment with.
- func
    All Matlab functions used with the program and scripts.
- scripts
    Scripts used when developing and testing the classifier.

#### To do:

- EMG Classifier
    - Full feature set.
    - Onset of movement detection.
    - Test cases with recored data.
- Additional options to sample and process the input signal.
- A GUI segway for training the classifier.
- Ability to input files or export/import training data.
- Ability to interface with our final EMG device through Bluetooth.
    - Allow for multiple channels of features. 

