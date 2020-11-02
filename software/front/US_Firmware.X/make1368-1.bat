@echo off
fixDeps "build/PIC32_with_bootloader/production/usb/usb_device.o.d"  -rsi "C:\Program Files (x86)\Microchip\xc32\v1.21\bin"../  -c "C:\Program Files (x86)\Microchip\xc32\v1.21\bin\xc32-gcc.exe"    -g -x c -c -mprocessor=32MX534F064H -O3 -MMD -MF "build/PIC32_with_bootloader/production/usb/usb_device.o.d" -o build/PIC32_with_bootloader/production/usb/usb_device.o usb/usb_device.c   
