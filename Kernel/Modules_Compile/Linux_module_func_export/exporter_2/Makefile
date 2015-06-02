#for Cross-compile
KERNELDIR= /home/tekkaman/development/linux-omap3

#for Local compile
#KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
INSTALLDIR := ./

CROSS_COMPILE = arm-none-linux-gnueabi-

ARCH = arm
MODULE_NAME = exporter_2


obj-m := $(MODULE_NAME).o

.PHONY: modules modules_install clean

modules:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	sudo cp $(MODULE_NAME).ko $(INSTALLDIR)

clean:
	@rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order .*.o.d
