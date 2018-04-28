# usb-to-i2c

## Prerequisite for the project

As this project borrows the USB Vendor ID and Product ID from the project "i2c-tiny-usb", which is now a part of linux kernel, hence before executing this project we have to remove the kernel module of i2c-tiny-usb project named as "i2c_tiny_usb". Otherwise our usb probe function will never be called.

* Command to remove the i2c-tiny-usb module : - "sudo rmmode i2c_tiny_usb".

## Summary

This project aims to devlop a USB-I2C converter, that can interface any i2c device to the PC through USB. There is no custom hardware is needed anymore.Through i2c bus we can control upto 128 slave devices using Two Wire Interface. These slave devices can be tempreture sensor, EPROM or another microcontroller. Here in this project we have taken ARDUINO UNO(ATMega32) as slave device tested Bi-dirextional data transfer between master and slave device. 


## Introduction

Attach any I2C client chip (thermo sensors or other microcontroller as ARDUINO ) to your PC via USB. The data transfer is done through i2c protocol. 

The i2c-usb project is an open source/open hardware project. The goal of i2c-usb is to provide a cheap generic i2c interface to be attached to the usb. It is meant as a replacement for those simple and cheap printer port to i2c adapters. A USB solution has several advantages incl. the built-in power supply and a more future proof interface. Furthermore no cpu intense bitbanging is required on the host side. This USB solution even requires less parts than some printer port solutions.

The i2c-usb project is based on:

*   The [Linux USB project](http://www.linux-usb.org/) and the <a hreh="http://www.kernel.org">Linux i2c</a> implementation
*   The windows driver and test application are based on [the libusb-win32](http://libusb-win32.sourceforge.net/)
*   [AVR-USB, a pure software implementation of USB for the AVR platform](http://www.obdev.at/products/avrusb/index.html)  

## Hardware

![](images/hardware.jpg)
---- | ----
**The prototype board including** | **The final hardware with**
**an ARDUINO UNO to test I2C Protocol**

The hardware of the i2c-usb interface consists of the [Atmel AVR Atmega8 CPU](https://www.mouser.com/ds/2/268/Atmel-2486-8-bit-AVR-microcontroller-ATmega8_L_dat-1065398.pdf), a cheap and easy to obtain microcontroller with 8 KBytes flash (of which ~2k are used in this application) and 1 KB RAM. The processor is surrounded by few other parts.

### The USB interface

The USB interface of the i2c-usb interface is based on a pure software implementation and uses two pins of the AVR (PD2 and PD4). This software implementation supports low speed USB only which is signalled to the PC by resistor R.

The I2C interface is implemented using a bitbanging approach. The hardware supported twi(two wire) interface of the atmega8 is bound to hardware pins at the chip that are required for USB operation and can thus not be used for I2C. The bitbanging I2C interface being used instead may not be fully I2C compatible and thus not every I2C client chip may function correctly at this bus. No incompatibilities have been reported so far. The i2c-usb provides a software adjustable i2c clock delay allowing to configure the i2c clock. The default delay is 10us. Due to additional delays in the i2c bitbanging code this results in a i2c clock of about 50kHz.

For simplicity reasons all USB transfers are done via the control endpoint. Since the avr usb library does only support low speed devices it cannot use bulk transfers which are specified for high and full speed devices only. Low speed devices support so called interrupt transfers which are limited to a preset bandwidth while control transfers can use any free bandwidth (if there's any at all).

The device therefore uses control transfers for all of its communication. This requires some additional limitation to prevent multiple driver software (e.g. the kernel driver and the libusb based test application) to access the device at the same time. Under Linux this can be achieved by selecting certain access request types. This kind of access control may not be possible under other operating systems.

### Power consumption

The whole device is a so called bus powered device. This means that the complete device is powered directly from USB. Therefore the AVR and one or more I2C client chips are powered from the USB VBUS signal.

The adapter itself draws less than 10mA and reports this to the host via its USB descriptors. The device is able to power I2C client chips as well. But since these chips vary in power consumption it is not possible to correctly include their demands into the device descriptors. It's your responsibility to keep an eye on the total power supply and especially to make sure that the entire device does not exceed the total USB limit of 500mA.


### Kernel driver

The i2c-usb is meant to be used with Linux. It comes with a Linux kernel driver that bridges between the USB and I2C subsystems in the Linux kernel. The driver then attaches to the USB device and make the i2c bus available to the i2c subsystem. Thus the entire setup is transparent to client applications like the two wire bidirectional data transfer with ARDUINO UNO and no special client chip drivers are required. Instead the drivers already present in the linux kernel are used with the i2c-usb as well.


### Schematic

![](images/schematic.png)

The zener diodes in the schematic are optional. They are required since the i2c-usb is directly powered from the USBs VBUS singnal at 5V. The USB data lines (D+ and D-) are supposed to be operated at 3.3V only. Some PCs encounter problems at 5V and limiting the voltage to at most 3.6V may help. My prototype lacks these diodes since my PC works fine with D+ and D- at 5V.

Resistor R1 is 1.5k instead of 1k for the same reason. It is meant to pullup to 3.3V. Since we are pulling up to 5V the higher resistance is required.


### Part list

You can get all parts directly. This list includes the following

Part | Qty | Name | 
---- | ---- | ---- |
D1, D2 | 2 | 3.6V zener diode 
X1 | 1 | 16Mhz crystal, XTAL18 package  
R | 1 | 1.5 kilo ohm resistor  
R3, R4 | 2 | 1.5 kilo ohm resistor  
R5 | 1 | 5 mega ohm resistor
R1, R2 | 2 | 68 ohm resistor
C1, C2 | 2 | 22pF ceramic capacitor, 2.54mm
C3 | 1 | 10nF capacitor, 5.08mm
C4 | 1 | 10μF electrolytic capacitor 
J1 | 1 | USB-B print connector 
I2C PORT | 1 | 2 pin I2C connector 
U1 | 1 | Atmega8l DIP  
-- | 1 | socket for U1

## Compiling & Uploading the firmware

Firmware compilation and uploading procedure can be found inside "/firmware/Readme.txt" file. 

## Using the device with a ARDUINO UNO

The i2c_usb works at various hosts. One of the most interesting ones is the ARDUINO UNO. You need to connect the A5 of Arduino Uno to SCL and A4 to SDL of atmega8 to make use of the i2c-usb.

![](images/arduino.jpg)

The demo application can easily be installed on the ARDUINO Platform . Once it's connected  it can be seen the address of arduino by simple command $(make detect) from /testapp. To send data to the slave(arduino) just type $(make write [data]) and the sent string can be shown in the serial monitor of the Arduino IDE.To receive data from the slave type $(make read), and the data sent from the slave will be shown in the terminal.


[![](images/screenshot.jpg)]

The i2c_usb demo application can support multiple I2C client chips. Further chips can easily be supported.

## Links

*   [AVR-USB, software USB for the AVR platform](http://www.obdev.at/products/avrusb/index.html)
*   [USBtiny, another software usb implementation for the AVR](http://www.xs4all.nl/~dicks/avr/usbtiny/)
*   [USB user space library libusb](http://libusb.sourceforge.net/)
*   [The Linux USB Project](http://www.linux-usb.org/)

* * *

## Note
Please note that, here in this project we have developed just an USB-I2C converter prototype with out client drivers.
To access any client device, you have to write separate kernel driver for client devices.
 
