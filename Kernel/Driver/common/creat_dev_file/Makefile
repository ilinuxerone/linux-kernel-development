ifneq ($(KERNELRELEASE),)
	obj-m  	:= cdev.o
else
	PWD	:= $(shell pwd)
	KVER	:= $(shell uname -r)
	KDIR	:= /lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR)  M=$(PWD) modules
.PHONY:clean
clean:
	-rm  *.ko *.o *s*
endif