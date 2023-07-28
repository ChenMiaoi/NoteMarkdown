obj-m := hello.o export_symbol.o use_export_module.o error_handle_1.o error_handle_2.o module_param_1.o module_param_2.o
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
	mv .*.d build/

clean:
	make -C $(INCLUDE_DIR) M=$(shell pwd) clean
	rm -rf .tmp* build/