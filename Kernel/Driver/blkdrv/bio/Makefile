ifneq ($(KERNELRELEASE),)

#obj-m := blk.o
obj-m := block.o

else

KDIR := /lib/modules/`uname -r`/build
all:
	make -C $(KDIR) M=$(PWD) modules 
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers

endif
