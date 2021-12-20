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
ifeq "$(wildcard nbproject/Makefile-local-PIC32_NoOptimization.mk)" "nbproject/Makefile-local-PIC32_NoOptimization.mk"
include nbproject/Makefile-local-PIC32_NoOptimization.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_NoOptimization
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
	${MAKE}  -f nbproject/Makefile-PIC32_NoOptimization.mk dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX564F128H
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/flags/PIC32_NoOptimization/68b72a633c984fde9be390b2d95fe4baa35e2580 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/flags/PIC32_NoOptimization/46b1176eb4d0601856c7b754b448bf829c5e7296 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/flags/PIC32_NoOptimization/937c5132e939d3854a594360ca29d509b7d818f5 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/flags/PIC32_NoOptimization/4a1d2174c430b04e55289c1722b4e8358731928d .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/flags/PIC32_NoOptimization/9774eb29536ba3caec1fbdf267e12b6e23a7475d .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/PIC32_NoOptimization/a7582758d4f5d52e02b34d3d715c5bd630210eb8 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/flags/PIC32_NoOptimization/82f9a03b5effad756d3a97a480032d64605042d6 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/flags/PIC32_NoOptimization/24d677cfe04868876b67f80777847aeffc844b12 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/flags/PIC32_NoOptimization/2fd3052d227e92b8f1be8052daa24aaa35ad39bf .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/flags/PIC32_NoOptimization/b7d17958b5484defff392b74da22a7ac2695c6b2 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/flags/PIC32_NoOptimization/6d810d302584f60a4b5b474463122d6882ac7dc1 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/flags/PIC32_NoOptimization/3b3af296ef4151f00cf4523f9de0128ede065849 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/PIC32_NoOptimization/d014b952786ebab396012a3ad7cec4b925f5ee09 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/flags/PIC32_NoOptimization/3d4cb03f07d530bd4a748991e3303df0a12ff044 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorMath.o: sensorMath.c  .generated_files/flags/PIC32_NoOptimization/16d2b021128c3cc3c986747866fc0d3e9e55d5e8 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorMath.o.d 
	@${RM} ${OBJECTDIR}/sensorMath.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/sensorMath.o.d" -o ${OBJECTDIR}/sensorMath.o sensorMath.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/flags/PIC32_NoOptimization/b000d859eb7fe1c14b11b63b579265dcac6c6b6a .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/flags/PIC32_NoOptimization/444bb48df44502d89e31b1537b685451560ae5 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/flags/PIC32_NoOptimization/61b2d6bddfca106b2805067553520fd14a98054d .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/flags/PIC32_NoOptimization/54ca79c7888bc9a705ee5350525b290755b72f6e .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/flags/PIC32_NoOptimization/b17572e39832149183b2bd9903a87b0019643346 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/flags/PIC32_NoOptimization/843c9b1dec4df2b12679f1492f49c4a46ffe428b .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/PIC32_NoOptimization/c694b89e7547dbc03155faee161c8117efe66ae3 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/flags/PIC32_NoOptimization/958133e7152a12635f4ec4374e53f1bc59ac1e9d .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/flags/PIC32_NoOptimization/95eb5477602773bf1d43e068cab3bc1db92bd2bc .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/flags/PIC32_NoOptimization/ac762d47427cb877f59ec6972b3913f6d1f25751 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/flags/PIC32_NoOptimization/eb0d0930309d358de42f846a760b8f91154d2bd7 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/flags/PIC32_NoOptimization/95a3b617e06904aa6c8fbbc2a43cf96fe509bf39 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/flags/PIC32_NoOptimization/4b28bc20f77ce2c752bc46dff3488126654d896d .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/PIC32_NoOptimization/a41fa8c304bd6700eeea91888fc1c358d29f41cf .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/flags/PIC32_NoOptimization/a2bf0d0850c070208fd92f41302a83a90894f65b .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorMath.o: sensorMath.c  .generated_files/flags/PIC32_NoOptimization/e8da93f5714224df645483edc54679bbf932dbc3 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorMath.o.d 
	@${RM} ${OBJECTDIR}/sensorMath.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/sensorMath.o.d" -o ${OBJECTDIR}/sensorMath.o sensorMath.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/flags/PIC32_NoOptimization/73172c308c587548ef29076effc99cdd379fe8d8 .generated_files/flags/PIC32_NoOptimization/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"./" -ffunction-sections -mips16 -fno-schedule-insns -fno-schedule-insns2 -fno-common -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_NoOptimization=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_NoOptimization
	${RM} -r dist/PIC32_NoOptimization

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
