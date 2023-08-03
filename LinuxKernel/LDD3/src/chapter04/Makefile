obj-m := test_debug.o
INCLUDE_DIR := /lib/modules/$(shell uname -r)/build
# INCLUDE_DIR := /usr/src/linux-2.6.10

build:
	make -C $(INCLUDE_DIR) M=$(shell pwd) modules
	mkdir build
	mv *.mod build/
	mv *.order build/
	mv *.symvers build/
	mv .*.cmd build/
	mv *.mod.c build/
	mv *.mod.o build/
	mv *.o build/
	# mv .*.d build/

clean:
	make -C $(INCLUDE_DIR) M=$(shell pwd) clean
	rm -rf .tmp* build/