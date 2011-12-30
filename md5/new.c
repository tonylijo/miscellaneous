#include<stdio.h>
#include<openssl/md5.h>

char gethexchr(char a) 
{	
	return "0123456789ABCDEF"[a];
}

char *hex(char a) 
{
	static char str[3];
	str[0] = gethexchr(a>>4);
	str[1] = gethexchr(a & 0x0f);
	str[2] = 0;
	return str;
}
int main(int argc,char *argv[])
{
	char digest[16];
	MD5("Tony",4,digest);
	char *b = hex((char)-1);
	printf("%s\n",b);
	return 0;
}
