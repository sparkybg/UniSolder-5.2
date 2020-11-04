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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
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
SOURCEFILES_QUOTED_IF_SPACED=usb/usb_descriptors.c usb/usb_device.c usb/usb_driver.c usb/usb_function_hid.c usb/usb_hal_pic24.c main.c isr.c iron.c PID.c io.c menu.c PIC32MX534F064H.c EEP.c OLED.c pars.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/usb/usb_descriptors.o ${OBJECTDIR}/usb/usb_device.o ${OBJECTDIR}/usb/usb_driver.o ${OBJECTDIR}/usb/usb_function_hid.o ${OBJECTDIR}/usb/usb_hal_pic24.o ${OBJECTDIR}/main.o ${OBJECTDIR}/isr.o ${OBJECTDIR}/iron.o ${OBJECTDIR}/PID.o ${OBJECTDIR}/io.o ${OBJECTDIR}/menu.o ${OBJECTDIR}/PIC32MX534F064H.o ${OBJECTDIR}/EEP.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/pars.o
POSSIBLE_DEPFILES=${OBJECTDIR}/usb/usb_descriptors.o.d ${OBJECTDIR}/usb/usb_device.o.d ${OBJECTDIR}/usb/usb_driver.o.d ${OBJECTDIR}/usb/usb_function_hid.o.d ${OBJECTDIR}/usb/usb_hal_pic24.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/isr.o.d ${OBJECTDIR}/iron.o.d ${OBJECTDIR}/PID.o.d ${OBJECTDIR}/io.o.d ${OBJECTDIR}/menu.o.d ${OBJECTDIR}/PIC32MX534F064H.o.d ${OBJECTDIR}/EEP.o.d ${OBJECTDIR}/OLED.o.d ${OBJECTDIR}/pars.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/usb/usb_descriptors.o ${OBJECTDIR}/usb/usb_device.o ${OBJECTDIR}/usb/usb_driver.o ${OBJECTDIR}/usb/usb_function_hid.o ${OBJECTDIR}/usb/usb_hal_pic24.o ${OBJECTDIR}/main.o ${OBJECTDIR}/isr.o ${OBJECTDIR}/iron.o ${OBJECTDIR}/PID.o ${OBJECTDIR}/io.o ${OBJECTDIR}/menu.o ${OBJECTDIR}/PIC32MX534F064H.o ${OBJECTDIR}/EEP.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/pars.o

# Source Files
SOURCEFILES=usb/usb_descriptors.c usb/usb_device.c usb/usb_driver.c usb/usb_function_hid.c usb/usb_hal_pic24.c main.c isr.c iron.c PID.c io.c menu.c PIC32MX534F064H.c EEP.c OLED.c pars.c



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
	${MAKE}  -f nbproject/Makefile-PIC32_with_bootloader.mk dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX534F064H
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
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/509e659fcb181b4e4850c061e1ee5073feed4d8f.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/864251d72b6d113ebeba8f3f62418c44075d38ed.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/554abc827e89a8b3f4def2351cafe0630ffc00ef.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/cd111f16071ba82af553c7cdd9990bfff333f7f3.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/8372f1fcebab7a6b8a2e6b8ea15eeda9e4787041.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/54a9b3c1521bc7b8e5a465f11636ea0edf5bbff0.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/347d9ef77b63ff41e735d5b1ccfed3c4487a7ea8.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/c159f1aeeddbbd1b0cf7c938a3ca6d3b4c27d20e.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/e69a97023510a5b0b09b4d8c2c2941901261098d.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/io.o: io.c  .generated_files/532b1426417aed315339b1240eb37ca699477b3f.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/d17a63039e6e2c76c6616dd98c2c01059b81c90.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PIC32MX534F064H.o: PIC32MX534F064H.c  .generated_files/5ae1e381756f409e8a92b805b4e289fd42fabcc.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX534F064H.o.d" -o ${OBJECTDIR}/PIC32MX534F064H.o PIC32MX534F064H.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/bb2a0b79546f72eff98192552ad21b8fad4b2413.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/2cd754150097f6b5e739d2cb9ee5a36ec25d51f3.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/23b9a0675745711a1bb9ce9890396fbcb89e19e3.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/10a4dbaf2e9b88795f5a2660ae40b8a9b5301d38.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/fffe1efd49ea12c5e1f7ed872ea80892ede8586d.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/ed08614d00aef434596b7e4cdf460ef1678297d7.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/eddb0357b520828d3e4e58569d4bec0f250f55a4.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/be562ca33896adf6f031a051d423c2b6828dbce8.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/a128d19e173534dfaf1475120b65319155e8a00c.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/4857ec84c7584e93b7a7a24f533109ed7ba9c79f.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/ae4c85bc8c5d3c17af1ab92ad168dc5b253fa2d.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/851b899898df088e2712c0e5c0bd30b4daf4e2ac.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/io.o: io.c  .generated_files/3fde17e03242d889a0639524e79f9645caf9ce29.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/e34e72cca23d6ce0ea13aedf476f568683ce8d0e.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PIC32MX534F064H.o: PIC32MX534F064H.c  .generated_files/109073282521ec4cdb7b14b55f9a49f5fd6db4ae.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX534F064H.o.d" -o ${OBJECTDIR}/PIC32MX534F064H.o PIC32MX534F064H.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/90e87a412eb1cb136d6619879954b7a3727d60f5.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/7545795a1306f4bd4ad29a0e7714d3a76bc8c29c.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/a134c98af0eadaf9469f38bd6a3895a61fefa8f4.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -Os -fschedule-insns -fschedule-insns2 -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    firmware.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   firmware.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_with_bootloader=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_with_bootloader
	${RM} -r dist/PIC32_with_bootloader

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
