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
