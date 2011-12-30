<<<<<<< HEAD
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
=======
/*
 *This program creates a unique hash sum of a given string using the 
 *MD5 algorithm 
 *it uses the openssl library 
 */
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<openssl/md5.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#define err_exit(msg) \
  do { perror(msg); exit(errno); } while(0)


/*
 * get the correspondign hexadecimal digit 
 */
char get_hex(unsigned char i)
{
  return "0123456789abcdef"[i];
}

/* 
 * create the corresponding hexadecimal string
 */
char *hex(unsigned char *msg_digest)
{
  static char dst[33];
  int i,j=0;
  for(i = 0; i < 16; i++) {
    dst[j++] = get_hex(msg_digest[i]>>4);
    dst[j++] = get_hex(msg_digest[i] & 0x0f);
  }
  dst[j] = 0;
  return dst;
}

/* 
 * returns the address of the virtual memory 
 * where the file is mapped by the kernel.
 */
char *get_vm_addr(char *filename)
{
  static char *map;
  int fd;
  int file_size = get_size(filename);
  
  if((fd = open(filename,O_RDONLY)) < 0) 
    err_exit("open:");

  if((map = mmap(NULL,file_size,
	PROT_READ,MAP_PRIVATE,fd,0)) == MAP_FAILED) {
      close(fd);
      err_exit("mmap");
  }
  return map;
}

/*
 * returns the size of the given file
 */
int get_size(char *filename)
{
  struct stat sb;
  int fd;
  if((fd = open(filename,O_RDONLY)) < 0) 
    err_exit("open:");
  if(fstat(fd,&sb) == -1) 
    err_exit("fstat");
  close(fd);
  return sb.st_size;
}
  
  
int main(int argc,char *argv[])
{
  unsigned char msg_digest[16];
  int length = get_size(argv[1]);
  char *map = get_vm_addr(argv[1]);
  
  MD5(map,length,msg_digest);
  printf("%s\n",hex(msg_digest));
>>>>>>> a9bbca8da218e60f5741381a0a89b47e2715040d
}
