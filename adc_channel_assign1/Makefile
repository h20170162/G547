obj-m += adc.o
version=`uname -r`
all:
	make -C /lib/modules/$(version)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(version)/build M=$(PWD) clean
