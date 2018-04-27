i2c-usb
---------------------------------------

This is the user space code to detect, read and write data to the intrfaced device.


To Compile the user space program, type
           make compile

To detect connected i2c devices, type
           make detect

To send data to connected i2c devices, type
           make write // The program itself will ask for different inputs (like slave address,adapter number,data to be sent etc.)

To receive data from connected i2c devices, type
           make read // The program itself will ask for different inputs (like slave address,adapter number)

To clean, type
           make clean            



