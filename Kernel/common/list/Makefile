ifneq (${KERNELRELEASE},)
	obj-m 	:=  list.o list_safe.o

else
	PWD	:= `pwd`
	KVER	:= `uname -r`
	KDIR	:= /lib/modules/${KVER}/build
default:
	${MAKE} -C ${KDIR} M=${PWD} modules

.PHONEY:clean
clean:
	-rm -f  *.o *.ko* *.mod.c  *.order* *.symvers
endif
