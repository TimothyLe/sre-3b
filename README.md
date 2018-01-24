**Pinning of the Arduino Uno to CAN BUS Shield (Optional)**
1. Connect LCD to the CAN BUS Shield via connector  
2. Connect CBS to Arduino  
![Layout of Arduino](http://www.sharetechnote.com/image/Arduino_Uno_FullBoard_03.png)  
* INT0 -> Pin 2 _Ext Int 0_  
* CLK -> Pin 13 _SCK_  
* MISO -> Pin 12 _MISO_  
* MOSI -> Pin 11 _MOSI_  
* SS -> Pin 10 _SS_  
* GND -> GND
* 5 -> 5V or 3.3V for LED  
3. (Optional) Skip Arduino SPI and flash to the Atmel 432 on the CBS  
4. Include "mcp_can.h" using CAN BUS Shield library from Seeed  
[CAN BUS Shield Arduino Library](https://github.com/Seeed-Studio/CAN_BUS_Shield)  
5. Perform these tasks:  
```
ToDo:
	-fix the message display
	-make sure pointers are being used correctly
	-Add Error interpretters for BMS, Motor Controller, VCU, (and our own errors)
	
-------------------------------------------------
Above messages are written by Alfredo in the past.
Below messages are written by Xiao. (1/23/2018)

You need to put CAN_BUS_Shield, Newliquidcrystal_1.3.5 and LEDv0.2 folders inside the arduino's "libraries" folder.
They contain libraries that are necessary to compile the code.

The first two libraries are open source libraries from internet (github).
The third might also be some kind of library written by Alfredo.

Newliquidcrystal_1.3.5 contains new LiquidCrystal_I2C library, your LiquidCrystal_I2C library might be outdated so some errors might come out while compiling it.  
```

# General Info

[Using the low voltage power supply](https://github.com/spartanracingelectric/SRE-2/raw/master/XHR-33-18%20Power%20Supply%20Instructions.docx)    
*You can also scroll down*

# SRE-2

[Programming for the HY-TTC50](http://1drv.ms/1NQUppu)

[VCU Pinout](https://1drv.ms/x/s!Avhc248Pj7v5gt4A6qt_feUsrY_taA)


# SRE-3

[VCU Pinout](https://app.box.com/s/uyuxl2mdqswess6gzmn8ut5do8v13yul)

[CAN Addresses](https://app.box.com/s/gschelv0rgm2yylm6qngef2f5tt4ew2y)

[EEPROM Addresses](https://app.box.com/s/nbz92djxusbby6u214ghj4r6kfeen3ia)

# Questions?
More information about the SRE-2 can be found in the wiki:  
https://github.com/Spartan-Racing-Electric-SJSU/sre-3b/wiki
