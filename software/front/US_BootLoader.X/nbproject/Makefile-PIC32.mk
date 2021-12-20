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
ifeq "$(wildcard nbproject/Makefile-local-PIC32.mk)" "nbproject/Makefile-local-PIC32.mk"
include nbproject/Makefile-local-PIC32.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC32
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=usb/usb_descriptors.c usb/usb_device.c usb/usb_driver.c usb/usb_function_hid.c main.c io.c crc.c OLED.c PIC32MX564F128H.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/usb/usb_descriptors.o ${OBJECTDIR}/usb/usb_device.o ${OBJECTDIR}/usb/usb_driver.o ${OBJECTDIR}/usb/usb_function_hid.o ${OBJECTDIR}/main.o ${OBJECTDIR}/io.o ${OBJECTDIR}/crc.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/PIC32MX564F128H.o
POSSIBLE_DEPFILES=${OBJECTDIR}/usb/usb_descriptors.o.d ${OBJECTDIR}/usb/usb_device.o.d ${OBJECTDIR}/usb/usb_driver.o.d ${OBJECTDIR}/usb/usb_function_hid.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/io.o.d ${OBJECTDIR}/crc.o.d ${OBJECTDIR}/OLED.o.d ${OBJECTDIR}/PIC32MX564F128H.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/usb/usb_descriptors.o ${OBJECTDIR}/usb/usb_device.o ${OBJECTDIR}/usb/usb_driver.o ${OBJECTDIR}/usb/usb_function_hid.o ${OBJECTDIR}/main.o ${OBJECTDIR}/io.o ${OBJECTDIR}/crc.o ${OBJECTDIR}/OLED.o ${OBJECTDIR}/PIC32MX564F128H.o

# Source Files
SOURCEFILES=usb/usb_descriptors.c usb/usb_device.c usb/usb_driver.c usb/usb_function_hid.c main.c io.c crc.c OLED.c PIC32MX564F128H.c



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
	${MAKE}  -f nbproject/Makefile-PIC32.mk dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX564F128H
MP_LINKER_FILE_OPTION=,--script="bootloader.ld"
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
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/flags/PIC32/ee3f2252dc1adbe4ab4ea154ce3b84fc172607ad .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/flags/PIC32/ea1f4b86e32f3dcca9db1488efbba417a7f8109a .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/flags/PIC32/f6094e3299d214fe8fd8f4ce3deed53ffbdfea9f .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/flags/PIC32/16638a66eb05015be59adb77dec5cd38f3562521 .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/PIC32/6e96b43861176e9dd7182e84d8967b22d3da338f .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/flags/PIC32/a560bc1383519fc6a59b44a919f568349e15b890 .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/crc.o: crc.c  .generated_files/flags/PIC32/71105bc19753b526494dba4e62ef3bbd1c853fd5 .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/crc.o.d 
	@${RM} ${OBJECTDIR}/crc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/crc.o.d" -o ${OBJECTDIR}/crc.o crc.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/PIC32/b0900d23cf4e84818f18683dc991ce1e8cf4806d .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/flags/PIC32/b35bfea3ed4006b24d1d24431413c6d246e17c1d .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/usb/usb_descriptors.o: usb/usb_descriptors.c  .generated_files/flags/PIC32/4edc5e5bdecf9ac74135380c7a93ac38f5fce6fa .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_descriptors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_descriptors.o.d" -o ${OBJECTDIR}/usb/usb_descriptors.o usb/usb_descriptors.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_device.o: usb/usb_device.c  .generated_files/flags/PIC32/ee5c16361f7e1897c2c594fc8abcd41093db1654 .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_device.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_device.o.d" -o ${OBJECTDIR}/usb/usb_device.o usb/usb_device.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_driver.o: usb/usb_driver.c  .generated_files/flags/PIC32/285d3a442c6b96fffa9a3057c446c66466a2c8fd .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_driver.o.d" -o ${OBJECTDIR}/usb/usb_driver.o usb/usb_driver.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/usb/usb_function_hid.o: usb/usb_function_hid.c  .generated_files/flags/PIC32/eb6d1f73fc6d6283cbace727bb0bb7379d51248f .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}/usb" 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o.d 
	@${RM} ${OBJECTDIR}/usb/usb_function_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/usb/usb_function_hid.o.d" -o ${OBJECTDIR}/usb/usb_function_hid.o usb/usb_function_hid.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/PIC32/100250e33a4317c06a5126a1001e4648e8a77b82 .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/io.o: io.c  .generated_files/flags/PIC32/7941d771dc6f923f53971edd9b4fb89a8a6ae8cb .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/io.o.d 
	@${RM} ${OBJECTDIR}/io.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/io.o.d" -o ${OBJECTDIR}/io.o io.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/crc.o: crc.c  .generated_files/flags/PIC32/5b4f33124afe4671812ec9599838f094894436cc .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/crc.o.d 
	@${RM} ${OBJECTDIR}/crc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/crc.o.d" -o ${OBJECTDIR}/crc.o crc.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OLED.o: OLED.c  .generated_files/flags/PIC32/f4a114162fcdc4f4b2d824b8f80ccd928955cee8 .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OLED.o.d 
	@${RM} ${OBJECTDIR}/OLED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/OLED.o.d" -o ${OBJECTDIR}/OLED.o OLED.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PIC32MX564F128H.o: PIC32MX564F128H.c  .generated_files/flags/PIC32/ac1496e6308d070d78442e0a461daee0ba45e2db .generated_files/flags/PIC32/f7a9c8f19abb2154f44cee6a025a1004e30e288d
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o.d 
	@${RM} ${OBJECTDIR}/PIC32MX564F128H.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -mips16 -mno-float -Os -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -Wall -MP -MMD -MF "${OBJECTDIR}/PIC32MX564F128H.o.d" -o ${OBJECTDIR}/PIC32MX564F128H.o PIC32MX564F128H.c    -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    bootloader.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mips16 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   bootloader.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mips16 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_PIC32=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/US_BootLoader.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC32
	${RM} -r dist/PIC32

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
