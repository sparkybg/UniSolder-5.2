REM set path=%path%;"C:\Program Files (x86)\Microchip\MPLABX\v4.20\gnuBins\GnuWin32\bin"
make -f nbproject/Makefile-PIC32_with_bootloader.mk SUBPROJECTS= .build-conf
make -f nbproject/Makefile-PIC32_Standalone.mk SUBPROJECTS= .build-conf
make -f nbproject/Makefile-PIC32_NoOptimization.mk SUBPROJECTS= .build-conf