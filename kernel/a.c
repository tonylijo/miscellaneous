#include <sys/io.h>

main(int argc,char *argv[])
{
	iopl(3);
	outb(atoi(argv[1]), 0x378);
}
