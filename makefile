cemg-test: ctest/emg_analysis_test.c \
	cemg/emg_features.h   cemg/emg_features.c   \
	cemg/emg_filter.h     cemg/emg_filter.c     \
	cemg/emg_onset.h      cemg/emg_onset.c      \
	cemg/emg_processing.h cemg/emg_processing.c \
	cemg/emg_signal.h     cemg/emg_signal.c     \

	clang --std=c99 -Icemg ctest/emg_analysis_test.c \
		cemg/emg_features.c cemg/emg_filter.c cemg/emg_onset.c cemg/emg_processing.c cemg/emg_signal.c \
	-o emg-analysis

	clang --std=c99 -Icemg ctest/emg_classifier_test.c \
	-o emg-classifier
