ifneq ($(KERNELRELEASE), )
	obj-m :=  blk.o
else
	PWD := $(shell pwd)
	KVER := $(shell uname -r)
	KDIR := /lib/modules/$(KVER)/build
default:
	$(MAKE) -C $(KDIR)  M=$(PWD) modules
.PHONY:clean
clean:
	-rm  *.ko
endif
