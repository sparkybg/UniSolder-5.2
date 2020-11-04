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
ifeq "$(wildcard nbproject/Makefile-local-PIC32_Standalone.mk)" "nbproject/Makefile-local-PIC32_Standalone.mk"
include nbproject/Makefile-local-PIC32_Standalone.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32_Standalone
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
	${MAKE}  -f nbproject/Makefile-PIC32_Standalone.mk dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX534F064H
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
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/b2d2ae3bab7160ce3faae3118a86c8da0dd39fd3.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/695168b8e4373ef66d79a87bb2d8e9a1da432172.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/cc607c3270e6c80a173ba2be7864eaf19e452dee.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/5a51a66fe5f0d7b41d1d2bb3ec14c3f074d1a48a.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/17bc60aebf3b662b19fa37411c52401ec070d1f3.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/a9214b3541f956925aba4050ffdc52b0a723632e.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/20787be72823b56a8b93f03d6570bab6ca158758.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/e67a05e5695a00293fbab7e53367bf39247ff269.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/3eb934a0c92095f7fe9feb70ffd22eb4f8eb1fc9.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/io.o: io.c  .generated_files/6c6cdca499c30a0299469bb28c42e7685b60b88.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/4f26fc20421907c5d9ea76d24d57a73da3db8c44.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PIC32MX534F064H.o: PIC32MX534F064H.c  .generated_files/b78f78aebe64b88bf59b7b15c18bf9e72a12a70e.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX534F064H.o.d" -o ${OBJECTDIR}/PIC32MX534F064H.o PIC32MX534F064H.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/2fb1b53e241612dc1def60160101d0abd94b1819.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/df81e55c382a3b81c309fa7668144390ad9ec4bf.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/b140eb69e88fb793c5a3439f1eee2d33726fbd99.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/fc7599dbeb9d6ce449893c3cb3907123cd5c3d5a.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/db0b6768bf7842b0e2bc78467ca8062b9c369a34.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/9a2c2107bf5585441c0111b970f165ab42f48781.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/8934f455a6cd64fee204c7997e67d01d605e91cc.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/31d0a06f0afc9c6d2f023c508be3bc7f575bebe4.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/main.o: main.c  .generated_files/f5f712a7848936fa8343a7dd5c2a6d07fbb82b3f.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/490aa18d13a3efddf285140f1a0dea506591fcf3.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/78d7a59e691fbfd458a7f1001b31e8d668fbc40f.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/a023619486aae85fba78d0550c12cb208fabebc7.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/io.o: io.c  .generated_files/34c0064c886ae1a068c348b98ac47b259928a95d.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/b342e05574b49a99bc356f9b5786cd544034f74b.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/PIC32MX534F064H.o: PIC32MX534F064H.c  .generated_files/8d46f4c0c50885f91a71235e36758d00dab54480.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX534F064H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX534F064H.o.d" -o ${OBJECTDIR}/PIC32MX534F064H.o PIC32MX534F064H.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/309d0d1dd801976251c5b28561d2df6f97cfc5eb.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/81fb43c2ac7847a76a1b830807df258524d938db.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/996f9513432978282eccd83593501d3676380df7.flag .generated_files/abe17b4284e9450d4e0fe8491b242cd2e8c4eb40.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -Os -D_SUPPRESS_PLIB_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)    
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_Standalone=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map" 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32_Standalone
	${RM} -r dist/PIC32_Standalone

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
