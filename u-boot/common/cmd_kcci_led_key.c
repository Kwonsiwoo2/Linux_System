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
    writel(temp,BCM2711_GPIO_GPFSEL1);
}

void print_key_status(unsigned long key_data)
{
    printf("0:1:2:3:4:5:6:7\n");

    for (int i = 0; i < 8; i++) {
        if (key_data & (1 << i)) {
            printf("O:");
        } else {
            printf("X:");
        }
    }
    printf("\n\n");
}

void key_init(void)
{
    unsigned long temp;

    temp = readl(BCM2711_GPIO_GPFSEL1); 
    temp &= ~(0xFFF << 18);
    writel(temp, BCM2711_GPIO_GPFSEL1);

    temp = readl(BCM2711_GPIO_GPFSEL2);
    temp &= ~(0xFFFF << 0);
    writel(temp, BCM2711_GPIO_GPFSEL2);
}

void key_read(unsigned long *key_data)
{
    unsigned long temp;

    temp = readl(BCM2711_GPIO_GPLEV0);
    temp = (temp >> 16) & 0xFF;
    *key_data = temp;   
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
    unsigned long key_data;
    unsigned long prev_key_data = 0x00;
    unsigned long handled_keys = 0x00;

    if(argc!=2)
    {
        cmd_usage(cmdtp);
        return 1;
    }
    printf("*LED TEST START\n");
    led_init();
    key_init();

    led_data = simple_strtoul(argv[1],NULL,16);
    led_write(led_data);

    do{
        key_read(&key_data);    

        unsigned long newly_pressed =  key_data & ~handled_keys;

        if(newly_pressed)
        {
            led_write(key_data);
            print_key_status(key_data);
            handled_keys |= newly_pressed;
        }

        handled_keys &= key_data;

        if(key_data == 0x80)
        {
            break;
        }
    }while(1);

    printf("*LED TEST END()%s : %#04x\n\n", argv[0],(unsigned int)led_data);
    return 0;
}

U_BOOT_CMD(
    led,2,0,do_KCCI_LED,
    "led - kcci LED Test",
    "number - Input argument is only one.(led [0x00~0xff])\n");
