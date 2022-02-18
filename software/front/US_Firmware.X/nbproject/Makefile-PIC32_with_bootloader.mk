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
ifeq "$(wildcard nbproject/Makefile-local-PIC32_with_bootloader.mk)" "nbproject/Makefile-local-PIC32_with_bootloader.mk"
include nbproject/Makefile-local-PIC32_with_bootloader.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_with_bootloader
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=usb/usb_descriptors.c usb/usb_device.c usb/usb_driver.c usb/usb_function_hid.c usb/usb_hal_pic24.c main.c isr.c iron.c PID.c io.c menu.c EEP.c OLED.c pars.c sensorMath.c PIC32MX564F128H.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/usb/usb_descriptors.o ${OBJECTDIR}/usb/usb_device.o ${OBJECTDIR}/usb/usb_driver.o ${OBJECTDIR}/usb/usb_function_hid.o ${OBJECTDIR}/usb/usb_hal_pic24.o ${OBJECTDIR}/main.o ${OBJECTDIR}/isr.o ${OBJECTDIR}/iron.o ${OBJECTDIR}/PID.o ${OBJECTDIR}/io.o ${OBJECTDIR}/menu.o ${OBJECTDIR}/EEP.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/pars.o ${OBJECTDIR}/sensorMath.o ${OBJECTDIR}/PIC32MX564F128H.o
POSSIBLE_DEPFILES=${OBJECTDIR}/usb/usb_descriptors.o.d ${OBJECTDIR}/usb/usb_device.o.d ${OBJECTDIR}/usb/usb_driver.o.d ${OBJECTDIR}/usb/usb_function_hid.o.d ${OBJECTDIR}/usb/usb_hal_pic24.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/isr.o.d ${OBJECTDIR}/iron.o.d ${OBJECTDIR}/PID.o.d ${OBJECTDIR}/io.o.d ${OBJECTDIR}/menu.o.d ${OBJECTDIR}/EEP.o.d ${OBJECTDIR}/OLED.o.d ${OBJECTDIR}/pars.o.d ${OBJECTDIR}/sensorMath.o.d ${OBJECTDIR}/PIC32MX564F128H.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/usb/usb_descriptors.o ${OBJECTDIR}/usb/usb_device.o ${OBJECTDIR}/usb/usb_driver.o ${OBJECTDIR}/usb/usb_function_hid.o ${OBJECTDIR}/usb/usb_hal_pic24.o ${OBJECTDIR}/main.o ${OBJECTDIR}/isr.o ${OBJECTDIR}/iron.o ${OBJECTDIR}/PID.o ${OBJECTDIR}/io.o ${OBJECTDIR}/menu.o ${OBJECTDIR}/EEP.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/pars.o ${OBJECTDIR}/sensorMath.o ${OBJECTDIR}/PIC32MX564F128H.o

# Source Files
SOURCEFILES=usb/usb_descriptors.c usb/usb_device.c usb/usb_driver.c usb/usb_function_hid.c usb/usb_hal_pic24.c main.c isr.c iron.c PID.c io.c menu.c EEP.c OLED.c pars.c sensorMath.c PIC32MX564F128H.c



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
	${MAKE}  -f nbproject/Makefile-PIC32_with_bootloader.mk ${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX564F128H
MP_LINKER_FILE_OPTION=,--script="firmware.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/flags/PIC32_with_bootloader/ecb1a3b91f83427c83b9dd151254c742379d2505 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/flags/PIC32_with_bootloader/c936226a52b1011e95c6e1bec4208041d23e4766 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/flags/PIC32_with_bootloader/959e4ee074197aa5d8a07aae4d41c15e5f70cdc1 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/flags/PIC32_with_bootloader/7cf30fc3fea1250df0a67230d6b7bc2db02986f6 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/flags/PIC32_with_bootloader/bedfda7d6b7cfff206417433a13f1c3b162d5817 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/PIC32_with_bootloader/8f5d2cfc628eaba5a84c054d8abb29a249a54c84 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/flags/PIC32_with_bootloader/b6a915c22f420885dae56e8380d3125cf09c6a0 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/flags/PIC32_with_bootloader/381118d137d91ea8af08de56e9eb82382992bc2e .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/flags/PIC32_with_bootloader/fdbe90fe2b134c3f254b13030bfd7bbe945b9962 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/flags/PIC32_with_bootloader/9d769568c8c9d9490f1bae88a105e5bd5410c286 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/flags/PIC32_with_bootloader/ded1509a6a317ef32558f1ca500df72e438fa7f .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/flags/PIC32_with_bootloader/a2ab5dc44fbac1c19586f48d232d0233e709f659 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/PIC32_with_bootloader/7fabb778ae3dfb8878dca8f8e4186d06770c0f6d .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/flags/PIC32_with_bootloader/abd7408457ff7f3f562de29b6c4313e16fa9517 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorMath.o: sensorMath.c  .generated_files/flags/PIC32_with_bootloader/27311f13160b76b6ebefa14ad48699a310d8d5e3 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorMath.o.d 
	@${RM} ${OBJECTDIR}/sensorMath.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/sensorMath.o.d" -o ${OBJECTDIR}/sensorMath.o sensorMath.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/flags/PIC32_with_bootloader/e1e30f0ef0a325e0a05ac584dd3129593fdda51e .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/flags/PIC32_with_bootloader/16ad83c769138cc13e06c51712f7f960d7803c4e .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/flags/PIC32_with_bootloader/508b63b7575985bbce5393c39b7d729811c729d7 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/flags/PIC32_with_bootloader/4153520318de08435ac69f3e10861b4bf441510f .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/flags/PIC32_with_bootloader/1040d5699583a5b461868215cd299fcfeb6e89ae .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/flags/PIC32_with_bootloader/6cf91ed2137b7f33072cbf6ce090565d239d5eff .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/PIC32_with_bootloader/1a54581be89f9c236f4b0dc137928803a71f7d33 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/flags/PIC32_with_bootloader/3ee05f529e535747f05eb59f85a035d338533fec .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/flags/PIC32_with_bootloader/6bf7548f6400a6814c29d0bc4e481c1d032e87b6 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/flags/PIC32_with_bootloader/9e5d585a6a16ebd9bf9cf5bc43eaee655c95fcd3 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/flags/PIC32_with_bootloader/65bdb5ec7f16ea623727c7395e79f63c4303ac71 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/flags/PIC32_with_bootloader/1c4eec34ddcc9f7e5b01bf7b65102d73c3c7db51 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/flags/PIC32_with_bootloader/b2a3c35cafb9334ee57693872b9ad4c60416a717 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/PIC32_with_bootloader/f47ca204e99e322265ea304f1d5e844229e5149f .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/flags/PIC32_with_bootloader/a67e26d953aa385d329e7943c050d1700cb03dad .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorMath.o: sensorMath.c  .generated_files/flags/PIC32_with_bootloader/9447e6856932b55a32e0e9611dfe32e6bc64eb7b .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorMath.o.d 
	@${RM} ${OBJECTDIR}/sensorMath.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/sensorMath.o.d" -o ${OBJECTDIR}/sensorMath.o sensorMath.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/flags/PIC32_with_bootloader/ecd98bbf07666fd18bce9ee11a439373be36b69 .generated_files/flags/PIC32_with_bootloader/104b0a473b3b30d72bf5e5d1ca867aa8e4d09ac2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"./" -ffunction-sections -mips16 -O2 -fschedule-insns -fschedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wno-missing-braces -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    firmware.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -mips16 -o ${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   firmware.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -mips16 -o ${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_with_bootloader=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
