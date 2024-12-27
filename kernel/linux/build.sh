#make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2711_defconfig
#make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs -j4
#make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage -j4 
