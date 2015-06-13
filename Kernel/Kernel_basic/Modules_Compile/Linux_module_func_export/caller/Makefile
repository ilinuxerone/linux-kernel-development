#for Cross-compile
KERNELDIR = /home/tekkaman/development/linux-omap3
#KBUILD_EXTRA_SYMBOLS = /home/tekkaman/development/research/Linux_module/exporter_1/Module.symvers
#KBUILD_EXTRA_SYMBOLS += /home/tekkaman/development/research/Linux_module/exporter_2/Module.symvers
#for Local compile
#KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
INSTALLDIR := ./

CROSS_COMPILE = arm-none-linux-gnueabi-

ARCH = arm
MODULE_NAME = caller


obj-m := $(MODULE_NAME).o

.PHONY: modules modules_install clean

modules:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	sudo cp $(MODULE_NAME).ko $(INSTALLDIR)

clean:
	@rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order .*.o.d
