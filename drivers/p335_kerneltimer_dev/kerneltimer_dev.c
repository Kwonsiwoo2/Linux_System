#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/moduleparam.h>

#define DEBUG 1

#define OFF 0
#define ON 1
#define GPIOCNT 8

#define   LEDKEY_DEV_NAME            "kerneltimer"
#define   LEDKEY_DEV_MAJOR            230    


static int gpioLedInit(void);
static void gpioLedSet(long val);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);
void kerneltimer_func(struct timer_list *t);

static int gpioLedInitFlag = 0;
static int gpioKeyInitFlag = 0;

static int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};
static int openFlag = 0;

static int timerVal = 100;
module_param(timerVal, int, 0);
static int ledVal = 0;
module_param(ledVal, int, 0);
struct timer_list timerLed;

static int ledkey_open (struct inode *inode, struct file *filp)
{
#if DEBUG
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
#endif
	if(openFlag)
		return -EBUSY;
	else
		openFlag = 1;

	if(!try_module_get(THIS_MODULE))
		return -ENODEV;

    return 0;
}

static loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
#if DEBUG
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
#endif
    return 0x23;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	kbuf=gpioKeyGet();
#if 1
	put_user(kbuf,buf);
#else
	int ret=copy_to_user(buf,&kbuf,sizeof(kbuf));
	if(ret < 0)
        return ret;
#endif

#if DEBUG
    printk( "call read -> key : %04X\n", kbuf );
#endif
    return sizeof(kbuf);
}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
#if 1
	get_user(kbuf,buf);
#else
	int ret;
	ret=copy_from_user(&kbuf,buf,sizeof(kbuf));
#endif

#if DEBUG
    printk( "call write -> led : %04X\n", kbuf );
#endif
	ledVal=kbuf;
	//gpioLedSet(kbuf);
	//return sizeof(kbuf);
	return sizeof(ledVal);
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
    return 0x53;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	//if (gpioLedInitFlag)
	//	gpioLedFree();
	//if(gpioKeyInitFlag)
	//	gpioKeyFree();
	module_put(THIS_MODULE);
	openFlag = 0;
    return 0;
}

static int gpioLedInit(void)
{
	int i;
	int ret=0;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"led%d",i);
		ret = gpio_request(gpioLed[i], gpioName);
		if(ret < 0)
		{
			printk("Failed request gpio%d error\n",gpioLed[i]);
			return ret;
		}
		ret = gpio_direction_output(gpioLed[i],OFF);
		if(ret < 0)
		{
			printk("Failed directon_output gpio%d error\n",gpioLed[i]);
			return ret;
		}
	}
	gpioLedInitFlag = 1;
	return ret;
}
static void gpioLedSet(long val)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],(val & (0x01 << i)));
	}
}
static void gpioLedFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioLed[i]);
	}
	gpioLedInitFlag = 0;
}
static int gpioKeyInit(void)
{
	int i;
	int ret=0;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"key%d",i);
		ret = gpio_request(gpioKey[i], gpioName);
		if(ret < 0) {
			printk("Failed Request gpio%d error\n", gpioKey[i]);
			return ret;
		}
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n", gpioKey[i]);
       	 	return ret;
		}
	}
	gpioKeyInitFlag = 1;
	return ret;
}
static int	gpioKeyGet(void)
{
	int i;
	int ret;
	int keyData=0;
	for(i=0;i<GPIOCNT;i++)
	{
//		ret=gpio_get_value(gpioKey[i]) << i;
//		keyData |= ret;
		ret=gpio_get_value(gpioKey[i]);
		keyData = keyData | ( ret << i );
	}
	return keyData;
}
static void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
	gpioKeyInitFlag = 0;
}

struct file_operations ledkey_fops =
{
//    .owner    = THIS_MODULE,
    .open     = ledkey_open,     
    .read     = ledkey_read,     
    .write    = ledkey_write,    
	.unlocked_ioctl = ledkey_ioctl,
    .llseek   = ledkey_llseek,   
    .release  = ledkey_release,  
};
void kerneltimer_registertimer(unsigned long timeover)
{
    timerLed.expires = get_jiffies_64() + timeover;
    timer_setup(&timerLed, kerneltimer_func, 0);
    add_timer(&timerLed);
}
void kerneltimer_func(struct timer_list *t)
{
#if DEBUG
    printk("ledVal : %#04x\n", (unsigned int)(ledVal));
#endif
    gpioLedSet(ledVal);

    ledVal = ~ledVal & 0xff;
    mod_timer(t,get_jiffies_64() + timerVal);
}

int kerneltimer_init(void)
{
	int result;
#if DEBUG
    printk("timerVal : %d, sec : %d\n", timerVal, timerVal/HZ);
#endif
    result = gpioLedInit();
	if(result < 0)
	{
		return result;
	}
    result = gpioKeyInit();
	if(result < 0)
	{
		return result;
	}
	 result = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (result < 0) return result;

    kerneltimer_registertimer(timerVal);
    return 0;
}
void kerneltimer_exit(void)
{
	gpioLedFree();
	gpioKeyFree();
    if(timer_pending(&timerLed))
	{
        del_timer(&timerLed);
	}
	unregister_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME);
}
module_init(kerneltimer_init);
module_exit(kerneltimer_exit);
MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");
