#
# Makefile
#

APP = write_usb_to_i2c
APP1 = find_usb_to_i2c
APP2 = read_usb_to_i2c

clean:
	rm -f $(APP) $(APP1) $(APP2)

compile:
	gcc $(APP).c -O -o $(APP)
	gcc $(APP1).c -O -o $(APP1)
	gcc $(APP2).c -O -o $(APP2)
write:
	sudo ./$(APP)
detect:
	sudo ./$(APP1)
read:
	sudo ./$(APP2)

