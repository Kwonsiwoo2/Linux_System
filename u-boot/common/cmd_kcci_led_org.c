#include <vsprintf.h>
#include <command.h>
#include <asm/io.h>

#define BCM2711_GPIO_GPFSEL0    0xFE200000
#define BCM2711_GPIO_GPFSEL1    0xFE200004
#define BCM2711_GPIO_GPFSEL2    0xFE200008
#define BCM2711_GPIO_GPSET0     0xFE20001C
#define BCM2711_GPIO_GPCLR0     0xFE200028
#define BCM2711_GPIO_GPLEV0     0xFE200034

#define GPIO6_9_SIG_OUTPUT      0x09240000
//#define GPIO10_13_SIG_OUTPUT    0x00012249
#define GPIO10_13_SIG_OUTPUT    0x00000249
#define GPIO20_23_SIG_INPUT     0X00000000

void led_init(void)
{
    unsigned long temp;
    temp = readl(BCM2711_GPIO_GPFSEL0);         //read
    temp &= 0x0003ffff;                   //modify(bit clear)
    temp |= GPIO6_9_SIG_OUTPUT;           //modify(bit set: output)
    writel(temp, BCM2711_GPIO_GPFSEL0);         //write

    temp = readl(BCM2711_GPIO_GPFSEL1);
    temp &= 0xfffff000;
    temp |= GPIO10_13_SIG_OUTPUT;
    writel(temp, BCM2711_GPIO_GPFSEL1);
}

void led_write(unsigned long led_data)
{
    writel(0x3fc0, BCM2711_GPIO_GPCLR0);
    led_data = led_data << 6;
    writel(led_data, BCM2711_GPIO_GPSET0);
}

static int do_KCCI_LED(struct cmd_tbl *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned long led_data;
    if(argc!=2)
    {
        cmd_usage(cmdtp);
        return 1;
    }
    printf("*LED TEST START\n");
    led_init();
    led_data = simple_strtoul(argv[1],NULL,16);
    led_write(led_data);
    printf("*LED TEST END()%s : %#04x\n\n", argv[0],(unsigned int)led_data);
    return 0;
}

U_BOOT_CMD(
    led,2,0,do_KCCI_LED,
    "led - kcci LED Test",
    "number - Input argument is only one.(led [0x00~0xff])\n");
