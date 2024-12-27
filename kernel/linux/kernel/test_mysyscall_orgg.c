#include <linux/kernel.h>
#include <linux/gpio.h>

#define OFF		0
#define ON		1
#define GPIOCNT	8

int gpioLed[GPIOCNT] = {518, 519, 520, 521, 523, 524, 525};

long sys_mysyscall(long val)
{
	long ret=0;
	ret = gpioLedInit();
	if(ret < 0)
	{
		return ret;
	}
	gpioLedSet(val);
	gpioLedFree();
	return val;
}

void gpioLedSet(val)
{
	
}
	for(i=0; i<GPIOCNT; i++)
	{
		char gpioName[1]
		sprintf(gpioName, "led%d",i);
		ret = gpio_request(gpioLed[i], gpioName);
		if(ret <0)
		{
			printk("Failed request gpio%d error\n",gpioLed[i]);
			return ret;
		}
	}
	
	for(i=0; i<GPIOCNT; i++)
	{
		ret = gpio_direction_output(gpioLed[i], OFF);
		if(ret<0)
		{
			printk("Failed direction_output gpio%d error\n", gpioLed[i]);
			return ret;
		}
	}
	for(i=0; i<GPIOCNT; i++)
	{
		gpio_set_value(gpioLed[i], (val & (0x01 << i)));
	}

	for(i=0; i<GPIOCNT; i++)
	{
		gpio_free(gpioLed[i]);
	}

	return ret;
}
