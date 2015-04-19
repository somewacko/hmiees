# Simple makefile to compile tests. Recompiles every time.
cemg-test:

	clang --std=c99 -Icemg/ ctest/emg_analysis_test.c \
		cemg/constants.c cemg/emg_features.c cemg/emg_filter.c cemg/emg_onset.c cemg/emg_processing.c cemg/emg_signal.c \
	-o emg-analysis

	clang --std=c99 -Icemg/ ctest/emg_classifier_test.c \
		cemg/constants.c cemg/emg_matrix.c cemg/emg_gesture.c \
	-o emg-classifier
