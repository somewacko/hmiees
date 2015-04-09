emg-ctest: emg_ctest.c \
	cemg/emg_features.h   cemg/emg_features.c   \
	cemg/emg_filter.h     cemg/emg_filter.c     \
	cemg/emg_onset.h      cemg/emg_onset.c      \
	cemg/emg_processing.h cemg/emg_processing.c \
	cemg/emg_signal.h \

	clang --std=c11 emg_ctest.c \
		cemg/emg_features.c cemg/emg_filter.c cemg/emg_onset.c cemg/emg_processing.c \
	-o emg-ctest