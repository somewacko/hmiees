#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../dspic/Test.c ../cemg/emg_features.c ../cemg/emg_filter.c ../cemg/emg_onset.c ../cemg/emg_processing.c ../cemg/emg_signal.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2118147700/Test.o ${OBJECTDIR}/_ext/761107349/emg_features.o ${OBJECTDIR}/_ext/761107349/emg_filter.o ${OBJECTDIR}/_ext/761107349/emg_onset.o ${OBJECTDIR}/_ext/761107349/emg_processing.o ${OBJECTDIR}/_ext/761107349/emg_signal.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2118147700/Test.o.d ${OBJECTDIR}/_ext/761107349/emg_features.o.d ${OBJECTDIR}/_ext/761107349/emg_filter.o.d ${OBJECTDIR}/_ext/761107349/emg_onset.o.d ${OBJECTDIR}/_ext/761107349/emg_processing.o.d ${OBJECTDIR}/_ext/761107349/emg_signal.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2118147700/Test.o ${OBJECTDIR}/_ext/761107349/emg_features.o ${OBJECTDIR}/_ext/761107349/emg_filter.o ${OBJECTDIR}/_ext/761107349/emg_onset.o ${OBJECTDIR}/_ext/761107349/emg_processing.o ${OBJECTDIR}/_ext/761107349/emg_signal.o

# Source Files
SOURCEFILES=../dspic/Test.c ../cemg/emg_features.c ../cemg/emg_filter.c ../cemg/emg_onset.c ../cemg/emg_processing.c ../cemg/emg_signal.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP202
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP202.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2118147700/Test.o: ../dspic/Test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118147700" 
	@${RM} ${OBJECTDIR}/_ext/2118147700/Test.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118147700/Test.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../dspic/Test.c  -o ${OBJECTDIR}/_ext/2118147700/Test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2118147700/Test.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118147700/Test.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_features.o: ../cemg/emg_features.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_features.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_features.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_features.c  -o ${OBJECTDIR}/_ext/761107349/emg_features.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_features.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_features.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_filter.o: ../cemg/emg_filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_filter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_filter.c  -o ${OBJECTDIR}/_ext/761107349/emg_filter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_filter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_filter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_onset.o: ../cemg/emg_onset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_onset.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_onset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_onset.c  -o ${OBJECTDIR}/_ext/761107349/emg_onset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_onset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_onset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_processing.o: ../cemg/emg_processing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_processing.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_processing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_processing.c  -o ${OBJECTDIR}/_ext/761107349/emg_processing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_processing.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_processing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_signal.o: ../cemg/emg_signal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_signal.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_signal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_signal.c  -o ${OBJECTDIR}/_ext/761107349/emg_signal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_signal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_signal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/2118147700/Test.o: ../dspic/Test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118147700" 
	@${RM} ${OBJECTDIR}/_ext/2118147700/Test.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118147700/Test.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../dspic/Test.c  -o ${OBJECTDIR}/_ext/2118147700/Test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2118147700/Test.o.d"        -g -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118147700/Test.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_features.o: ../cemg/emg_features.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_features.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_features.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_features.c  -o ${OBJECTDIR}/_ext/761107349/emg_features.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_features.o.d"        -g -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_features.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_filter.o: ../cemg/emg_filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_filter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_filter.c  -o ${OBJECTDIR}/_ext/761107349/emg_filter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_filter.o.d"        -g -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_filter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_onset.o: ../cemg/emg_onset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_onset.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_onset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_onset.c  -o ${OBJECTDIR}/_ext/761107349/emg_onset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_onset.o.d"        -g -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_onset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_processing.o: ../cemg/emg_processing.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_processing.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_processing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_processing.c  -o ${OBJECTDIR}/_ext/761107349/emg_processing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_processing.o.d"        -g -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_processing.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/761107349/emg_signal.o: ../cemg/emg_signal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/761107349" 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_signal.o.d 
	@${RM} ${OBJECTDIR}/_ext/761107349/emg_signal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../cemg/emg_signal.c  -o ${OBJECTDIR}/_ext/761107349/emg_signal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/761107349/emg_signal.o.d"        -g -omf=elf -O0 -I"C:/Users/sharpleysm/Desktop/repository/emg-classifier/dspic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/761107349/emg_signal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Feature_Extraction.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
