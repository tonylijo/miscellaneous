#include "rtc.h"
#include<assert.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

main()
{
	int fd,dat,i,r;
	fd = open("rtc",O_RDONLY);
	assert(fd >= 0) ;
	
	r = ioctl(fd,RTC_PIE_ON,0);
	assert(r == 0);
	r = ioctl(fd,RTC_IRQP_SET,15);
	
	assert(r == 0);
	for(i = 0; i < 20; i++) {
		read(fd,&dat, sizeof(dat));
		printf("i = %d \n",i);
	}
}
