# UniSolder - The universal soldering controller  ![License CC-BY-4.0](https://img.shields.io/badge/License-CC--BY--4.0-green.svg)
Control almost any low voltage soldering instrument

<img width=500 align="center" src="/img/UniSolder52_small.jpg"/>

My intention was to build the most universal soldering controller I can think of. It can drive any low voltage (upto 24V) iron with thermocouple or resistive sensor, in series with the heater, or separate.

### A short list of features:
- power: 12-24V, AC or DC (24V 6A toroidal transformer is the best possible power source)
- automatic 1/2, 1/4 and 1/8 power selection, so only simple single winding 24V transformer can drive all the instruments, from the smallest JBC Nano, to the largest JBC C245.
- 2 separate heater control channels
- 2 independent sensor inputs
- current source on any sensor input 3uA - 12mA, with 2 bands (x1, x16) and 256 steps per band
- flexible differential amplifier input selection
- amplifier gain from 0 to 750 in 256 steps
- negative offset selection in 1024 steps
- resistive instrument identification (upto 625 different instruments can be identified by 2 resistors in the connector)
- polynomial floating point voltage/resistance to temperature calculation
- wave shaping to filter out the inductive peaks from series sensor signal
- PID control with power limit
- isolated USB port for firmware updates and live data
- 128x64 OLED display with rich user interface.

