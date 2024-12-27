#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int ret;

	ret = mknod("/dev/test_dev",S_IRWXU | S_IRWXG | S_IRWXO | S_IFCHR, (230<<8)|1);
	if(ret < 0)
	{
		perror("mknod()");
		return ret;
	}
	ret = open("/dev/ledkey_dev", O_RDWR);
	if(ret < 0)
	{
		perror("open()");
		return ret;
	}	
	return 0;
} 
