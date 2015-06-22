ifneq (${KERNELRELEASE},)
	obj-m 	:= mem_alloc.o
else
	PWD  	:= $(shell pwd)
	KVER	:= $(shell uname -r)
	KDIR	:= /lib/modules/${KVER}/build
all:
	${MAKE} -C ${KDIR} M=${PWD} modules
.PHONE:clean
clean:
	-rm *.o *.ko *.mod*  *s*
endif
