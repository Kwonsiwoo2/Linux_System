APP := kerneltimer_app
MOD := kerneltimer_dev
SRC := $(APP).c
obj-m := $(MOD).o

CROSS = ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
CC := arm-linux-gnueabihf-gcc
KDIR := /home/ubuntu/pi_bsp/kernel/linux
PWD := $(shell pwd)

default:clean $(APP)
	$(MAKE) -C $(KDIR) M=$(PWD) modules $(CROSS)
	cp $(MOD).ko /srv/nfs/drivers
$(APP):
	$(CC) $(APP).c -o $(APP)
	cp $(APP) /srv/nfs/drivers
clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf modules.order
	rm -rf Module.symvers
	rm -rf $(MOD).mod
	rm -rf .tmp_versions
	rm -rf $(APP)
