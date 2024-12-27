#include <linux/kernel.h>
#include <linux/gpio.h>

#define OFF     0
#define ON      1
#define GPIOCNT 8

int gpioLed[8] = {518, 519, 520, 521, 522, 523, 524, 525};
int ret = 0;

void gpioLedInit(void);
void gpioLedSet(long val);
void gpioLedFree(void);

long sys_mysyscall(long val) {
        gpioLedInit();
        if(ret < 0)
                return ret;
        gpioLedSet(val);
        gpioLedFree();

        return (long)ret;
}

void gpioLedInit(void) {
        char gpioName[10];
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


