#include<stdio.h>
#include<string.h>

void swap(char *a,char *b)
{
  char tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

char *strcpy_1(char *dst,char *src)
{
  if(*dst++ = *src++) 
    return strcpy_1(dst,src);
}

int strlen_1(char *src)
{
  if(*src) 
    return strlen_1(++src)+1;
  else 
    return 0;
}

char *strcat_1(char *src,char *dst)
{
  static flag = 1;
  int len;
  static char *tmp;

  if(flag) {
    len = strlen_1(src);
    flag = 0;
    tmp = src + len;
  }
  
  if(*tmp = *dst)
    return strcat_1(++tmp,++dst);
  else 
    return src;
}
void reverse(char *src,int i,int j) 
{
  if(i < j) {
    swap(&src[i],&src[j]);
    reverse(src,++i,--j);
  }
}

void strrev_1(char *src)
{
  reverse(src,0,strlen(src)-1);
}

int strcmp_1(char *src,char *dst)
{
  static int flag;
  if(!(*src - *dst) && (*src != 0) && (*dst != 0) ) {
    return strcmp_1(++src,++dst);
  } else {
    return *src - *dst;
  }
}

int main()
{
  char str1[] = "tony";
  char str2[] = "lijo";
  char dummy[100];
  printf("len = %d\n",strlen_1(str1));
  strcpy_1(dummy,str1);
  printf("%s\n",dummy);
  strcat_1(dummy,str1);
  printf("%s\n",dummy);
  strrev_1(dummy);
  printf("reverse %s\n",dummy);
  printf("tony tony %d\n",strcmp_1("tony","tony"));
  printf("tony ton %d\n",strcmp_1("tony","ton"));
  printf("tony jony %d \n", strcmp_1("tony","jony"));
  printf("ton tony %d \n",strcmp_1("ton","tony"));
  printf("jon tony %d \n",strcmp_1("jon","tony"));
}
