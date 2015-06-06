ifneq (${KERNELRELEASE},)
	obj-m	:= list.o
else
	PWD	:= `pwd`
	KVER	:= `uname -r`
	KDIR	:= /lib/modules/${KVER}/build

default:
	${MAKE} -C ${KDIR}  M=${PWD} modules
.PHONEY:clean
clean:
	-rm *.ko* *.o *sym*   *mod*

endif
