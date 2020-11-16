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
	${MAKE}  -f nbproject/Makefile-PIC32_Standalone.mk dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/e9346fddf62f06186a7071ac653665a32f3205cd.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/3eac3b7fda1077cc37915ae2ed6f97bc8f0c8bf.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/53bf95c78f529bbc7e736bf2bdb63845007d2a7.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/d93db5f51e3e1cfe01c1c3616eb7bdb38c455234.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/d7b4167cd1dcb4af6ebf0c39bcc8a33a6d9b0e37.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/91abb40492fec1f465c10337d63e4f564d0dfff6.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/dbccbae7a7548d6470ef285421201954729c15d8.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/5326f262cf29a951e257c57efd74f1cc70ee1d7.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/513ec8399d30506ac5b0c9239fd5ca25d02a92d9.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/1866a136a34e8c524bb4ff5f887fb693e0d758ec.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/eaca3b1badacf6bdf042a476e81b0253d0aae1d5.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/e1d0c51a1447726c457ac540d9b141ea3eef56c1.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/e6f859795e6ca5159c10afe6bc8f05ed5ca936de.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/77351cd897e35de6af562230748ba91301406b53.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorMath.o: sensorMath.c  .generated_files/1b34e9fd7f8d12212e47a7d6a2ddd06881410682.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorMath.o.d 
	@${RM} ${OBJECTDIR}/sensorMath.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/sensorMath.o.d" -o ${OBJECTDIR}/sensorMath.o sensorMath.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/fc4b0121a9c3c00ed18f7c23a620b9c87f25cf2b.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/88c249d9988d30f5f5dc361e642aa97d939774a7.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/49de02a5feb35eab46e2a2d556bf9ed1babe4c96.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/c2be29459f498333ad33cd980854e8e384ff7228.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/35fecfc158202436f58316efc6a8a15782300214.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_hal_pic24.o: usb/usb_hal_pic24.c  .generated_files/9dc00ea5796844d63f10ba3a0783d0d76711c8a7.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_hal_pic24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/usb/usb_hal_pic24.o.d" -o ${OBJECTDIR}/usb/usb_hal_pic24.o usb/usb_hal_pic24.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/9d755fc5d7dda00d5bf0cc8fc9690207d24873df.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/isr.o: isr.c  .generated_files/91239ddb8c6e38ac16e331ce5a655250f0cb5674.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/isr.o.d 
	@${RM} ${OBJECTDIR}/isr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/isr.o.d" -o ${OBJECTDIR}/isr.o isr.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/iron.o: iron.c  .generated_files/52fec9bba51ecbbe058735b320334a1371ad7db8.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/iron.o.d 
	@${RM} ${OBJECTDIR}/iron.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/iron.o.d" -o ${OBJECTDIR}/iron.o iron.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PID.o: PID.c  .generated_files/3c8059584499fcf5e64ee0b7180e34833cc5178f.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PID.o.d 
	@${RM} ${OBJECTDIR}/PID.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PID.o.d" -o ${OBJECTDIR}/PID.o PID.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/257f33cc5927e2d6a086f4cf8820dcb6907b5719.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/menu.o: menu.c  .generated_files/10e1dd68e20dba32248cfccb4dcbf9c2e9489caf.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/menu.o.d 
	@${RM} ${OBJECTDIR}/menu.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/menu.o.d" -o ${OBJECTDIR}/menu.o menu.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EEP.o: EEP.c  .generated_files/63ac501383ea0076d21a9c9e6e37d94c28b404d3.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEP.o.d 
	@${RM} ${OBJECTDIR}/EEP.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/EEP.o.d" -o ${OBJECTDIR}/EEP.o EEP.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/5047593605765e5a04cafd3214d0a2d5ca392858.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/pars.o: pars.c  .generated_files/cb9c1207360bab64eebe75453a500ee6684cb244.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pars.o.d 
	@${RM} ${OBJECTDIR}/pars.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/pars.o.d" -o ${OBJECTDIR}/pars.o pars.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/sensorMath.o: sensorMath.c  .generated_files/ccd26bdde18e0c4337aa1eda476b4b786b3e86d.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sensorMath.o.d 
	@${RM} ${OBJECTDIR}/sensorMath.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/sensorMath.o.d" -o ${OBJECTDIR}/sensorMath.o sensorMath.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/5fd437f202e53140ab117d4ce5541d71754d7319.flag .generated_files/1cd795e86e0e1b2131ee7aebeffccbb30c0217ce.flag
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -O2 -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/US_Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32_Standalone=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
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
