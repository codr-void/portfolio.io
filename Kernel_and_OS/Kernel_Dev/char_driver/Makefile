obj-m += char_dev.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Target for kernel module
all: modules userspace

modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

userspace:
	gcc -o userspace userspace.c

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
	rm -f userspace

