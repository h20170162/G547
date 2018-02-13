This Device Driver code will execute delay in milliseconds through 8254 Programmable Interval Timer

 
Follow these steps to build the program:

STEP : 1
$ make all
$ sudo insmod timer.ko

This will load the device driver into kernel.

STEP : 2
$ gcc timer.c -o timer
$ sudo ./timer

The program will ask to enter delay in ms:
a. Read current timer counter value.
b. Insert delay (in milliseconds).
