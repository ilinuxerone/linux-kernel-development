ifneq ($(KERNELRELEASE),)
	obj-m	:= platform_davice.o platform_driver.o
//	obj-m	:= platform_driver.o
else
	PWD	:= $(shell pwd)
	KVER	:= $(shell uname -r)
	KDIR	:= /lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
.PHONY:clean
clean:
	-rm  *.o *.ko
endif