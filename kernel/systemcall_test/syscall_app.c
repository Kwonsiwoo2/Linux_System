#include <stdio.h>
#include <unistd.h>
#include <asm-generic/unistd.h>

#define LEFT    0
#define RIGHT   1
#pragma GCC diagnostic ignored "-Wunused-result"
int main()
{
	long i = 0x01;
	int direction = LEFT;

    int ret;
    
	do{
        ret = syscall(__NR_mysyscall, i);
        if(ret<0)
    	{
    		perror("syscall");
       	 	return 1;
    	}
        for(int j=0;j<8;j++)
		{
			if(i & (0x01 << j))
				putchar('O');
			else
				putchar('X');
			if(j != 7 )
				putchar(':');
			else
				putchar('\n');
		}
		if (direction == LEFT) 
        {
            if (i == 0x100) {
                i = 0x80;
                direction = RIGHT;
			}
            else
            {
                i <<= 0x01;
            }
        } 
        else 
        {
	        if (i == 0x00) 
            {
                i=0x01;
                direction = LEFT;
            }
            else{
                i >>= 0x01;
            }
        }
        usleep(50000);
    }   while(1);
	return 0;
}
