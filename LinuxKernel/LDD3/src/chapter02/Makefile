obj-m := hello.o
INCLUDE_DIR := /lib/modules/$(shell uname -r)/build
# INCLUDE_DIR := /usr/src/linux-2.6.10

all:
	make -C $(INCLUDE_DIR) M=$(shell pwd) modules

clean:
	make -C $(INCLUDE_DIR) M=$(shell pwd) clean
	rm -rf .tmp*