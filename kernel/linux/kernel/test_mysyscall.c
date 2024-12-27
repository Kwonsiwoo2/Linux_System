#include <linux/kernel.h>

long sys_mysyscall(long val)
{
	printk(KERN_INFO "welcome to KCCI's ~ app value %ld\n", val);
	return val * val;
}
