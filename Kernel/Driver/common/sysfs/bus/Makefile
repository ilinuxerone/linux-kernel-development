ifneq (${KERNELRELEASE},)
	obj-m	:=  bus_basic.o  bus.o device.o  driver.o
else
	PWD	:= `pwd`
	KVER	:= `uname -r`
	KDIR	:= /lib/modules/${KVER}/build
all:
	${MAKE} -C ${KDIR}  M=${PWD} modules
.PHONY:clean
clean:
	-rm *.o  *.ko* *.sym* *.order *.mod.c
endif
