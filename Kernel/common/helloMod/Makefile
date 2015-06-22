ifneq ($(KERNELRELEASE),)
	obj-m	:=  hello.o
else	
	PWD	:=  $(shell pwd)
	KVER	:=  $(shell uname -r)
	KDIR	:=  /lib/modules/$(KVER)/build

default:
	$(MAKE) -C  $(KDIR) M=$(PWD) modules
clean:
	-rm -r  *.o  *.ko *.mod.c 
endif
