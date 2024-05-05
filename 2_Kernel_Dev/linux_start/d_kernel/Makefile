ifneq (${KERNELRELEASE},)
	obj-m := hello.o
else
	KERNEL_SOURCE := /lib/modules/5.15.0-101-generic/build
	PwD := $(shell pwd)

default:
	$(MAKE) -C $(KERNEL_SOURCE) M=${PwD} modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=${PwD} clean
endif