### Tested so far with:
- HAKKO T12/T15 (series TC)
- HAKKO FX8801 (PTC)
- PACE TD100 (series TC, the controller also uses the cold junction sensor in the iron's handle)
- PACE TD200 (series TC, the controller also uses the cold junction sensor in the iron's handle)
- JBC C245 (series or separate TC, depends on connection)
- JBC C210 (series TC)
- JBC Microtweezers (PA120/AN120, 2 separate heaters, each with series TC)
- JBC C105/C115 (series TC)
- JBC Nanotweezers (NP115/AN115/NP105/NP105-B, 2 separate heaters, each with series TC)
- WELLER WSP80 (PTC) (This iron was sent to me by a reader of the thread for a previous version of the controller. Thanks, Jaroslaw)
- WELLER WMRT (2 separate heaters, each with separate TC)
- ERSA RT80 (series PTC/heater resistance)
- various chinese cheap irons with separate TC

### Some movies:
- JBC C245: https://www.youtube.com/watch?v=oTdQB4ywDOA&feature=youtu.be
- JBC C210: https://www.youtube.com/watch?v=iyz-EDf-JaY&feature=youtu.be
- T12, JBC C210, JBC Microtweezers: https://www.youtube.com/watch?v=-f0KSU0PJzc&t=70s
- Chinese T12: https://www.youtube.com/watch?v=u588sh-4thg&feature=youtu.be
- Weller WSP80: https://www.youtube.com/watch?v=gd_8w7l8_Bo&feature=youtu.be
- Weller WMRT: https://www.youtube.com/watch?v=eHNJuQEw6XU&feature=youtu.be

### Additional resources
- Valerio made a great git repo with plenty ot usefull information and notes here: https://github.com/valerionew/unisolder-notes
- There are really big thread for this project, where this all started: http://dangerousprototypes.com/forum/index.php?topic=7218.0

## The calibration procedure
- Connect a resistor with well known resistance (0.1%) of around 10ohm between SENSEA and Vout1-
- Go to "CALIBRATION" submenu
- Adjust the calibration trimmer until you get value of "R" as close as possible to the resistance of the resistor, multiplied by 100 (1000 for 10ohm resistor).
- Optionally, press and hold center button for 3+ seconds an release it - the "currect" parameter should now show "1 128" instead of "0 128" it was showing so far
- Connect the same resistor to SENSEB and Vout1-. The Value of "R" should be da same or very close to value shown 2 steps above. If there is a significant difference, there is a problem either with current sources or 0.1% resistors they must be made with.

## My connection layout and the calibration connection in real world:
<img width=500 align="center" src="/img/UniSolder52_Cal_Con-2.jpg"/><br/>

## Connections to different tips/irons:

### 1. HAKKO T12:
 - Outer shell, and heater negative (middle) terminal connected together to Vout1- and EARTH
 - heater positive (bottom terminal) connected to Vout1+ and SENSEA
 - 1k resistor between ID and Vout1-
 - 5.6k resistor between ID and Vout2-

### 2. HAKKO FX8801, HAKKO 907 (original, with PTC sensor):
- Outer shell, PTC negative  and heater negative connected to EARTH, Vout1- and SENSEB
- Heater positive connected to Vout1+
- PTC positive  connected to SENSEA
- 1k between ID and Vout1-
- 820ohm between ID and Vout2-

### 3. JBC C245:
 - Outer shell (green wire) connected to EARTH and SENSEB
 - Heater positive(red wire) connected to Vout1- and SENSEA
 - Heater negative(blue wire) connected to Vout1+
 - 150ohm between ID and Vout1-
 - 5.6k between ID and Vout2-

### 4. JBC C210:
 - Outer shell (green wire) connected to EARTH and SENSEB
 - Heater negative (middle terminal, blue wire) connected to Vout1-
 - Heater positive (smaller terminal, red wire) connected to Vout1+ and SENSEA
 - 3.0k between ID and Vout1-
 - 5.6k between ID and Vout2-

### 5. JBC C105/C115:
 - Outer shell (green wire), connected to EARTH
 - Heater negative (blue wire), connected to Vout1-
 - Heater positive (red wire), connected to Vout1+ and SENSEA
 - 3.0k between ID and Vout1-
 - 1.0k between ID and Vout2-

### 6. JBC Microtweezers (PA120/AN120):
 - There are 2 diodes in the original handle - they must be removed or shorted
 - Outer shell of both tips (green wire) connected to EARTH
 - Heater 1 negative (blue wire) connected to Vout1-
 - Heater 1 positive (red wire) connected to Vout1+ and SENSEA
 - Heater 2 negative (brown wire) connected to Vout2-
 - Heater 2 positive (yellow wire) connected to Vout2+ and SENSEB
 - 1.0k between ID and Vout1-

### 7. JBC Nanotweezers (NP115/AN115/NP105/NP105-B):
 - There are 2 diodes in the instrument - they must be removed or shorted
 - Outer shell of both tips (green wire) connected to EARTH
 - Heater 1 negative (blue wire) connected to Vout1-
 - Heater 1 positive (red wire) connected to Vout1+ and SENSEA
 - Heater 2 negative (brown wire) connected to Vout2-
 - Heater 2 positive (yellow wire) connected to Vout2+ and SENSEB
 - 1.5k between ID and Vout1-

### 8. WELLER WSP80:
- Outer shell, PTC negative  and heater negative (white, black and brown wires) connected to EARTH, Vout1- and SENSEB
- Heater positive (blue wire) connected to Vout1+
- PTC positive (red wire) connected to SENSEA
- 120ohm between ID and Vout1-
- 5.6k between ID and Vout2-

### 9. ERSA RT80:
- Outer shell and Heater/PTC negative (pink and white wires) connected to EARTH, Vout1- and SENSEB
- Heater/PTC positive (black wire) connected to Vout1+ and SENSEA
- 300ohm between ID and Vout1-
- 110ohm between ID and Vout2-

## How to build & load the firmware

- Download MPLAB X IDE 4.20 (IDE)
- Download & install XC32 v2.50 (compiler)
- Download & install pic32 legacy peripheral libraries in C:\Program Files\Microchip\xc32\v2.50
- Check instructions at https://github.com/cv007/XC3216/blob/master/xc32xc16-info.txt for specs file (if needed)
- Open project from IDE
- Build / Build Project
- Load the produced HEX file using the Windows Unisolder application

## How to build Windows tools

- Install Visual Studio 2022 Community Edition with Desktop .net application workload
- Open Solution file in /software/PC
- Build All
- Run UniSolder project

