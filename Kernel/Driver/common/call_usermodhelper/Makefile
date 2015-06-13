ifneq (${KERNELRELEASE},)
	obj-m		:=   usermod_helper.o
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

