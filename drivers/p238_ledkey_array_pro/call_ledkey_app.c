#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_FILENAME  "/dev/ledkey_dev"

void print_led(char *);
void print_key(unsigned char);
int main(int argc,char * argv[])
{
    int dev;
    char buff[8] = {0};
    char buffOff[8] = {0};
	char oldBuff[8] = {0};
    int ret;
	int i;
	if(argc < 2)
	{
		printf("USAGE : %s [ledval] \n",argv[0]);
		return 1;
	}
	ret = strtoul(argv[1],NULL,16);
	for(i=0;i<8;i++)
	{
		buff[i] =  (ret >> i) & 0x01;
//		printf("buff[%d]: %d\n",i,buff[i]);
	}

    dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY );
	if(dev<0)
	{
		perror("open()");
		return 2;
	}
    ret = write(dev,buff,sizeof(buff));
	if(ret < 0)
	{
		perror("write()");
		return 3;
	}
	print_led(buff);

	memset(buff,0,sizeof(buff));
	do {
		usleep(100000);
		read(dev,buff,sizeof(buff));
#if 1
		if(memcmp(buff,buffOff,sizeof(buff)))
		{
			if(memcmp(buff,oldBuff,sizeof(buff)))
			{
				print_led(buff);
    			write(dev,buff,sizeof(buff));
				if(buff[7] == 1)
					break;
				putchar('\n');
			}
			memcpy(oldBuff,buff,sizeof(buff));
		}
#endif
	} while(1);


    close(dev);
    return 0;
}
void print_led(char * led)
{
	int i;
	puts("1:2:3:4:5:6:7:8");
	for(i=0;i<=7;i++)
	{
		if(led[i])
			putchar('O');
		else
			putchar('X');
		if(i < 7 )
			putchar(':');
		else
			putchar('\n');
	}
	return;
}

void print_key(unsigned char key)
{
	int i;
	puts("1:2:3:4:5:6:7:8");
	for(i=0;i<=7;i++)
	{
		if(key & (0x01 << i))
			putchar('O');
		else
			putchar('X');
		if(i < 7 )
			putchar(':');
		else
			putchar('\n');
	}
	return;
}
