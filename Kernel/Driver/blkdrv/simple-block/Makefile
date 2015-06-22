ifneq ($(KERNELRELEASE),)

obj-m := simple-blk.o
target := modules

else

KDIR := /lib/modules/`uname -r`/build
all:
	make -C $(KDIR) M=$(PWD)  $(target)
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers

endif
