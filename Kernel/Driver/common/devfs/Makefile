ifneq (${KERNELRELEASE},)
	obj-m		:=   dev.o  ioctl.o
else
 	PWD		:= `pwd`
	KVER		:= `uname -r`
	KDIR		:= /lib/modules/${KVER}/build  

default:
	${MAKE} -C ${KDIR} M=${PWD} modules
.PHONEY:clean
clean:
	-rm -f *.o *.ko*  *.sym* *.mod.* *.order*

endif

