ifneq ($(KERNELRELEASE), )
	obj-m	:=   chrdev.o
else
	PWD = $(shell pwd)
	KVER = $(shell uname -r)
	KDIR = /lib/modules/$(KVER)/build
	
all:
	$(MAKE) -C $(KDIR) M=$(PWD)  modules
endif
