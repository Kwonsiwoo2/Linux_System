#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define OFF     0
#define ON      1
#define GPIOCNT 8

void gpioLedInit(void);
void gpioLedSet(long val);
void gpioLedFree(void);

int gpioLed[8] = {518, 519, 520, 521, 522, 523, 524, 525};
int gpioKey[8] = {528, 529, 530, 531, 532, 533, 534, 535};


void gpioLedInit(void) {
        char gpioName[10];
        int ret;
        for(int i = 0; i < GPIOCNT; i++) {
                sprintf(gpioName, "led%d", i);
                ret = gpio_request(gpioLed[i], gpioName);
                if(ret < 0) {
                        printk("Failed Request gpio%d error\n", gpioLed[i]);
                }
        }
        for(int i = 0; i < GPIOCNT; i++) {
                ret = gpio_direction_output(gpioLed[i], OFF);
                if(ret < 0) {
                        printk("Failed direction_ouput gpio%d error\n", gpioLed[i]);
                }
        }
}

void gpioLedSet(long val) {
        for(int i = 0; i < GPIOCNT; i++)
        {
                gpio_set_value(gpioLed[i], (val & (0x01 <<i)));
        }
}

void gpioLedFree(void)
{
        for(int i = 0; i < GPIOCNT; i++)
        {
                gpio_free(gpioLed[i]);
        }
}

int gpioKeyInit(void)
{
        char gpioName[10];
        int ret = 0;
        for(int i = 0; i < GPIOCNT; i++)
        {
                sprintf(gpioName, "key%d", i);
                ret = gpio_request(gpioKey[i], gpioName);
                if(ret < 0)
                {
                        printk("Failed Request gpio%d error\n", gpioKey[i]);
                }
        }
        for(int i = 0; i < GPIOCNT; i++) {
                ret = gpio_direction_input(gpioKey[i]);
                if(ret < 0) {
                        printk("Failed direction_input gpio%d error\n", gpioKey[i]);
                }
        }
        return ret;
}

int gpioKeyGet(void) {
        int val = 0;
		int	ret;
        for(int i = 0; i < GPIOCNT; i++)
        {
			ret = gpio_get_value(gpioKey[i]);
			val = val | (ret << i);
			//if(gpio_get_value(gpioKey[i])
			//		val |= (1 << i);
        }
        return val;
}

void gpioKeyFree(void)
{
        for(int i = 0; i < GPIOCNT; i++)
        {
                gpio_free(gpioKey[i]);
        }
}

static int hello_init(void)
{
	long val=0x00;
	printk("Hello, world \n");
	gpioLedInit();
	gpioKeyInit();
	gpioLedSet(0xff);
	val=gpioKeyGet();
	printk("%ld\n",val);
	return 0;
}
static void hello_exit(void)
{
	long val = 0x00;
	printk("Goodbye, world\n");
	gpioLedSet(0x00);
	gpioLedFree();
	val=gpioKeyGet();
	printk("%ld\n",val);
	gpioKeyFree();
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
